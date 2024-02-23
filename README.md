# Learn ROS2
Documentation of learning ROS2 with the distro Humble

## Creating a ROS2 workspace
- Navigate to the project directory, then make a folder for the workspace
```
cd project_dir/
mkdir ros2_ws
```
- Navigate to the workspace, create a `src` folder for all the script in the workspace
```
cd ros2_ws
mkdir src
```
- Build the workspace
```
cd ros2_ws
colcon build
```