// v05 - Command runner: drive a path written as letters
//   F = forward one cell (30 cm)
//   R = spin 90 degrees right
//   L = spin 90 degrees left
// Test path: a square of 2 cells per side, ending where it started.
//
// Changed from v04:
//  - New "command runner" that reads a string like "FFRFFL" and drives it
//  - It uses millis() instead of delay(), so the ESP32 is never "frozen".
//    This is needed in the next version, where the robot must listen to
//    Wi-Fi (Go / Stop buttons) WHILE it is driving.

const int RPWM_Right = 23;
const int LPWM_Right = 22;
const int RPWM_Left  = 25;
const int LPWM_Left  = 21;

const int PWMFreq = 1000;
const int PWMResolution = 8;

// Straight driving (tuned)
const int RIGHT_SPEED = 186;
const int LEFT_SPEED  = 180;

// Calibrated times (milliseconds)
const int CELL_TIME       = 300;  // forward 30 cm   - confirmed v02
const int SPIN_SPEED      = 180;
const int SPIN_RIGHT_TIME = 238;  // 90 deg right    - confirmed v04
const int SPIN_LEFT_TIME  = 238;  // 90 deg left     - confirmed v04
const int PAUSE_TIME      = 300;  // stop between moves

// The path to drive (square, 2 cells per side)
const char* TEST_PATH = "FFRFFRFFRFFR";

// ---------- Command runner state ----------
String commands = "";            // the path being driven
int stepIndex = 0;               // which letter we are on
bool running = false;            // true while driving a path
bool pausing = false;            // true during the short stop after a move
unsigned long phaseStart = 0;    // when the current move/pause started
unsigned long moveDuration = 0;  // how long the current move lasts

void rotateMotor(int rightSpeed, int leftSpeed) {
  ledcWrite(RPWM_Right, max(rightSpeed, 0));
  ledcWrite(LPWM_Right, max(-rightSpeed, 0));

  ledcWrite(RPWM_Left, max(leftSpeed, 0));
  ledcWrite(LPWM_Left, max(-leftSpeed, 0));
}

void stopMotors() {
  rotateMotor(0, 0);
}

// Start the motors for one letter. Returns false for an unknown letter.
bool startMove(char c) {
  if (c == 'F') {
    rotateMotor(RIGHT_SPEED, LEFT_SPEED);
    moveDuration = CELL_TIME;
  } else if (c == 'R') {
    rotateMotor(-SPIN_SPEED, SPIN_SPEED);
    moveDuration = SPIN_RIGHT_TIME;
  } else if (c == 'L') {
    rotateMotor(SPIN_SPEED, -SPIN_SPEED);
    moveDuration = SPIN_LEFT_TIME;
  } else {
    return false;
  }

  Serial.print("Step ");
  Serial.print(stepIndex + 1);
  Serial.print("/");
  Serial.print(commands.length());
  Serial.print(": ");
  Serial.println(c);

  pausing = false;
  phaseStart = millis();
  return true;
}

// Begin driving a new path
void startCommands(String path) {
  commands = path;
  stepIndex = 0;
  running = true;

  // Skip any unknown letters at the start
  while (stepIndex < (int)commands.length() && !startMove(commands[stepIndex])) {
    stepIndex++;
  }
  if (stepIndex >= (int)commands.length()) {
    running = false;
    Serial.println("Nothing to do");
  }
}

// Emergency / manual stop
void stopCommands() {
  stopMotors();
  running = false;
  Serial.println("Stopped");
}

// Call this again and again from loop(). It checks the clock and moves
// on to the next step when the current move or pause has finished.
void updateRunner() {
  if (!running) return;

  unsigned long elapsed = millis() - phaseStart;

  if (!pausing && elapsed >= moveDuration) {
    // Move finished -> stop and start the pause
    stopMotors();
    pausing = true;
    phaseStart = millis();
  } else if (pausing && elapsed >= PAUSE_TIME) {
    // Pause finished -> next letter
    stepIndex++;
    while (stepIndex < (int)commands.length() && !startMove(commands[stepIndex])) {
      stepIndex++;  // skip unknown letters
    }
    if (stepIndex >= (int)commands.length()) {
      running = false;
      Serial.println("Done");
    }
  }
}

void setup() {
  Serial.begin(115200);

  ledcAttach(RPWM_Right, PWMFreq, PWMResolution);
  ledcAttach(LPWM_Right, PWMFreq, PWMResolution);
  ledcAttach(RPWM_Left, PWMFreq, PWMResolution);
  ledcAttach(LPWM_Left, PWMFreq, PWMResolution);
  stopMotors();

  delay(3000);  // time to step back (only here, before driving)

  Serial.print("Driving path: ");
  Serial.println(TEST_PATH);
  startCommands(TEST_PATH);
}

void loop() {
  updateRunner();
}
