// v06 - Wi-Fi control: the robot makes its own Wi-Fi network,
//       serves the web page, and drives the path you send from it.
//
// How to use:
//   1. Upload this sketch (index_html.h must be in the same folder).
//   2. On your phone/laptop, join Wi-Fi "AGV-Robot" (password below).
//   3. Open http://192.168.4.1 in the browser.
//   4. Draw the map, put the robot on the Start cell facing the arrow, press Go.
//
// Changed from v05:
//  - Added Wi-Fi access point + web server (WiFi.h, WebServer.h)
//  - Web page is stored in index_html.h (made by web/make_header.py)
//  - New web addresses: /  /run  /stop  /status
//  - Path comes from the web page instead of a fixed TEST_PATH
//  - 1 second wait after Go before the robot moves
//  - SPIN times 245 ms (re-tuned in the v05 square test)

#include <WiFi.h>
#include <WebServer.h>
#include "index_html.h"

// ---------- Wi-Fi settings ----------
const char* WIFI_NAME     = "AGV-Robot";
const char* WIFI_PASSWORD = "agv12345";   // must be at least 8 characters

WebServer server(80);  // port 80 = normal web address

// ---------- Motor pins ----------
const int RPWM_Right = 23;
const int LPWM_Right = 22;
const int RPWM_Left  = 25;
const int LPWM_Left  = 21;

const int PWMFreq = 1000;
const int PWMResolution = 8;

// ---------- Calibration (milliseconds) ----------
const int RIGHT_SPEED     = 186;  // straight driving
const int LEFT_SPEED      = 180;
const int CELL_TIME       = 300;  // forward 30 cm   - confirmed v02
const int SPIN_SPEED      = 180;
const int SPIN_RIGHT_TIME = 245;  // 90 deg right    - confirmed v05
const int SPIN_LEFT_TIME  = 245;  // 90 deg left     - confirmed v05
const int PAUSE_TIME      = 300;  // stop between moves
const int START_DELAY     = 1000; // wait after Go before moving

const int MAX_PATH_LENGTH = 1000; // refuse paths longer than this

// ---------- Command runner state ----------
String commands = "";            // the path being driven
int stepIndex = 0;               // which letter we are on (-1 = start wait)
bool running = false;            // true while driving a path
bool pausing = false;            // true while stopped (start wait or between moves)
unsigned long phaseStart = 0;    // when the current move/pause started
unsigned long moveDuration = 0;  // how long the current move lasts
unsigned long pauseDuration = 0; // how long the current pause lasts

// ================= MOTORS =================

void rotateMotor(int rightSpeed, int leftSpeed) {
  ledcWrite(RPWM_Right, max(rightSpeed, 0));
  ledcWrite(LPWM_Right, max(-rightSpeed, 0));

  ledcWrite(RPWM_Left, max(leftSpeed, 0));
  ledcWrite(LPWM_Left, max(-leftSpeed, 0));
}

void stopMotors() {
  rotateMotor(0, 0);
}

// ================= COMMAND RUNNER =================

// Start the motors for one letter.
void startMove(char c) {
  if (c == 'F') {
    rotateMotor(RIGHT_SPEED, LEFT_SPEED);
    moveDuration = CELL_TIME;
  } else if (c == 'R') {
    rotateMotor(-SPIN_SPEED, SPIN_SPEED);
    moveDuration = SPIN_RIGHT_TIME;
  } else if (c == 'L') {
    rotateMotor(SPIN_SPEED, -SPIN_SPEED);
    moveDuration = SPIN_LEFT_TIME;
  }

  Serial.print("Step ");
  Serial.print(stepIndex + 1);
  Serial.print("/");
  Serial.print(commands.length());
  Serial.print(": ");
  Serial.println(c);

  pausing = false;
  phaseStart = millis();
}

// Begin a new path (letters already checked to be only F/R/L).
// The robot first waits START_DELAY, then drives.
void startCommands(String path) {
  commands = path;
  stepIndex = -1;          // -1 means "waiting to start"
  running = true;
  pausing = true;
  pauseDuration = START_DELAY;
  phaseStart = millis();
  Serial.print("New path: ");
  Serial.println(commands);
}

void stopCommands() {
  stopMotors();
  running = false;
  Serial.println("Stopped");
}

// Called again and again from loop(). Moves on to the next step
// when the current move or pause has finished. Never uses delay().
void updateRunner() {
  if (!running) return;

  unsigned long elapsed = millis() - phaseStart;

  if (!pausing && elapsed >= moveDuration) {
    // Move finished -> stop and pause
    stopMotors();
    pausing = true;
    pauseDuration = PAUSE_TIME;
    phaseStart = millis();
  } else if (pausing && elapsed >= pauseDuration) {
    // Pause finished -> next letter (or finished)
    stepIndex++;
    if (stepIndex >= (int)commands.length()) {
      running = false;
      Serial.println("Done");
    } else {
      startMove(commands[stepIndex]);
    }
  }
}

// How many commands are finished (for the progress bar)
int stepsFinished() {
  if (!running) {
    return (stepIndex >= (int)commands.length()) ? commands.length() : max(stepIndex, 0);
  }
  if (stepIndex < 0) return 0;              // still in start wait
  return pausing ? stepIndex + 1 : stepIndex; // pausing = current move is done
}

// ================= WEB SERVER =================

// Lets the page work even when opened as a local file on a laptop
void addCorsHeader() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
}

// GET /  -> send the web page
void handleRoot() {
  addCorsHeader();
  server.send_P(200, "text/html; charset=utf-8", INDEX_HTML);
}

// POST /run  -> body is the path, e.g. "FFRFFLF"
void handleRun() {
  addCorsHeader();

  if (running) {
    server.send(409, "text/plain", "BUSY");
    return;
  }

  String body = server.arg("plain");  // the text the page sent
  String path = "";

  for (int i = 0; i < (int)body.length(); i++) {
    char c = toupper(body[i]);
    if (c == 'F' || c == 'R' || c == 'L') {
      path += c;
    } else if (c == ' ' || c == ',' || c == '\n' || c == '\r') {
      // ignore spaces and separators
    } else {
      server.send(400, "text/plain", "ERR bad command");
      return;
    }
  }

  if (path.length() == 0 || (int)path.length() > MAX_PATH_LENGTH) {
    server.send(400, "text/plain", "ERR bad command");
    return;
  }

  // Answer the page first, then start driving
  server.send(200, "text/plain", "OK " + String(path.length()) + " steps");
  startCommands(path);
}

// POST /stop  -> stop now
void handleStop() {
  addCorsHeader();
  stopCommands();
  server.send(200, "text/plain", "STOPPED");
}

// GET /status  -> {"state":"running","step":3,"total":7}
void handleStatus() {
  addCorsHeader();
  String json = "{\"state\":\"";
  json += running ? "running" : "idle";
  json += "\",\"step\":";
  json += stepsFinished();
  json += ",\"total\":";
  json += commands.length();
  json += "}";
  server.send(200, "application/json", json);
}

// Anything else
void handleNotFound() {
  addCorsHeader();
  if (server.method() == HTTP_OPTIONS) {
    server.send(204);  // browser "pre-check" - just say OK
  } else {
    server.send(404, "text/plain", "Not found");
  }
}

// ================= SETUP / LOOP =================

void setup() {
  Serial.begin(115200);

  ledcAttach(RPWM_Right, PWMFreq, PWMResolution);
  ledcAttach(LPWM_Right, PWMFreq, PWMResolution);
  ledcAttach(RPWM_Left, PWMFreq, PWMResolution);
  ledcAttach(LPWM_Left, PWMFreq, PWMResolution);
  stopMotors();

  // Start the robot's own Wi-Fi network
  WiFi.mode(WIFI_AP);
  WiFi.softAP(WIFI_NAME, WIFI_PASSWORD);
  WiFi.setSleep(false);  // faster replies

  Serial.print("Wi-Fi: ");
  Serial.println(WIFI_NAME);
  Serial.print("Open http://");
  Serial.println(WiFi.softAPIP());  // normally 192.168.4.1

  // Connect web addresses to their functions
  server.on("/", HTTP_GET, handleRoot);
  server.on("/run", HTTP_POST, handleRun);
  server.on("/stop", HTTP_POST, handleStop);
  server.on("/status", HTTP_GET, handleStatus);
  server.onNotFound(handleNotFound);
  server.begin();

  Serial.println("Ready - waiting for a path");
}

void loop() {
  server.handleClient();  // answer the web page
  updateRunner();         // drive the path
}
