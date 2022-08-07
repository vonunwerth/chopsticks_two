#include <chopsticks_two_driver/chopsticks_two_hardware_interface.h>

namespace chopsticks_two_ns
{
    chopsticks_twoHWInterface::chopsticks_twoHWInterface(ros::NodeHandle& nh, urdf::Model* urdf_model)
            : GenericHWInterface(nh, urdf_model)
    {

        telemetry_sub = nh.subscribe("/chopsticks_two_telemetry", 1, &chopsticks_twoHWInterface::telemetryCallback, this);
        //cmd_pub = nh.advertise<chopsticks_two_driver::armCmd>("/armCmd", 1);
        cmd_pub = nh.advertise<std_msgs::Float64>("/armCmd", 1);
        ROS_INFO("chopsticks_twoHWInterface constructed. That's good!");
    }

    //void chopsticks_twoHWInterface::telemetryCallback(const chopsticks_two_driver::chopsticks_twoTelemetry::ConstPtr &msg) //TODO do own message type
    void chopsticks_twoHWInterface::telemetryCallback(const std_msgs::Float64 &msg)
    {
    for (int i = 0; i < num_joints_; i++) {
        joint_velocity_[i] = msg.data; //TODO neccassary?
        joint_position_[i] = msg.data; //TODO Each joint gets the same data
        //joint_position_[i] = msg->angle[i];//Fill here whatever comes from the message form the arduino
        //joint_velocity_[i] = msg->vel[i]; //joint_position and velocity requires rad and rad/sec
    }

    }

    void chopsticks_twoHWInterface::init()
    {
        // Call parent class version of this function
        GenericHWInterface::init(); //Looks at how many joints we are using based on the config file and then creates correct number of HWInterfaces
        ROS_INFO("chopsticks_twoHWInterface Ready.");
    }

    void chopsticks_twoHWInterface::read(ros::Duration& elapsed_time)
    {
        //Is called every control loop
        //Need a read from the robot hardware -> from serial for example
        // No need to read since our write() command populates our state for us
        ros::spinOnce(); //checks all callbacks TODO in arduino code state feedback is not implemented, will moveits current states stay at 0-config
    }

    void chopsticks_twoHWInterface::write(ros::Duration& elapsed_time)
    {
        //Writing to hardware

        //static chopsticks_two_driver::armCmd arm_cmd; //Only created once
        static std_msgs::Float64 armCmd;
        for (int i = 0; i < num_joints_; i++) {
            armCmd.data = joint_position_command_[i];
            //arm_cmd.vel[i] = joint_velocity_command_[i];
        }
        cmd_pub.publish(armCmd); //Publish the updates message
    }

    void chopsticks_twoHWInterface::enforceLimits(ros::Duration& period)
    {
        // Enforces position and velocity
        //pos_jnt_sat_interface_.enforceLimits(period);
    }

}
