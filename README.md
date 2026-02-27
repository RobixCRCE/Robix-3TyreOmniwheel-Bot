# Robix-3TyreOmniwheel-Bot

Overview:
This project implements a 3-wheel omni-directional robot using an ESP32 and two L298N motor drivers. The robot supports forward, backward, lateral (strafe), and rotational movement via Bluetooth commands.
The omni wheels are arranged 120° apart, enabling full holonomic motion.

Hardware Requirements:
ESP32 Dev Module
2 × L298N motor drivers
3 × DC motors with omni wheels
External motor power supply
Chassis (120° wheel placement)
Bluetooth terminal app (Android recommended)

Bluetooth Configuration:
Device Name: RobixOmniwheelBot
Communication: Classic Bluetooth (SPP)
Baud Rate (Serial Monitor): 115200
Connect via a Bluetooth terminal and send single-character commands.

Pin Configuration:
Motor 1 (L298N #1)
IN1 → GPIO 14
IN2 → GPIO 26
Motor 2 (L298N #1)
IN1 → GPIO 33
IN2 → GPIO 32
Motor 3 (L298N #2)
IN1 → GPIO 13
IN2 → GPIO 12

Note: Enable pins of L298N should be tied HIGH or connected to PWM if speed control is required.

Control Commands:
Command	Action
F	Move Forward
B	Move Backward
L	Strafe Left
R	Strafe Right
C	Rotate Clockwise
A	Rotate Anti-Clockwise
S	Stop

Working Principle:
The robot uses 3-wheel omni kinematics:
vx → Forward/Backward motion
vy → Left/Right strafing
w → Rotation

Motor velocity equations:
M1 = (-0.5 × vx) + (0.866 × vy) + w
M2 = (-0.5 × vx) - (0.866 × vy) + w
M3 = (1.0 × vx) + w

Motor direction is determined by the sign of computed velocity. Current implementation runs motors at full speed (direction only control).

Features:
Holonomic motion (move in any direction)
Independent rotation without translation
Bluetooth real-time control
Clean kinematic implementation
Add gyro-based heading correction

Add mecanum-style smooth vector normalization
