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
- Rename topic at runtime (topic remapping)
    ```
    ros2 run package_name executable_name --ros-args -r topic_name:=new_topic_name
    ```
  For example:
    ```
    ros2 run my_python_pkg robot_news_station --ros-args -r robot_news:=news_station
    ```
  ⚠️ Don't forget to also remap the topic name on subscriber

## Services
- Client/server system
- Can be either synchronous or asynchronous
- Defined as a name and a pair of messages (1 message type for Request, 1 message type of Response)
- Service server can only exist once but can have many clients
- Initializing a service:
    ```python
    from rclpy.node import Node
    
    node = Node("node_name")
    server = node.create_service(srv_type, srv_name, callback)
    ```
- Initializing a service client:
    ```python
    from rclpy.node import Node

    node = Node("node_name")
    client = node.create_client(srv_type, srv_name)

    # request = ....

    future = client.call_async(request)
    rclpy.spin_until_future_complete(node, future)

    ```
- Remap a service at runtime
    ```
    ros2 run package_name executable_name --ros-args -r service_name:=new_service_name
    ```
  For example:
    ```
    ros2 run my_cpp_pkg add_two_ints_server --ros-args -r add_two_ints:=new_name
    ```

## Interfaces
- Define the data structures and communication contracts
- Used by nodes to exchange information accross topics, services, and actions
- Use **Interface Definition Language (IDL)** files such as `.msg`, `.srv`, and `.action` to generate source code accross supported languages
- In topics:
    ```
    {
        name, --> ex: /number_count
        msg_definition --> ex: example_interfaces/msg/Int64
    }
    ```
- In services:
    ```
    {
        name, --> ex: /reset_number_count
        srv_definition --> ex: example_interfaces/srv/SetBool
    }
    ```
- Topics and Services act as the **communication layer tool**, Interfaces is the **actual content** being sent