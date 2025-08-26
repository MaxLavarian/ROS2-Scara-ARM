import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy
from std_msgs.msg import Int32MultiArray

class MultiStepperSerialPublisher(Node):
    def __init__(self):
        super().__init__('motori_target')

        self.sub_joy = self.create_subscription(Joy, '/joy', self.joy_callback, 10)
        self.pub_array = self.create_publisher(Int32MultiArray, '/motori_target', 10)

        # Stato interno del messaggio (5 elementi)
        self.state = [0, 0, 0, 0, 0]

        self.get_logger().info(" Nodo joy  multi_stepper_serial avviato.")

    def joy_callback(self, msg: Joy):
        updated = False

        # axis[0] = sinistra/destra → elemento 0
        if msg.axes[0] > 0.5:
            self.state[0] += 100
            updated = True
        elif msg.axes[0] < -0.5:
            self.state[0] -= 100
            updated = True

        # axis[1] = avanti/indietro → elemento 1
        if msg.axes[1] > 0.5:
            self.state[1] += 100
            updated = True
        elif msg.axes[1] < -0.5:
            self.state[1] -= 100
            updated = True

        # button 4 → +400 a elemento 2
        if msg.buttons[4] == 1:
            self.state[2] += 400
            updated = True

        # button 5 → -400 a elemento 2
        if msg.buttons[5] == 1:
            self.state[2] -= 400
            updated = True

        # button 0 → imposta 1 a elemento 3
        if msg.buttons[0] == 1:
            self.state[3] = 1
            updated = True

        # button 1 → imposta 0 a elemento 3
        if msg.buttons[1] == 1:
            self.state[3] = 0
            updated = True

        # button 3 → imposta 1 a elemento 4
        if msg.buttons[3] == 1:
            self.state[4] = 1
            updated = True

        # button 2 → imposta 0 a elemento 4
        if msg.buttons[2] == 1:
            self.state[4] = 0
            updated = True

        if updated:
            array_msg = Int32MultiArray(data=self.state)
            self.pub_array.publish(array_msg)
            self.get_logger().info(f" Pubblicato: {self.state}")

def main(args=None):
    rclpy.init(args=args)
    node = MultiStepperSerialPublisher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
