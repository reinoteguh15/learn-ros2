#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/msg/led_state_array.hpp"
#include "my_robot_interfaces/srv/set_led.hpp"

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

        // Create a service to set the state of a specific LED
        set_led_service_ = this->create_service<my_robot_interfaces::srv::SetLed>(
            "set_led",
            std::bind(&LedPanelNode::callbackSetLed, this, _1, _2)
        );

        RCLCPP_INFO(this->get_logger(), "LED panel node has been started");
    }
private:
    void publishLedStates()
    {
        auto message = my_robot_interfaces::msg::LedStateArray();
        message.led_states = led_states_;
        led_states_publisher_->publish(message);
    }

    void callbackSetLed(const my_robot_interfaces::srv::SetLed::Request::SharedPtr request,
                        const my_robot_interfaces::srv::SetLed::Response::SharedPtr response)
    {
        int64_t led_number = request->led_number;
        int64_t led_state = request->led_state;

        // Validate the led_number and led_state
        if (led_number >= (int64_t)led_states_.size() || led_number < 0)
        {
            response->success = false;
            return;
        }

        if (led_state != 0 && led_state != 1)
        {
            response->success = false;
            return;
        }

        led_states_[led_number] = led_state;
        response->success = true;
        publishLedStates(); // Publish the updated LED states immediately after a change
    }

    std::vector<int64_t> led_states_;
    rclcpp::Publisher<my_robot_interfaces::msg::LedStateArray>::SharedPtr led_states_publisher_;
    rclcpp::TimerBase::SharedPtr led_states_timer_;
    rclcpp::Service<my_robot_interfaces::srv::SetLed>::SharedPtr set_led_service_;
}; 

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LedPanelNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}