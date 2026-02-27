#include <Arduino.h>
#include <BluetoothSerial.h>

BluetoothSerial ESP_BT;  // Bluetooth object

// --- Motor pin mapping ---
// Motor 1 (on L298N #1)
#define M1_IN1 14
#define M1_IN2 26

// Motor 2 (on L298N #1)
#define M2_IN1 33
#define M2_IN2 32

// Motor 3 (on L298N #2)
#define M3_IN1 13
#define M3_IN2 12

// --- Motor control helper ---
void setMotor(int IN1, int IN2, int speed) {
  // speed > 0 → forward
  // speed < 0 → backward
  // speed = 0 → stop

  if (speed > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else if (speed < 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }
}

// --- Setup ---
void setup() {
  pinMode(M1_IN1, OUTPUT);
  pinMode(M1_IN2, OUTPUT);
  pinMode(M2_IN1, OUTPUT);
  pinMode(M2_IN2, OUTPUT);
  pinMode(M3_IN1, OUTPUT);
  pinMode(M3_IN2, OUTPUT);

  Serial.begin(115200);
  ESP_BT.begin("RobixOmniwheelBot"); // Bluetooth device name
  Serial.println("RobixOmniwheelBot Ready. Connect & send commands.");
}

// --- Omni kinematics ---
// vx = forward/backward
// vy = strafe left/right
// w  = rotation
void driveOmni(float vx, float vy, float w) {
  // 3-wheel omni base (120° apart)
  float m1 = (-0.5 * vx) + (0.866 * vy) + w;  // 120°
  float m2 = (-0.5 * vx) - (0.866 * vy) + w;  // 240°
  float m3 = (1.0 * vx) + w;                  // 0°

  // Convert to sign only (full speed control)
  int speed1 = (m1 > 0) ? 1 : (m1 < 0 ? -1 : 0);
  int speed2 = (m2 > 0) ? 1 : (m2 < 0 ? -1 : 0);
  int speed3 = (m3 > 0) ? 1 : (m3 < 0 ? -1 : 0);

  setMotor(M1_IN1, M1_IN2, speed1);
  setMotor(M2_IN1, M2_IN2, speed2);
  setMotor(M3_IN1, M3_IN2, speed3);
}

void loop() {
  if (ESP_BT.available()) {
    char cmd = ESP_BT.read();
    Serial.print("CMD: "); Serial.println(cmd);

    switch (cmd) {
      case 'F':  // Forward
        driveOmni(1.0, 0.0, 0.0);
        break;
      case 'B':  // Backward
        driveOmni(-1.0, 0.0, 0.0);
        break;
      case 'L':  // Strafe Left
        driveOmni(0.0, 1.0, 0.0);
        break;
      case 'R':  // Strafe Right
        driveOmni(0.0, -1.0, 0.0);
        break;
      case 'C':  // Rotate Clockwise
        driveOmni(0.0, 0.0, 1.0);
        break;
      case 'A':  // Rotate Anti-clockwise
        driveOmni(0.0, 0.0, -1.0);
        break;
      case 'S':  // Stop
      default:
        driveOmni(0.0, 0.0, 0.0);
        break;
    }
  }
}

