// v03 - Calibrate SPIN turn right 90 degrees
// Changed from v02: forward move removed, new spinRight() function.
// Spin turn = left side forward, right side backward, so the robot
// turns on the spot and stays in the centre of its grid cell.

const int RPWM_Right = 23;
const int LPWM_Right = 22;
const int RPWM_Left  = 25;
const int LPWM_Left  = 21;

const int PWMFreq = 1000;
const int PWMResolution = 8;

// Straight driving (your tuned values)
const int RIGHT_SPEED = 186;
const int LEFT_SPEED  = 180;

// One grid cell (30 cm) - confirmed in v02
const int CELL_TIME  = 300;
const int PAUSE_TIME = 300;  // short stop between moves

// Spin turn - this is what we are testing
const int SPIN_SPEED = 180;  // both sides use this speed
const int SPIN_TIME  = 250;  // first guess for 90 degrees

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

void spinRight() {
  // Right side backward (negative), left side forward (positive)
  rotateMotor(-SPIN_SPEED, SPIN_SPEED);
  delay(SPIN_TIME);
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

  Serial.println("Spin right 90");
  spinRight();

  Serial.println("Done");
}

void loop() {}
