# sirius_servo
Arduino project to interface six servo motors of a robotic arm via rosserial.

### Wiring
Servo motors must be connected to the pins **4, 5, 6, 7, 8, 13**. *VCC* of the Arduino is not enough. You need to connect the motors to its own power supply. Connect *GND* of the Arduino to the *GND* you are using for the motors.

Servo wiring:
|   GND     |   BLACK         | BROWN |
| +5V      | RED |  |
|  SIGNAL     | YELLOW      | ORANGE  |

### Installation
Upload the *chopsticks_two_servo* sketch to an Arduino. Don't use Arduino IDE Version 2! As *rosserial* and self defined *message types* are used, some things need to be prepared first. 

1. *rosserial* has to be [installed](http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup)*

2. As described in the tutorial from step 1, the *ros_lib* library must be created. Make sure your workspace contains the *chopsticks_two_driver* package with its messages and that you source the ```setup.bash``` from your workspace. Then run ```rosrun rosserial_arduino make_libraries.py .``` inside of the *libraries* folder of your Arduino workspace.

3. Check if you can access the *ros_lib* examples in the Arduino IDE. Also check if the generated *ros_lib* folder contains a folder *chopsticks_two_driver. There should be *.h* files for the message types from the driver package.

### Usage
After uploading the sketch to an Arduino, you could run ```roscore``` and in an other terminal ```rosrun rosserial_arduino serial_node.py _port:=/dev/ttyUSB0``` to connect "ROS" running on the Arduino to your *roscore*.

Run ```rostopic list```. You should now see a topic to command the motors called */armCmd* and a topic published by the Arduino with the current motor states called *chopsticks_two_telemetry*. This can be published and subscribed manually or will be used by the *chopsticks_two_driver*.

### Implementation
The Arduino subscribes to the *armCmd* topic, which includes six radian values for all six motors. Each time a new message appears on that topic, the servos will be commanded to move to the new values and the ```joint_angles``` array will be updated. This variable will be published via the *chopsticks_two_telemetry* topic.


### Troubleshooting
##### Tried to publish before configured, topic id 125
Check out that Github [issue](https://github.com/ros-drivers/rosserial/issues/63). Maybe it could help.
