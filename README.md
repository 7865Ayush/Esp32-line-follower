

# ESP32-Based Line Follower Robot

An autonomous line-following robot built using an ESP32 microcontroller and an 8-channel IR sensor array.

## Project Overview

The robot detects and follows a predefined path using infrared sensors. The ESP32 processes the sensor outputs and controls the motor speeds to adjust the robot's direction and maintain line tracking.


## Hardware Components

- ESP32 development board
- 8-channel IR sensor array with adjustable sensors
- L298N dual H-bridge motor driver
- 2 DC geared motors
- 2 robot wheels
- Robot chassis
- 2 × 18650 lithium-ion battery cells
- Dual-cell battery holder
- Jumper wires and connecting cables
- USB cable for programming the ESP32



## My Contributions

- Assembled the robot and integrated the electronic components.

- Performed soldering and hardware connections.

- Worked on adjusting the control code to regulate motor speed and turning behaviour.

- Tested the robot to improve its movement and line-following performance.

## Working Principle

1. The IR sensor array detects the line on the surface.

2. The ESP32 reads the sensor outputs.

3. The controller determines the line position and calculates steering corrections.

4. The motor driver adjusts the motor speeds to steer the robot.

5. This process repeats continuously to follow the path
