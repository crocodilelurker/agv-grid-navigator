// v04 - Check 90 degree spin turns as SEPARATE moves (right and left)
// Changed from v03:
//  - SPIN_TIME split into SPIN_RIGHT_TIME and SPIN_LEFT_TIME = 238 ms (950 / 4)
//  - New spinLeft() function (mirror of spinRight)
//  - Test does 4 separate right spins, waits 3 s, then 4 separate left spins
// Expected: after the 4 rights the robot faces the start direction again,
//           and after the 4 lefts it faces the start direction again.

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

// Spin turns - v03: one continuous 950 ms spin = 360 degrees
const int SPIN_SPEED      = 180;
const int SPIN_RIGHT_TIME = 238;  // testing: 90 degrees right
const int SPIN_LEFT_TIME  = 238;  // testing: 90 degrees left

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
  // Right side backward, left side forward
  rotateMotor(-SPIN_SPEED, SPIN_SPEED);
  delay(SPIN_RIGHT_TIME);
  stopMotors();
  delay(PAUSE_TIME);
}

void spinLeft() {
  // Right side forward, left side backward
  rotateMotor(SPIN_SPEED, -SPIN_SPEED);
  delay(SPIN_LEFT_TIME);
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

  for (int i = 1; i <= 4; i++) {
    Serial.print("Spin right ");
    Serial.println(i);
    spinRight();
  }

  Serial.println("Check: facing start direction? Waiting 3 s...");
  delay(3000);

  for (int i = 1; i <= 4; i++) {
    Serial.print("Spin left ");
    Serial.println(i);
    spinLeft();
  }

  Serial.println("Done");
}

void loop() {}
