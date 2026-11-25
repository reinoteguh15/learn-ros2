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
### Create a custom interface:
  1. Create a new package only for `msg` and `srv` definitions (for example: `my_robot_interfaces`). T
    ```bash
    ros2 pkg create my_robot_interfaces 
    ```
  2. Remove the `include/` and `src/` folders, then add `msg/` or `srv/` folder. The structure will look like this
  ```
  my_robot_interfaces/
  ├── msg/
  |    ├── MessageInterface1.msg
  |    └── MessageInterface2.msg
  ├── srv/
  |    ├── ServiceInterface1.srv
  |    └── ServiceInterface2.srv
  ├── CMakeLists.txt
  └── package.xml
  ```

  3. Setup the package - `CMakeLists.txt` and `package.xml`
      - for `CMakeLists.txt` add this line
        ```
        find_package(rosidl_default_generators REQUIRED)
        
        rosidl_generate_interfaces(${PROJECT_NAME}
            "msg/MessageInterface1.msg"
            "msg/MessageInterface2.msg"
            "srv/ServiceInterface1.srv"
            "srv/ServiceInterface2.srv"
        )
        
        ament_export_dependencies(rosidl_default_runtime)
        ```
        
      - for `package.xml` add this line
        ```
        <buildtool_depend>rosidl_default_generators</buildtool_depend>
        <exec_depend>rosidl_default_runtime</exec_depend>
        <member_of_group>rosidl_interface_packages</member_of_group>
        ```

  4. Use the custom message interface in code:
      - python
        - import library
          ```
          from my_robot_interfaces.msg import MessageInterface1
          ```
        - add in `package.xml`
          ```
          <depend>my_robot_interfaces</depend>
          ```

      - cpp
        - import library
          ```
          #include "my_robot_interfaces/msg/MessageInterface2.hpp"
          ```
        - add in `package.xml`
          ```
          <depend>my_robot_interfaces</depend>
          ```
        - add in `CMakeLists.txt`
          ```
          find_package(my_robot_interfaces REQUIRED)
          ```
  5. Use the custom service interface in code:
      - python
        - import library
          ```
          from my_robot_interfaces.srv import ServiceInterface1
          ```

      - cpp
        - import library
          ```
          #include "my_robot_interfaces/srv/ServiceInterface2.hpp"
          ```