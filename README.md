# Robotic Systems: EMATM0054_22-23
Teaching Materials for Robotic Systems EMATM0054 AY 2022-2023

## Suggested Timeline

As a 20 Credit unit of study, you are expected to **invest 16 hours per week** to use the Core Labsheets to complete Assessment 1 Line Following Challenge.  For example, you could structure your time into two 8 hour days per week, or four 4 hour sessions of work.  **In general, it is recommended you focus for long blocks of time when learning to program a robot**.  It is likely you will fail Assessment 1 if you only work in the 2 hour laboratory sessions.  Use the laboratory sessions to discuss with the teaching staff problems and challenges that you have discovered during the week.  

<p align="center">
<img src="https://github.com/paulodowd/EMATM0054_22-23/blob/main/Images/TimeLine.png?raw=true">
</p>

## Assessment 1 Solution

Core Labsheets are provided below, which will help you develop the core components of your solution for Assessment 1 Line Following Challenge.  However, you must integrate these core components into a final solution.  A block diagram is provided below to act as a guide, which will be discussed in the lecture sessions.  This block diagram illustrates the essential flow of information in the system, and how the system exhibits intelligent autonomous behaviour.

<p align="center">
<a href="https://github.com/paulodowd/EMATM0054_22-23/blob/main/Images/SystemBlockDiagram.png?raw=true"><img src=https://github.com/paulodowd/EMATM0054_22-23/blob/main/Images/SystemBlockDiagram.png?raw=true></a>
</p>

## Assessment 1 Video Example


[![Video Example of a solution to Assessment 1](https://img.youtube.com/vi/IbfQaGqX-YU/0.jpg)](https://youtu.be/IbfQaGqX-YU)



## Core Labsheets (Assessment 1)

It is recommended you read through all Labsheets before you start, and then decide on which areas you need to focus on.  If you have prior experience programming, there may be areas you can skip.  

You may wish to use the code template available on this <a href="https://github.com/paulodowd/EMATM0054_22-23/tree/main/3PI_CodeStub">github</a>, called `Labsheet_X`, and create copies replacing the X with the number of the labsheet you are currently working on.  This is the simplest way to keep versions of your code.  

Start Here: <a href="https://github.com/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Core/L0_Troubleshooting.md"> FAQ / Trouble Shooting</a><br>

|  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;            | Labsheet Title | Estimated Time | Description |
|---------------|----------------|----------------|-------------|
| [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Core/L0_Troubleshooting.ipynb) | FAQ / TroubleShooting | n/a | Review common problems and solutions |
| [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Core/L1_MeetThe3PI.ipynb) | **Labsheet 1**: Getting Started, Uploading, Debugging | 2 hours | Very basic exercises to familiarise with coding and the 3Pi+ robot. <br><a href="https://github.com/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Core/L1_ExercisesOnly.md">(Exercises Only)</a> |
| [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Core/L2_Motors.ipynb) | **Labsheet 2**: Motors | 4 hours | Exercises to get your robot moving, steps to be confident that your code will behave predictably, and writing a Class. <br><a href="https://github.com/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Core/L2_ExercisesOnly.md">(Exercises Only)</a> |
| [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Core/L3_LineSensors.ipynb) | **Labsheet 3**: Line Sensors | 6 hours | Incremental exercises to get the line sensors working.  The first difficult programming exercise in terms of logic and iteration. <br><a href="https://github.com/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Core/L3_ExercisesOnly.md">(Exercises Only)</a> |
| [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Core/L4_LineFollowing.ipynb) | **Labsheet 4**: Line Following | 4 hours  | Exercises to read the line sensors (input) and to produce useful motion (output).  The first case of autonomous behaviour.  Debugging robot behaviours may be a challenge (e.g., "this isn't doing what I expected" might not be just a software problem). <br><a href="https://github.com/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Core/L4_ExercisesOnly.md">(Exercises Only)</a> |
| [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Core/L5_FiniteStateMachine.ipynb) | **Labsheet 5**: Finite State Machine | 0.5 hours | Very easy - mostly information.  How to get your robot to automatically switch between different behaviours to solve more complicated tasks. <br><a href="https://github.com/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Core/L5_ExercisesOnly.md">(Exercises Only)</a> |
| [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Core/L6_Odometry.ipynb) | **Labsheet 6**: Odometry | 4 hours  | Relatively straight-forward programming to use the wheel encoders and to estimate the robot position.  Some time will need to be spent to understand and calibrate out error. <br><a href="https://github.com/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Core/L6_ExercisesOnly.md">(Exercises Only)</a> |
| [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Core/L7_PID.ipynb) | **Labsheet 7**: PID | 6 hours  | Relatively straight-forward programming to implement a PID controller for wheel speed control. However, this can be difficult to debug and the work must be conducted slowly and systematically. <br><a href="https://github.com/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Core/L7_ExercisesOnly.md">(Exercises Only)</a> |
  

## Supplementary Labsheets (Assessment 2)

|  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; | Labsheet Title | Description |
|---------------|----------------|----------------|
| [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Supp/SL0_MeasuringBatteryVoltage.ipynb) | SL0: Battery Voltage | How to read the battery voltage of your 3Pi+. |
| [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Supp/SL1_InterruptsAndTimers.ipynb) | SL1: Interrupts and Timers | How to configure a precise timer to run code automatically. |
| [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Supp/SL2_BumpSensors.ipynb) | SL2: Bump Sensors | How to read the bump sensors. <br> |
| [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Supp/SL3_InertialSensors.ipynb) | SL3: Inertial Sensors |  How to read the Gyro, Accelerometer and Magnetometer sensors. <br> |
| [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Supp/SL4_NonVolatileMemory.ipynbb) | SL4: Non-Volatile Memory |  How to read and write data into memory which persists when the robot is powered off. <br>|
| [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Supp/SL5_RetrieveSerialData.ipynb) | SL5: Retrieving Data | How to plug in a USB cable and retrieve data without resetting your robot. <br> |
| [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Supp/SL6_PlottingResults.ipynb) | SL6: Graphing Results | Example Python/Colab code to plot various graphs for Assessment 2. <br> |
| [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Supp/SL7_Serial_Input.ipynb) | SL7: Serial Input |  How to use the Serial interface to provide input to your robot. <br>|

## Assessment 1 Video Demonstration





## A2 Experiment Ideas

 [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Misc/Previous_Projects.ipynb) Previous Project, List of Abstracts
<br><br>

<a href="">Example Reports</a>
<br><br>
<a href="">Example A2 Feedback</a>


## Teaching Team
