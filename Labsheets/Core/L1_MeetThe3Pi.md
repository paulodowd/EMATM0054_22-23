# Labsheet 1: Getting Started, Uploading, Debugging

In this exercise sheet, you will get to know the **3Pi+ robot** that you will be using throughout these labs and for the coursework assessments. 


In this labsheet you will:

+ See the standard Arduino sketch, which has the structure of setup() and loop() routines.
+ Experiment with Arduino Example sketches.
+ Upload sketches to your 3Pi+ robot.
+ Experiment with Serial commands to view debug output from your code.


**If you have difficulty connecting to your 3Pi+, please see the notes in <a href="https://github.com/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Core/L0_TroubleShooting.md">FAQ/Troubleshooting</a>.**

<hr>
<br><br><br><br>

## 3Pi+ Overview Video



[![3PI+ Overview Video](https://img.youtube.com/vi/BRJKrKbe4Uw/0.jpg)](https://www.youtube.com/watch?v=BRJKrKbe4Uw)

<a href="https://youtu.be/BRJKrKbe4Uw">Youtube Link</a>

<hr>
<br><br><br><br>
## Arduino IDE



[![Quick Video on Arduino IDE setup for the 3Pi+ Robot](https://img.youtube.com/vi/0W2lgNKPqKY/0.jpg)](https://www.youtube.com/watch?v=0W2lgNKPqKY)

<a href="https://youtu.be/0W2lgNKPqKY">Quick Video on Arduino IDE setup for the 3Pi+ Robot</a>


Please use the Arduino IDE (Integrated Development Environment), which is <a href="https://www.arduino.cc/en/software">available at the Arduino Website</a> (`https://www.arduino.cc/en/software`).  Please also use the application intended to be downloaded and installed on to your computer, rather than the web-browser version.

You are free to use another IDE, such as Eclipse of Visual Studio.  However, the teaching staff are **not able to offer support** to these applications.

A template Arduino Sketch is avialable via GitHub (<a href="https://github.com/paulodowd/EMATM0053_21_22/tree/main/3PI_CodeStub">Github Page</a>, <a href="https://github.com/paulodowd/EMATM0053_21_22/raw/main/3PI_CodeStub/Labsheet_X.zip">Zip Download</a>).  Simple open the `.ino` file with the Arduino IDE.

To add `line numbers`, `code block collapsing`, or to turn off `auto-complete` features, you can click: `File -> Preference`, and in the dialogue box find a reference to a text file with further options called "preferences.txt".  Edit this file to set your preferences and save the file.   You will need to restart the Arduino IDE. 

Remember that you will need to:
- Select the appropriate board, `Tools -> Board -> Arduino Leonardo`.  
- Select the appropriate port, `Tools -> Ports ->`
  - This will be COM(n) in Windows, and as a general rule, the highest enumerated.
  - This will be something like `ttyUSB0` or `ttyACM0` in Linux
  - This will be something like `USBModem` on Apple computers. 

Further help on setting up the Arduino IDE can be found on the <a href="https://www.pololu.com/docs/0J83/6.2">Pololu Website in the 3Pi+ documentation</a>.

<hr>
<br><br><br><br>

## Pololu 3PI+ in Overview

 You are welcome to review the product page and documentation on the 3Pi+ provided by Pololu which is <a href="https://www.pololu.com/product/3737/resources">available here</a>.  

You might also discover that Pololu provide an Arduino Software library to operate the 3Pi+, <a href="https://github.com/pololu/pololu-3pi-plus-32u4-arduino-library">available here</a>.  You are encouraged to investigate this library where it is useful to support your learning.  However, for this coursework you are **not permitted** to use the Library in your work or your final submission.  If you investigate the Pololu library code, you will find:
- some of it is very terse.
- it references further available libraries. 
- it is easy to spot some advanced techniques.  

The aim of these exercise sheets is to help you to develop a **deep understanding**, which is best gained by writing your own code for the available hardware.  This will also give you the necessary practice (i.e time invested) to develop skill in debugging software written for a robotic system.  

<p align="center">
<br>
<img src="https://github.com/paulodowd/EMATM0054_22-23/blob/main/Images/3PI_Top_Annotated.png?raw=true">
<br>
</p>

Above is a photo of the Pololu 3Pi+ robot taken looking at the top of the robot.  On the left, the LCD screen is installed by the manufacturer.  For these labsheets it is recommended you remove the LCD screen, so your robot will look like the image on the right.  We will not be using the LCD, and the LCD screen will consume your battery power quicker.  To remove the LCD, simply pull it directly away from the robot body.  **If you decide to install the LCD again, ensure it is plugged in the correct way around to avoid damage to your robot.**

<p align="center">
<br>
<img src="https://github.com/paulodowd/EMATM0054_22-23/blob/main/Images/3PI_BottomAnnotated.png?raw=true">
<br>
</p>

In the above image, the 3Pi+ has been flipped over, so that the bottom of the robot is visible.  On the right, the most important parts of the robot have been annotated for the task of line following:
- 5 ground sensors, measuring reflected infra-red light.
- two motors, each with an attached gear-train and rotary encoder.
- a ball-caster.


The 3Pi+ is controlled by an ATMEL ATMEGA32u4 Microcontroller (<a href="https://www.microchip.com/en-us/product/ATmega32U4">produce page</a>, <a href="https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7766-8-bit-AVR-ATmega16U4-32U4_Datasheet.pdf">datasheet</a>).  Throughout these labsheets you'll find a general discussion of the electronics.  We will not be required to make any changes or direct interaction with the electronics.  


