const int RPWM_Right = 23;
const int LPWM_Right = 22;
const int RPWM_Left  = 25;
const int LPWM_Left  = 21;

const int PWMFreq = 1000;
const int PWMResolution = 8;

// Straight driving (your tuned values)
const int RIGHT_SPEED = 186;
const int LEFT_SPEED  = 180;

// Sharp turn: right side stopped, left side drives
const int TURN_RIGHT_SPEED = 0;
const int TURN_LEFT_SPEED  = 180;

// Times in milliseconds
const int FORWARD_TIME = 200;  // about 20 cm (estimate)
const int TURN_TIME    = 460;  // Changed: was 500
const int PAUSE_TIME   = 300;  // short stop between moves

void rotateMotor(int rightSpeed, int leftSpeed) {
  ledcWrite(RPWM_Right, max(rightSpeed, 0));
  ledcWrite(LPWM_Right, max(-rightSpeed, 0));

  ledcWrite(RPWM_Left, max(leftSpeed, 0));
  ledcWrite(LPWM_Left, max(-leftSpeed, 0));
}

void stopMotors() {
  rotateMotor(0, 0);
}

void goForward() {
  rotateMotor(RIGHT_SPEED, LEFT_SPEED);
  delay(FORWARD_TIME);
  stopMotors();
  delay(PAUSE_TIME);
}

void sharpTurnRight() {
  rotateMotor(TURN_RIGHT_SPEED, TURN_LEFT_SPEED);
  delay(TURN_TIME);
  stopMotors();
  delay(PAUSE_TIME);
}

void setup() {
  Serial.begin(115200);

  ledcAttach(RPWM_Right, PWMFreq, PWMResolution);
  ledcAttach(LPWM_Right, PWMFreq, PWMResolution);
  ledcAttach(RPWM_Left, PWMFreq, PWMResolution);
  ledcAttach(LPWM_Left, PWMFreq, PWMResolution);

  delay(3000);  // time to step back

  Serial.println("Forward 1");
  goForward();

  Serial.println("Sharp turn 1");
  sharpTurnRight();

  Serial.println("Forward 2");
  goForward();

  Serial.println("Sharp turn 2");
  sharpTurnRight();

  Serial.println("Done");
}

void loop() {}