# Repository for chopsticks_two robotic arm.

### chopsticks_two_description
URDF description of the robotic arm, mesh files and a launch file to visualize the arm in RVIZ

### chopsticks_two_driver
ros_control hardware interface for six motors, commanded via self defined messages. Launch file to launch everything needed to control the real arm, including a rosserial node, which communicates with an Arduino as interface to the motor hardware. The Arduino provides a Subscriber for the motor command topic and publishes the current motor states. The package also provides a configuration file for the controllers.

The template boilerplate code for the driver package can be found [here](https://github.com/PickNikRobotics/ros_control_boilerplate). The whole code of the chopsticks_two_driver is derived from this package.

### ros_control_boilerplate
A simplified version of the boilerplat code from [here](https://github.com/PickNikRobotics/ros_control_boilerplate). Still needed for the driver to run. Will be embedded in the driver in later versions.

### chopsticks_two_moveit_config
MoveIt! configuration package created by the moveit_setup_assistant. Sets up everything regarding motion control of the robot.

### sirius_rover
No ROS package! The Arduino code, which provides the real control of the motor hardware.
