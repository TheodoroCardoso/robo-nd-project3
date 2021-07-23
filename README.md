[![Udacity - Robotics NanoDegree Program](https://s3-us-west-1.amazonaws.com/udacity-robotics/Extra+Images/RoboND_flag.png)](https://www.udacity.com/robotics)
# robo-nd-project3

Where Am I? - 3rd project for Robotics Software Engineer Nanodegree @Udacity

This project uses the Adaptative Monte Carlo Localization package to localize a differential drive mobile robot in a 4x2 meters performance environment.

The Gazebo world design intends to replicate the **WorldSkills Mobile Robotics** next challange in a simplified version.
For more information please take a look on a brief competition overview at the end.

![alt text](https://github.com/TheodoroCardoso/robo-nd-project3/blob/main/Localized%20Robot.png)

## How to Launch the simulation?

#### Create a catkin_ws, feel free to skip if you already have one!
```sh
$ cd /home/workspace/
$ mkdir -p /home/workspace/catkin_ws/src/
$ cd catkin_ws/src/
$ catkin_init_workspace
$ cd ..
```

#### Clone the package in catkin_ws/src/
```sh
$ cd /home/workspace/catkin_ws/src/
$ git clone https://github.com/TheodoroCardoso/where-am-i.git
```

#### Build the packages
```sh
$ cd /home/workspace/catkin_ws/ 
$ catkin_make
```

#### After building the packages, source your environment
```sh
$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash
```

#### Once `my_robot` package has been built, you can launch the simulation environment using
```sh
$ roslaunch my_robot world.launch
```

#### To run the AMCL algorithm
Open a new terminal and type the following:
```sh
$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash
$ roslaunch my_robot amcl.launch
```

#### That's it! Now just give the robot a 2D Nav Goal using Rviz and watch the localization process.
----

## Learn more about WorldSkills
[WorldSkills](https://worldskills.org/) Is the world's largest TVET competition that happens every 2 years in a different country.

Last event was in Kazan, Russia and had over 60 different skills from bakery to hairdressing to mobile robotics.

The next edition which will take place in Shanghai, China 2022.

### Mobile Robotics
The competition is based on a [robotics kit](https://www.studica.co/worldskills-shanghai-2022) to level the playing field between different countries.

In previous years LabVIEW was the mandatory programming language, but for the next edition the hardware has changed and more options like ROS are available.

### The Robot's Task
The WS Shanghai 2022 challange simulates a hospital.

In the actual competition teams will develop mobile robots that have to carry medicines and hazardous materials represented by colored cubes and gurneys represented by a four wheeled chassis.
