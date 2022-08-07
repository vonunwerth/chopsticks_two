# Template für ros_control hardware_interface

### generic_hw_control_loop
We will use that control_loop. It just updates the control loop, reads, updates and writes

### generic_hw_interface
Is what we are here for. It's a generalized hardware_interface where we have to inherit from. Registers the important hardware_interfaces.

### sim_hw_interface
Example how to use the template

# Create own hardware_interface
1. Create new package -> <robot_name>_control