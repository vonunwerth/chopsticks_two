#ifndef CHOPSTICKS_TWO_GENERIC_HW_INTERFACE_H
#define CHOPSTICKS_TWO_GENERIC_HW_INTERFACE_H

#include <ros_control_boilerplate/generic_hw_interface.h> //TODO integrate generic_hw_interface.h, control_loop in the driver
#include <chopsticks_two_driver/armCmd.h>
#include <chopsticks_two_driver/chopsticksTwoTelemetry.h>
#include <std_msgs/Float64.h> //TODO only for 1 joint!!! otherwise Float64MultiArray have to be used

namespace chopsticks_two_ns
{
/** \brief Hardware interface for a robot */
class chopsticks_twoHWInterface : public ros_control_boilerplate::GenericHWInterface //Inherit from the boilerplate class
    {
    public:
        /**
         * \brief Constructor
         * \param nh - Node handle for topics.
         */
        chopsticks_twoHWInterface(ros::NodeHandle& nh, urdf::Model* urdf_model = NULL);

        /** \brief Initialize the robot hardware interface */
        virtual void init();

        /** \brief Read the state from the robot hardware. */
        virtual void read(ros::Duration& elapsed_time);

        /** \brief Write the command to the robot hardware. */
        virtual void write(ros::Duration& elapsed_time); //TODO set joint limits of the servos to 0-180deg

        /** \breif Enforce limits for all values before writing */
        virtual void enforceLimits(ros::Duration& period);

    protected:
        ros::Subscriber telemetry_sub;
        //void telemetryCallback(const chopsticks_two_driver::chopsticks_twoTelemetry::ConstPtr &msg);
        void telemetryCallback(const std_msgs::Float64 &msg);

        ros::Publisher cmd_pub;

    };  // class

}

#endif
