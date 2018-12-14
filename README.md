Skeleton Tracking Based on Kinect Sensor V2
===========================================

This work is to realize communication between Windows and Ubuntu to interact skeleton tracking data. Windows's advantage is that its kinect application is easily to install, and it has powerful Kinect SDK to get and process skeleton tracking data directly. Ubuntus's advantage is that it support ROS, and can make robotics system access these data. All of these inspired me to combine these two system, and provide a basis for roboticists to do further work on skeleton tracking.

For this repository, `Kinect_V2` is folder should only run on Windows, `kinect_v2` is folder should only run on Ubuntu.

**note: Before everything starting, make sure your Windows and Ubuntu both connect to the same local network to secure the communication between their ROS clients. And also make sure to plugin Kinect Sensor V2 to USB3.0 port on your windows computer.
    
### Windows
1. Download and install Kinect for Windows SDK 2.0
    
    The download page is [here](https://www.microsoft.com/en-us/download/details.aspx?id=44561).
    
2. Verify the successful installation in Device Manager.

3. Open `Kinect v2`, and then install `Kinect Configuration Verifier` to check the success of installation.

### Ubuntu
1. Clone the kinect v2 repository to your ROS workspace and do catkin_make
    ```bash
    cd ~/catkin_ws/src
    git clone git@github.com:msr-peng/kinect_v2_skeleton_tracking.git
    cd kinect_v2_skeleton_tracking && sudo cp -r kinect_v2 ../ && cd ..
    rm -r kinect_v2_skeleton_tracking
    cd .. && catkin_make

2. Get your Ubuntu IP address in local network
    ```bash
    ifconfig
    ```
    Then you should get the IP address behind "inet addr:"

3. Start ROS and rosserial_server
    In order for rosserial_windows to communicate with the ROS master, a server socket is needed to connect. Now I just uses a TCP socket, but in theory it is also possible to sue a serial port. On the ROS master, start the ROS core:
    ```bash
    roscore
    ```
    In a separate terminal, start the rosserial server:
    ```bash
    rosrun rosserial_server socket_node
    ```
    Then go back to your windows machine and run the app.

### Windows
1. Clone the repository, and enter into Kinect_V2 folder

2. Set Ubuntu IP address in Windows app
    Go to `Kinect_V2.cpp` source file, find line
        char master_uri[] = "192.168.0.104";
    Then replace the string with your Ubuntu IP address your just got.

3. Run Kinect_V2 solution in Visual Studio
    Then windows should send skeleton tracking data to Ubuntu.

### Ubuntu
1. Process skeleton tracking data, publish them as `TF` forms
    ```bash
    rosrun kinect_v2 show_joint
    ```

2. Visualize skeleton tracking data on `Rviz` (basic frame is `/kinect_v2`)
    ```bash
    rosrun rviz rviz -f kinect_v2
    ```
    Then in `Rviz`, add `TF` to display, you should see the frames of skeleton keypoints.
