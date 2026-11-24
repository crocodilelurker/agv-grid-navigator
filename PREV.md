I am building a 4-wheel autonomous robot with an ESP32. I am a beginner in electronics and programming. Please help me program it for whatever I ask next, using the exact hardware and calibration details below.

=== HARDWARE ===
- ESP32 development board
- 4 DC motors (2 on the left, 2 on the right), 4-wheel chassis
- 2 BTS7960 motor drivers (one for the left side, one for the right side)
- Battery supply
- Common ground between the ESP32 and both motor drivers
- No sensors, no encoders. Movement is controlled by timing only.
- No phone, Wi-Fi, or Bluetooth control. The robot must work autonomously.

=== PIN CONNECTIONS ===
- Right BTS7960: RPWM = GPIO 23, LPWM = GPIO 22
- Left BTS7960: RPWM = GPIO 25, LPWM = GPIO 21
- Both drivers: R_EN and L_EN are connected to 3.3V

=== SOFTWARE ===
- Arduino IDE with ESP32 Arduino Core 3.x
- PWM is set up with ledcAttach(pin, PWMFreq, PWMResolution)
- PWMFreq = 1000 Hz, PWMResolution = 8 bits (speed values 0-255)

=== WORKING BASE CODE (tested and confirmed) ===
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

How rotateMotor(rightSpeed, leftSpeed) works:
- Positive value = that side drives the robot forward.
- Negative value = that side drives backward.
- 0 = that side stops.
- Max is 255.

=== WHAT WE LEARNED (history) ===
1. My original code reversed the right side in software. With that, the robot spun on the spot clockwise when I called rotateMotor(180, 180). The fix was removing the reversal, so positive values now mean forward on BOTH sides. This is already built into the code above.
2. With equal speeds (180, 180) the robot drifted slightly right. Setting RIGHT_SPEED = 186 and LEFT_SPEED = 180 made it go perfectly straight. Battery charge level may change this slightly, so the 186 may need small re-tuning.
3. A gentle curve (right = 100, left = 180) was written but I never reported how much it turned.
4. I now want SHARP turns, not curves. Plan: right side stopped (0), left side driving (180), so the robot pivots around its right wheels. I am willing to try a spin around the centre instead if needed.

=== DISTANCE CALIBRATION ===
- At speeds 186/180, driving for 150 ms moved the robot 14.5 cm (about 0.097 cm per ms).
- Estimates from that: 100 ms is about 10 cm, 200 ms is about 20 cm.
- These are estimates. Short runs are not perfectly proportional because of motor start-up delay and the robot rolling after it stops.
- Earlier I measured 309.66 cm for a 500 ms and a 100 ms run. This was never explained, and the later 150 ms test (14.5 cm) was realistic. Treat 309.66 as a measurement mistake or an old sketch running, not as real data.

=== NOT YET CONFIRMED (please help me test these, one at a time) ===
- The real distance for DRIVE_TIME = 100 ms and 200 ms (I have not reported the 100 ms result yet).
- TURN_TIME for a sharp 90 degree turn. The first guess is 500 ms with right = 0 and left = 180. I have not tested it.
- Whether a pause of 300 ms between moves is enough to stop the robot rolling.

=== MY GOAL RIGHT NOW ===
Move 20 cm straight, make a sharp 90 degree right turn, move 20 cm straight, make another sharp right turn, and stop. Repeat four times in total to complete a square.

=== CODE STRUCTURE I LIKE ===
Use small named functions such as goForward() and sharpTurnRight(), with the times stored in named constants (FORWARD_TIME, TURN_TIME, PAUSE_TIME) so I can tune them easily. Start with delay(3000) in setup() so I can step back, and print progress with Serial.println().

=== HOW I WANT YOU TO TEACH ME ===
- Use simple, beginner-friendly language.
- Give step-by-step instructions.
- Change only ONE thing at a time.
- Always give the complete code, ready to copy and paste.
- Explain what changed and why.
- Include safety steps (clear space, hand near the power switch).
- After each test, ask me for a specific result and WAIT for it before moving on.
- If a number I report looks wrong (for example impossibly fast), ask me to re-check it before using it.
- Do not give long unrelated explanations.
- Remember that without sensors, timing-based movement is only approximate. Tell me if a goal needs a sensor (encoder, gyroscope/MPU6050, ultrasonic) to be accurate.

=== WHAT I WANT TO BUILD NEXT ===
[Write your new idea here, for example: obstacle avoidance, line following, draw a shape, patrol in a rectangle.]