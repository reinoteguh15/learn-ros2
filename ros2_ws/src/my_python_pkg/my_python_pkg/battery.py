#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from my_robot_interfaces.srv import SetLed

class BatteryNode(Node):
    def __init__(self):
        super().__init__("battery")
        self.battery_state_ = "full"
        self.last_time_battery_sate_changed_ = self.get_current_time_seconds()
        self.battery_timer_ = self.create_timer(0.1, self.check_battery_state)
        self.set_led_client_ = self.create_client(SetLed, 'set_led')
        self.get_logger().info("Battery Node has been started...")

    def get_current_time_seconds(self):
        seconds, nanoseconds = self.get_clock().now().seconds_nanoseconds()
        return seconds + nanoseconds / 1000000000.0

    def check_battery_state(self):
        time_now = self.get_current_time_seconds()
        if self.battery_state_ == "full":
            if time_now - self.last_time_battery_sate_changed_ > 4.0:  # Example condition
                self.battery_state_ = "empty"
                self.get_logger().info("Battery is empty! Charging...")
                self.call_set_led(2, 1)
                self.last_time_battery_sate_changed_ = time_now
        elif self.battery_state_ == "empty":
            if time_now - self.last_time_battery_sate_changed_ > 6.0:  # Example condition
                self.battery_state_ = "full"
                self.get_logger().info("Battery is full!")
                self.call_set_led(2, 0)
                self.last_time_battery_sate_changed_ = time_now

    def call_set_led(self, led_number, state):
        while not self.set_led_client_.wait_for_service(timeout_sec=1.0):
            self.get_logger().warn('Waiting for set_led service...')  

        req = SetLed.Request()
        req.led_number = led_number
        req.led_state = state

        future = self.set_led_client_.call_async(req)
        future.add_done_callback(self.callback_call_set_led)

    def callback_call_set_led(self, future):
        response: SetLed.Response = future.result()
        if response.success:
            self.get_logger().info("LED state changed")
        else:
            self.get_logger().info("LED not changed")

def main(args=None):
    rclpy.init(args=args)
    node = BatteryNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()