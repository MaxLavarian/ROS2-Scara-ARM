import rclpy
from rclpy.node import Node
import serial
import threading

from std_msgs.msg import String

class ArduinoSerialSubscriber(Node):
    def __init__(self):
        super().__init__('arduino_serial_subscriber')

        # Configurazione della porta seriale
        self.serial_port = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
        self.get_logger().info('Aperta porta seriale su /dev/ttyUSB0')

        # Publisher per topic di tipo String
        self.publisher_ = self.create_publisher(String, 'arduino_data', 10)

        # Avvia lettura in un thread separato
        self.running = True
        self.read_thread = threading.Thread(target=self.read_serial)
        self.read_thread.start()

    def read_serial(self):
        while self.running:
            try:
                line = self.serial_port.readline().decode().strip()
                if line:
                    self.get_logger().info(f'Dato ricevuto: {line}')
                    
                    # Crea e pubblica il messaggio String
                    msg = String()
                    msg.data = line
                    self.publisher_.publish(msg)

            except Exception as e:
                self.get_logger().error(f'Errore nella lettura seriale: {e}')

    def destroy_node(self):
        self.running = False
        self.read_thread.join()
        self.serial_port.close()
        super().destroy_node()

def main(args=None):
    rclpy.init(args=args)
    node = ArduinoSerialSubscriber()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    node.destroy_node()
    rclpy.shutdown()
