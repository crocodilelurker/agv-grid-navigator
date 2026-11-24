// v02 - Calibrate ONE grid cell (30 cm) forward
// Changed from v01: turns removed, single forward move, CELL_TIME = 300 ms

const int RPWM_Right = 23;
const int LPWM_Right = 22;
const int RPWM_Left  = 25;
const int LPWM_Left  = 21;

const int PWMFreq = 1000;
const int PWMResolution = 8;

// Straight driving (your tuned values)
const int RIGHT_SPEED = 186;
const int LEFT_SPEED  = 180;

// Time to move ONE cell (30 cm) - this is what we are testing
const int CELL_TIME  = 300;
const int PAUSE_TIME = 300;  // short stop after the move

void rotateMotor(int rightSpeed, int leftSpeed) {
  ledcWrite(RPWM_Right, max(rightSpeed, 0));
  ledcWrite(LPWM_Right, max(-rightSpeed, 0));

  ledcWrite(RPWM_Left, max(leftSpeed, 0));
  ledcWrite(LPWM_Left, max(-leftSpeed, 0));
}

void stopMotors() {
  rotateMotor(0, 0);
}

void goForwardOneCell() {
  rotateMotor(RIGHT_SPEED, LEFT_SPEED);
  delay(CELL_TIME);
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

  Serial.println("Forward 1 cell");
  goForwardOneCell();

  Serial.println("Done");
}

void loop() {}
