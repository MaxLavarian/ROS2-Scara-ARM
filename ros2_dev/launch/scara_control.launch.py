from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='joy',
            executable='joy_node',
            name='joy_node',
            output='screen'
        ),
        Node(
            package='ros2_dev',
            executable='scara_serial_subscriber',
            name='scara_serial_subscriber',
            output='screen'
        ),
        Node(
            package='ros2_dev',
            executable='joy_scara_publisher',
            name='joy_scara_publisher',
            output='screen'
        ),
    ])
