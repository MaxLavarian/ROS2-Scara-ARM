import rclpy
from rclpy.node import Node
from std_msgs.msg import Int32MultiArray
import serial

class MultiStepperSerialPublisher(Node):
    def __init__(self):
        super().__init__('multi_stepper_serial_publisher')

        # Porta seriale verso Arduino (modifica se diverso!)
        self.ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)

        # Sottoscrizione al topic
        self.subscription = self.create_subscription(
            Int32MultiArray,
            'motori_target',
            self.listener_callback,
            10
        )

    def listener_callback(self, msg):
        if len(msg.data) != 5:
            self.get_logger().warn(' Il messaggio deve contenere 5 valori (uno per ogni motore)')
            return

        # Crea stringa seriale: "val1 val2 val3\n"
        serial_msg = f"{msg.data[0]} {msg.data[1]} {msg.data[2]} {msg.data[3]} {msg.data[4]}\n"
        self.ser.write(serial_msg.encode())
        self.get_logger().info(f' Inviato ad Arduino: {serial_msg.strip()}')

def main(args=None):
    rclpy.init(args=args)
    node = MultiStepperSerialPublisher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
