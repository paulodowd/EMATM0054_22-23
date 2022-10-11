# Labsheet 2: Motors (Exercises Only)


## Exercise 1: Basic Motor Operation

1. **Hypothesise (hardware):** In the above circuit extract, we can see a tiny arrow next to the symbol for the motors.  This arrow indicates the normal direction of the motor.  These arrows are pointing in different directions.  Why may the circuit and hardware have been specified in this way?

2. Follow the below code below these exercises, filling in the important parameters and operations:
 - you can find the appropriate pins in the <a href="https://www.pololu.com/docs/0J83/5.9">pin assignment section of the 3Pi+ documentation</a>.  
 - you will haved used the Arduino built-in functions to configure pins in Labsheet 1 (`pinMode()`)

3. **Validate:** Check that you have assigned the left and right pins appropriately.  Does activating just the left motor in code activate the left motor in reality?  What about the right motor, is that correct?

4. **Validate:** Check whether a `HIGH` value for the `direction` pin produces forward or backward motion of your robot.
  - It is recommended you then create and use `#define FWD LOW` (or HIGH), and `#define REV ...` definitions in your code, to make it more readable.  You can then use `FWD` and `REV` instead of `HIGH` and `LOW`, where `#define` is acting like a find-and-replace operation.

5. Explore combinations of left and right motor power values.  Adjust your program in simple ways to get your robot to:
  - drive forwards in a straight line.
  - drive backwards in a straight line.
  - turn on the spot to the left.
  - turn on the spot to he right.
  - drive on an arc, or to trace a large circle.
  - **Note:** When we are powering the motors and not using any sensor information, **your robot cannot drive in a good straight line**.  We will address this by programming line following behaviour, and later PID speed control.

6. Investigate how `analogWrite()` operates, and how it might produce errors:
  - What happens if you send negative numbers to `analogWrite()`?
  - What happens if a value larger than 255 is sent to `analogWrite()`?
  - What happens if fractional numbers are sent to `analogWrite()`?


```c

// Replace the ? with correct pin numbers
// https://www.pololu.com/docs/0J83/5.9
#define L_PWM_PIN ?
#define L_DIR_PIN ?
#define R_PWM_PIN ?
#define R_DIR_PIN ?

#define FWD ?
#define REV ?

// Runs once.
void setup() {

  // Set all the motor pins as outputs.
  // There are 4 pins in total to set.
  // ...

  // Set initial direction (HIGH/LOW)
  // for the direction pins.
  // ...

  // Set initial power values for the PWM
  // Pins.
  // ...


  // Start serial, send debug text.
  Serial.begin(9600);
  delay(1000);
  Serial.println("***RESET***");

}

// Repeats.
void loop() {

  // Add code to set the direction of rotation
  // for the left and right motor here.


  // Use analogWrite() to set the power to the
  // motors.
  // 20 is a low level of activation to test
  // the motor operation.
  analogWrite( L_PWM_PIN, 20 );
  analogWrite( R_PWM_PIN, 20 );

  // An empty loop can block further uploads.
  // A small delay to prevent this for now.
  delay(5);
}
```

<br><br>
<hr>
<br><br>


 
## Exercise 2: Getting Familiar

Although we are writing software, it is important that you learn from experience how your robot physically behaves under certain conditions.  Take some time to experiment with your code and figure out the limitations and surprises:

1. Deadband: The forward and reverse PWM values and which cannot produce movement are called a **deadband**, and can be a difficult problem to deal with when controlling motors.  What is the range of PWM values which constitute the deadband for your robot?
  - **Experimental Observations:** the following observations will be _unique to your 3Pi+_ and will be useful for future labsheets:
    - Experiment to find the **minimum** motor PWM required for your robot to move fowards, note this down.
    - Experiment to find the **minimum** motor PWM required for your robot to move backwards, note this down.
    - Are the above measurements the same values for forwards and backwards?
    - Are the above measurements the same for left and right motors?
    - **Hypothesise**: What factors (robot or environment) may influence your above observations?
      - which factors could you predict and test immediately?
      - which factors might take a long time to emmerge?
      - when you make these predictions, what do you hypothesise would be observable in the robot performance?

2. Drift: Because of varying tolerances in manufacturing, it is unlikely that you 3Pi+ motors will perform in an identical way.  We can evaluate this by observing the travel of the robot against a straight line.  Use the black vinyl tape to mark down a straight line on your work surface (or draw a line). A recommended minimum distance is **60cm**.  Adjust your Arduino program in the following ways:
  - Set the same direction for both motors and set the same PWM value for left and right motors.
  - Set your program so that your robot will drive forwards for a fixed period of time, enough to travel the length of your line.  You can use `delay()` for this.  Your robot should then deactivate the motors indefinitely (until power-cycled or reset is pressed - see note below for help).  
  - Use tape or draw some marks on the work surface so that you can start your robot in the same location and rotation precisely.  If you cannot place your robot consistently, you will introduce **`human error`** into your experiment, and **`confuse`** your results.  
  - **Experimental Observations:**
    - Activate your robot and allow it to complete the forward travel.
    - Decide how to mark the end position of the robot.  We want to measure the the distance between the center of the robot and the center of the straight line.
    - Repeat this process 10 times for a single PWM value, recording your results.  
    - Use the code cell below (or other software) to plot your results.  Try using a different PWM value to measure the error over the same distance.  Record your results, plot them.
    - How can we interpret, or what can we learn, from the Box and Whisker plot?
    - what would a negative Travel Error (mm) indicate, versus a positive value?
    - **Hypothesise:** If all results were negative, how would you predict and explain what this meant in terms of the **`observable behaviour`** of your robot?
    - In the boxplot, what does the size of the box represent?
    - Are we observing **random error**, or **systematic error**?  Which of these is **evidenced** in the graph of your results, and how? 


**Note**: to halt your robot motion indefinitely (stop travelling), you will need to write a 0 PWM value to both motors, and then trap your program within a loop with no end.  The following code extract is an example:
```c
  // Example to stop the robot indefinitely.
  // Only a hard reset will break the loop.
  analogWrite( L_PWM_PIN, 0);
  analogWrite( R_PWM_PIN, 0);
  while(1) {
    Serial.println("Program Halted");
    delay(500);
  }
```

<br><br>
<hr>
<br><br>


## Exercise 3: Confident Operation

A robotic system can quickly become very complicated, and it can be hard to tell where an error is coming from.  Sources or causes of error in a robotic system include:
- **Environment:** misunderstood or unanticipated environment conditions (e.g. a dirty floor, bright sunlinght)
- **Hardware:** mechanical, electronic failures on the robot (e.g. something not plugged in, low battery power). 
- **Software:** logical and/or execution programming errors (e.g. a bug in your code!).
- **Task:** human misunderstanding of the robot capability or assigned task (e.g. <a href="https://en.wikipedia.org/wiki/Anthropomorphism">anthropomorphism</a>, "it should know...!").

As a rule of thumb, it is good practice to move through the above 4 categories when attempting to diagnose a problem.  Usually, we become very focused at the  **task** and **software** level, and we typically can overlook errors caused by the **hardware** and **environment** (such as, a dirty worksurface changing the behaviour of the robot).  Because of this, we can spend hours editing a lot of code from an assumption of a problem.

To make problem solving easier, we can prioritise being **confident** that our code works as expected.  If we can catch all possible error conditions in software, we will have an easier time figuring out why something isn't working.  

1. **Refactor:** Complete the below example function to operate your 3Pi+ motors.
  - Focus on either the left or right motor first.
  - Use the sign of the argument `PWM` to set the motor direction.
  - Use the absolute magnitude (unsigned value) of argument `PWM` for analogWrite().
  - Limit the possible range of values accepted.  What is a sensible range?
    - **Note:** This means setting a maximum speed, both forwards and backwards. This is highly recommended.
  - Decide how your function should respond to illegal values.
  - When satisfied that one motor is working correctly, complete the function to work with both motors.


```c
/*
 * Sets the power of the motors using analogWrite().
 * This function sets direction and PWM (power).
 * This function catches all errors of input PWM.
 *  inputs: 
 *     pwm   accepts negative, 0 and positve
 *           values.  Sign of value used to set
 *           the direction of the motor.  Values
 *           are limited in range [ ??? : ??? ].
 *           Magnitude used to set analogWrite().
 */
void setLeftMotorPower( float left_pwm, float right_pwm ) {

}
```

2. **Validate:** Write a test routine within your main `loop()`:
  - Start your PWM value at 0
  - Write a routine to automatically increment the value sent to your motor operation function.  
  - Allow the value to increment past the acceptable input to your motor operation function.  What should happen, as determined in your function?
  - Set an arbitrary positive limit witin `loop()`, which once reached toggles the routine to decrement into negative PWM values.  What should happen, as determined in your function?
  - Allow the negative values to exceed the valid input range of your function.  What should happen?
  - Conduct this test on left and right motors simultaneously.
  - Did your code and robot pass the test?


<br><br>
<hr>
<br><br>

## Exercise 4: Write and Test a Motor Class

You can download a template Arduino sketch with empty class files created for you from Github (<a href="https://github.com/paulodowd/EMATM0053_21_22/tree/main/3PI_CodeStub">Github Page</a>, <a href="https://github.com/paulodowd/EMATM0053_21_22/raw/main/3PI_CodeStub/Labsheet_X.zip">Download Link for Zip file</a>).

<p align="center">
<img src="https://github.com/paulodowd/EMATM0054_22-23/blob/main/Images/3PI_ArduinoTabs.png?raw=true">
</p>

1. **Refactor:** Extract your code relating to motor operation from your main Arduino sketch file (.ino), and `refactor` it into a/the `motors.h` class file.  If you have downloaded the provided template, this source file will appear in the Arduino IDE as a tab at the top:
  - decide if you will use a class to define the operation of a single motor, or both motors together as a subsystem.
  - complete the provided function `intialise()`, or write your own, to set the mode and initial state of the `gpio` pins for motor operation.  
    - You can either pass arguments into this function for pin numbers (etc), or when necessary, add `#define` statements or `global` variables to the class file.
  - before you go further, adjust your main Arduino sketch file (.ino) to include the following statements, and solve any errors that occur:

```c

// other code...

// Create an instance of the motor 
// class named "motors"
Motors_c motors;

void setup() {

  // Initialise the motor gpio
  motors.initialise();

  // Other code....
}


// other code...
```

2. **Refactor:** Continue to extract your code, moving the function you have written to command your motors (direction and power) into the motors class file.  
  - Work sequentially, and test your code compiles as you go.
  - Remember that now you will have to call your function by accessing it thorugh the class instance (in the example, named `motors`).

3. **Validate:** Run some final tests to ensure that you class is operating well and without bugs.

With some variation, you main Arduino sketch should now take a form similar to:

```c
// other code...

// Create an instance of the motor 
// class named "motors"
Motors_c motors;

void setup() {

  // Initialise the motor gpio
  motors.initialise();

  // Other code....
}

void loop() {
  
  // test to set motors
  motors.myMotorCommandFunction();

  // other code...

}

// other code...
```




