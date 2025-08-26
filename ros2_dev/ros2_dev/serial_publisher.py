import rclpy
from rclpy.node import Node
from std_msgs.msg import Int16
import serial

class SerialPublisher(Node):
    def __init__(self):
        super().__init__('serial_publisher')

        # Modifica questo con il tuo device, es: /dev/ttyACM0 o /dev/ttyUSB0
        self.ser = serial.Serial('/dev/ttyUSB0', 115200)

        # Topic ROS2 da cui ricevere comandi
        self.subscription = self.create_subscription(
            Int16,
            'arduino_command',
            self.listener_callback,
            10
        )

    def listener_callback(self, msg):
        comando = str(msg.data)
        self.get_logger().info(f'Inviando a seriale: {comando}')
        self.ser.write(comando.encode())  # invia singolo carattere o numero

def main(args=None):
    rclpy.init(args=args)
    node = SerialPublisher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
