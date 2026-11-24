// v00 - Base code: motor setup + straight-drive tuning
// Source: "WORKING BASE CODE" section of PREV.md
// Note: PREV.md did not include loop(); an empty loop() was added so it compiles.

const int RPWM_Right = 23;
const int LPWM_Right = 22;
const int RPWM_Left  = 25;
const int LPWM_Left  = 21;

const int PWMFreq = 1000;
const int PWMResolution = 8;

// Tuned so the robot drives straight
const int RIGHT_SPEED = 186;
const int LEFT_SPEED  = 180;

void rotateMotor(int rightSpeed, int leftSpeed) {
  // Right side
  ledcWrite(RPWM_Right, max(rightSpeed, 0));
  ledcWrite(LPWM_Right, max(-rightSpeed, 0));

  // Left side
  ledcWrite(RPWM_Left, max(leftSpeed, 0));
  ledcWrite(LPWM_Left, max(-leftSpeed, 0));
}

void stopMotors() {
  rotateMotor(0, 0);
}

void setup() {
  ledcAttach(RPWM_Right, PWMFreq, PWMResolution);
  ledcAttach(LPWM_Right, PWMFreq, PWMResolution);
  ledcAttach(RPWM_Left, PWMFreq, PWMResolution);
  ledcAttach(LPWM_Left, PWMFreq, PWMResolution);
}

void loop() {}
