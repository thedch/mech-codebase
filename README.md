# Final Project Code

This repository holds the robot behavior state machine and sensor integration algorithms for the final project of CMPE 118, Mechatronics at UCSC. 

Additionally, it holds a test harness project that was used to ensure hardware functionality. 

The helper functions file on the top level is used throughout the project and test harness for two purposes:

Firstly, it ensures that all robot operations are uniform, and can be changed easily. Abstracting away specific PWM voltages or sensor I/O pins allows a hardware change to be reflected in the software quickly and accurately. 

Secondly, it allows for a "control panel" style robot interface when developing and debugging the state machine. Instead of both worrying about "am I accessing sensor data correctly" and "am I using sensor data correctly", the helper functions take care of the first worry and allow the developer to focus on the second.
