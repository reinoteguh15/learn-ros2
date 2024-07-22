from setuptools import find_packages, setup

package_name = 'my_python_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='reino',
    maintainer_email='reinoteguhsts15@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "py_node = my_python_pkg.my_first_python_node:main",
            "robot_news_station = my_python_pkg.robot_news_station:main",
            "smartphone = my_python_pkg.smartphone:main",
            "number_publisher = my_python_pkg.number_publisher:main",
            "number_counter = my_python_pkg.number_counter:main",
            "add_two_ints_server = my_python_pkg.add_two_ints_server:main",
            "add_two_ints_client = my_python_pkg.add_two_ints_client:main",
            "add_two_ints_client_no_oop = my_python_pkg.add_two_ints_client_no_oop:main"
        ],
    },
)
