from setuptools import find_packages, setup
import os
from glob import glob

package_name = 'ros2_dev'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',   ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.launch.py')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='max',
    maintainer_email='max@todo.todo',
    description='TODO: Package description',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
                'publisher_node = ros2_dev.publisher:main',
                'subscriber_node = ros2_dev.subscriber:main',
                'chatter_node = ros2_dev.chatter:main',
                'serial_publisher_node = ros2_dev.serial_publisher:main',
                'scara_serial_subscriber = ros2_dev.serial_scara_subscriber:main',
                'joy_scara_publisher = ros2_dev.joy_scara_publisher:main',
                'arduino_serial_subscriber = ros2_dev.arduino_serial_subscriber:main',
        ],
    },
)