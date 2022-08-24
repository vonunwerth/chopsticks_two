//Wiring
// BLACK/BROWN: GND
// RED: +5V
// WHITE/YELLOW/ORANGE: SIGNAL

//To start it run
//roscore
//rosrun rosserial_arduino serial_node.py 

#include <Servo.h>
#include <ros.h>
#include <chopsticks_two_driver/chopsticksTwoTelemetry.h>
#include <chopsticks_two_driver/armCmd.h>

Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

ros::NodeHandle  nh;
float joint_angles[6];

void messageCb(const chopsticks_two_driver::armCmd &msg){
  servo0.write(msg.angle[0] * 180 / M_PI);
  servo1.write(msg.angle[1] * 180 / M_PI);
  servo2.write(msg.angle[2] * 180 / M_PI);
  servo3.write(msg.angle[3] * 180 / M_PI);
  servo4.write(msg.angle[4] * 180 / M_PI);
  servo5.write(msg.angle[5] * 180 / M_PI);
  for (int i = 0; i < 6; i++) {
    joint_angles[i] = msg.angle[i];
  }
}

ros::Subscriber<chopsticks_two_driver::armCmd> sub("armCmd", messageCb );
chopsticks_two_driver::chopsticksTwoTelemetry telemetry;
ros::Publisher telemetry_pub("chopsticks_two_telemetry", &telemetry);

void setup()
{
  servo0.attach(7);
  servo1.attach(8);
  servo2.attach(13);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
  for (int i = 0; i < 6; i++) {
    joint_angles[i] = 0; 
  }
  nh.initNode();
  nh.advertise(telemetry_pub);
  nh.subscribe(sub);
}

void loop()
{
  for (int i = 0; i < 6; i++) {
    telemetry.angle[i] = joint_angles[i];
  }
  telemetry_pub.publish(&telemetry);
  nh.spinOnce();
  delay(1);
}
