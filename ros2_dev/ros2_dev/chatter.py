import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import datetime

class ChatterPublisher(Node):
    def __init__(self):
        super().__init__('chatter_publisher')
        self.publisher_ = self.create_publisher(String, 'chatter', 10)
        self.timer = self.create_timer(1.0, self.timer_callback)  # ogni 1 secondo
        self.count = 0

    def timer_callback(self):
        now = datetime.datetime.now().strftime("%H:%M:%S")
        msg = String()
        msg.data = f"Ciao dal publisher ROS2! [{self.count}] alle {now}"
        self.publisher_.publish(msg)
        self.get_logger().info(f'📤 Messaggio pubblicato: "{msg.data}"')
        self.count += 1

def main(args=None):
    rclpy.init(args=args)
    node = ChatterPublisher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
