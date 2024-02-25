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
## Creating a ROS2 Package
- Navigate to the `workspace/src` directory
    ```
    cd ros2_ws/src
    ```
* Create package using `ros2 pkg create` command
    + Python Package
        ```
        ros2 pkg create package_name --build-type ament_python --dependencies rclpy

        ```
    + C++ Package
        ```
        ros2 pkg create package_name --build-type ament_cmake --dependencies rclcpp
        ```
## Node
- Node &rarr; a subpart of the application with a single purpose
-  Application will contain many nodes, will be wrapped in a package
- Nodes can communicate each other through `topics`, `services`, and `parameters`
- Running a node using `ros2 run` command
    ```
    ros2 run package_name executable_node_name
    ```
    For example (running the `py_node` node in `my_python_pkg` package):
    ```
    ros2 run my_python_pkg py_node
    ```
- Rename node at runtime (safe way to launch same node multiple times) using `--ros-args`
    ```
    ros2 run my_python_pkg py_node --ros-args --remap __node:=new_py_node
    ```
## Topic
- A named bus over which nodes exchange messages
- Often used when a data stream is needed, especially unidirectional data stream (publisher/subscriber)
- Has a message type that must be the same for publishers and subscribers to communicate within the topic
