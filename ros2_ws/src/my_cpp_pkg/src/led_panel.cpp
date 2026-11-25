#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/msg/led_state_array.hpp"

using namespace std::placeholders;
using namespace std::chrono_literals;

class LedPanelNode : public rclcpp::Node
{
public:
    LedPanelNode() : Node("led_panel_node"), led_states_(3, 0)
    {
        // Create a publisher for the LED states
        led_states_publisher_ = this->create_publisher<my_robot_interfaces::msg::LedStateArray>("led_panel_state", 10);

        // Create a timer to publish the LED states at a regular interval (i.e. 5 seconds)
        led_states_timer_ = this->create_wall_timer(5s, std::bind(&LedPanelNode::publishLedStates, this));

        RCLCPP_INFO(this->get_logger(), "LED panel node has been started");
    }
private:
    void publishLedStates()
    {
        auto message = my_robot_interfaces::msg::LedStateArray();
        message.led_states = led_states_;
        led_states_publisher_->publish(message);
    }


    std::vector<int64_t> led_states_;
    rclcpp::Publisher<my_robot_interfaces::msg::LedStateArray>::SharedPtr led_states_publisher_;
    rclcpp::TimerBase::SharedPtr led_states_timer_;
}; 

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LedPanelNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}