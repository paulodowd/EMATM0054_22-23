# Labsheet 4: Line Following (Exercises Only)

## Exercise 1: Ground Sensors

Feel free to discuss these questions with your peers.  It is a valuable skill to be able to construct **hypotheses** prior to working with the robot:

1. **Hypothesise**: Given your prior experience of the line-sensors, what do we expect the time-values of the 3 ground sensors to be on white and black surfaces?
  - in the above example, we have considered the central sensor to be "active" on the line, but we could also define this in inverted terms.  
  
2. **Hypothesise**: What motion would you expect to observe in the robot motion if the feedback-signal was inverted?
  - is there a case where line following can be achieved with an inverted feedback signal?

3. **Hypothesise**: An exceptional case not caught with the above logic would be if all three ground-sensors were detecting back simultaneously.  This can happen even though the black line is narrower than the gap between the two outer-most sensors.  Under what condition might this occur?

4. **Hypothesise**: What would be appropriate feedback responses for other exceptional (non-defined) cases of the sensor activation?

5. **Hypothesise**: If your robot was to calculate a performance score within `loop()` for line-following (a **metric**) as it operated:
  - what **`proprioceptive`** information could be used?
  - what **`exteroceptive`** information could be used?
  
  <br><br>
  <hr>
  <br><br>
  
  
  ## Exercise 2: Implement a Bang-Bang Controller 

1. Is a bang-bang controller **`open-loop`** or **`closed-loop`** control?  What is the difference?

2. Using your prior experience taking readings from the ground sensors, decide appropriate thresholds for when each sensor can be considered `active` or `inactive`:
  - decide whether large time measurements indicate the presence of a line or not.
  - decide on some time measurement values to use as a threshold. For example, at what value would we say the line was present?
  - which sensor states will be used to build the bang-bang control logic discussed above?  You could use individual sensor states, or a combination of them.  
  - are these threshold values the same for `DN2`, `DN3` and `DN4`?  Remember that you can inspect the values of your sensors using `Serial.print()` and `Serial.println()`.
  - remember that you can use the `Serial Plotter` built into the Arduino IDE to look at multiple sensor values simultaneously.
  - it is recommended to use `#define` statements to set these values at the top of your program.  This way, they will be easy to find and change.
  

3. Implement the discussed bang-bang controller logic within your `loop()`:
  - to begin with, place your robot on the line.  Do not expect your robot to be able to find the line if it is not on the line to start with.
  - use the black vinyl tape to create a short black line on your work surface.
  - it is recommended you start with `slow` or `low` motor velocities.
  - to begin with, do not implement forward motion.  Instead, work only with turning on the spot (rotation).  Does your robot turn the correct way to get back to central on the line?
  - check that your `feedback signal` turns your robot in the appropriate directions with respect to sensor activation.
  - investigate what happens when your line is placed into difficult places with respect to the line - are any of these a problem you need to address?
  - once you are confident rotation is working properly, implement forward motion.
  - **help**: remember your conditional statement can use: 
    - `<`  less than
    - `<=` less than or equal to
    - `==` equal to
    - `>=` greater than or equal to
    - `>`  greater than
    - `!=` not equal to
  - **help**: what is the functional difference between the two code examples immediately below?
  
```c
  // Example 1
  if( ) {

  } 
  if( ) {

  }

  // Example 2
  if( ) {

  } else if( ) {

  } 
```

4. Does your robot conduct `turn` and `move fowards` operations seperately?  
  - Can these be integrated so that the robot does not stop moving forwards?
    - it may be useful to use your bang-bang logic to set the value of left and right `pwm` or `power` variables, which are then used to command the motors once after the logic.
  - How is performance effected with turning and moving forwards combined?
  - Moving slowly might increase the general reliability of the line following behaviour.  As a thought experiment, what other hypothetical **`task requirements`** would make fast forward speed desirable for the robotic system?
  - What is the quickest forward speed you can utilise and still achieve reliable line-following?
  - If you have not done so already, experiment with more challenging line shapes, such as corners and curves.  

5. What information about the line does the robot have when no sensors detect the black surface?
  - When might this circumstance occur?  Consider the line map provided for the line following challenge.
  - What would be an appropriate response in this condition?
  - What other information is available to the robot that might be useful?

6. Write a function to simply confirm if the robot is on a black line.  The function should report a `true` or `false` value when called.  For example, a function named `lineDetected()` (returning true or false).
  - is there a reason to discriminate between which of the sensors is on a black surface, or can it be any of the 3?  Explain your reasoning, adjust the function if necessary.

7. Use the above function to allow your robot to start off the line and drive forwards until it meets the line.  Once it is on the line, it should activate (begin calling) the bang-bang controller.
  - Consider using a `global` variable and an `if()` statement to switch the robot between these two behaviours, or `states` of operation. 

8. Start your robot off the line, and allow it to travel forward to join and follow the line.  Currently, what is the most extreme <a href="https://en.wikipedia.org/wiki/Angle_of_incidence_(optics)">angle of incidence</a> where your controller can still successfully begin line following?
  - if you were to create a results table of different angles when joining the line, how could you quantify the reliability of the controller?

<br><br>
<hr>
<br><br>

## Exercise 3: Weighted-Line Measurement, Proportional Control

In these exercises, there is a risk that you might mix variable types within your code.  As you write your code, be mindful of what `data type` you variables are in, and what type the calculations are executed in.  In general, avoid compound calculations because they are difficult to debug - it is the same amount of computation to split your calcuations across multiple lines of code.    

You will probably see the following bugs - look out for them!
 - $e_{line}$, $w_{left}$, $w_{right}$, always reporting a value of 0.
  - Did you setup your line sensors properly?
 - $e_{line}$ reporting `NaN` or `inf` - this typically means an error through division by 0.
  - Use an `if()` statement to catch a zero value, and decide what calculation or value should be used instead.
 - etc.

<p>
<br>
</p>

1. **Hypothesise:** When $w_{left}$ and $w_{right}$ are equal, what would we expect the value of $e_{line}$ to be?

2. For your 3PI+ robot, would a negative value of $e_{line}$ provide feedback to turn left or right?  
  - There is not a right answer to this question - you must decide how to implement this within your system.

3.  Implement the weighted-line sensing as discussed above. To start with, ignore motor operation and check that a weighted-measurement can be gained ($e_{line}$).  You may also want to develop this code within `loop()` for now, and then integrate it within a line sensing `class` once you are sure it works reliably.  There are further considerations to make:
  - is your ground sensor `active low` or `active high`?   How could you invert the value of a sensor reading?  Is this necessary?
  - how can you invert the sign of the error signal, $e_{line}$?
  - test that $e_{line}$ meets your expectations by moving your 3Pi+ by hand over different surfaces and the a black line.  Does it have a negative value when you would expect?  
  
4. Begin to add motor operation.  Write code to utilise the weighted-measurement to operate the 3Pi+ motors:
    - **Decompose the problem:** To begin with, ignore any forward motion.
    - You can start by using the Bang-Bang controller code by just checking if the value is positive or negative, and deciding which way to turn.
    - Is your robot able to re-centre itself over the line?  Check by manually placing your robot in different circumstances.  
    - If it turns the wrong way, how might you invert the behaviour?
  - **help**: What would you expect your robot to do when it is not on a line?  What do you observe when the robot is not on a line?
  - **help**: The following code extract should help you to instead utilise the continuous $e_{line}$ value to determine a continous motor output.  You should integrate this with techniques and understanding you have picked up in previous labsheets:

```c
void loop() {

  // Get the line error from a function you have
  // written, or a class you have written.
  float e_line;
  e_line = getLineError(); 

  // Determine a proportional rotation power.  
  // We will scale a maximum PWM value by the 
  // e_line signal.
  float turn_pwm;
  turn_pwm = ????;  // What is a sensible max pwm for rotation?

  // Turn_pwm is scaled by e_line [ -1.0 : +1.0 ]
  turn_pwm = turn_pwm * e_line;

  // Set motor values.
  // Assuming you have written a function to command
  // your motors.
  // What does "0 -" and "0 +" achieve here?
  setMotorValues( (0 - turn_pwm), (0 + turn_pwm) );
    
}

// A function to return an error signal representative
// of the line placement under the ground sensor.
//
// !! Be careful with mixed variable types!!
//
float getLineError() {
  float e_line;
  float w_left;
  float w_right;

  // Get latest line sensor readings.
  // You may need to call an updateLineSensor()
  // function from loop before hand - it depends
  // on your implementation.

  // Sum ground sensor activation

  // Normalise individual sensor readings 
  // against sum

  // Calculated error signal
  w_right = ????;
  w_left  = ????;
  e_line  = ????;

  // Return result
  return e_line;
}

```


5. Modify your solution to implement a fixed forward velocity for your robot in addition to the proportional turning response.
  - How fast can your robot move forwards and still reliably follow the line?  Slowly adjust the speed of your robot, testing each case.
  - Which parts of the line following map present the greatest challenge to your solution?
  - How might your robot measure it's own line following performance (a **`metric`**)?
    - what `proprioceptive` information could be used?
    - what `exteroceptive` information could be used? 
  

6. Implement a mechanism to vary the foward pwm of your robot independently of the turning pwm:
  - Aim for high forward velocity on straight-line segments, and low forward velocity on sharp corners.
  - How can you convert this line performance measure into another `proportional control` mechanism for forward velocity?
  - Is it useful if the forward motion can also be reversed?  e.g., a negative feedback signal?

7. When you are confident that your line following process is good enough, `refactor` the code into a new function with an appropriate name, such as `lineFollowingBehaviour()`.
  - because this behaviour will make operate both the line sensors and the motors, it is not especially useful to integrate this into a class.  When considering your classes, it might be a good criteria to consider what code could be "portable" (useful) to other projects.  
    - In this case, the line following behaviour is likely too specific to your robot - whilst the operation of the motors and line sensors has more generic processes, and more elementary parameters (e.g., pin numbers).  
    - We can also consider portability by how many dependencies a piece of code has on other code.  Ideal portability has the fewest dependencies.

8. Use the task-scheduling technique from Labsheet 3 to schedule the line following behaviour to update at a known time interval:
  - what happens if this time interval is made large?
  - what happens if this time interval is made small?
  - between large and small intervals, is the behaviour consistent in performance? 

9. Alter your code so that your robot can start off-the-line and then drive forwards until it meets the line.  Once it is on the line, it should activate the line following controller.
  - Consider using a `global` variable and an `if()` statement to switch the robot between these two behaviours. 
  - What is the most extreme <a href="https://en.wikipedia.org/wiki/Angle_of_incidence_(optics)">angle of incidence</a> where your controller can still successfully begin line following?
  - How does this compare to the bang-bang controller?
  
  
  <br><br>
  <hr>
  <br><br>
  
  ## Exercise 4: Calibration Function 

We will utilise the calibration routine as the first operation when the robot is powered on.  After this, we expect the 3Pi+ into the more complex and iterative behavior of solving the line following challenge.  As such, it is acceptable to write a short sequential section of code which moves through the calibration protocol outlined above.  We can consider calibration as part of the robot initialisation.

Also note that, after your robot has completed this initial calibration, the task environment is likely to change.  This means you may see your sensors exhibit some bias later.  For example, you might find that when centered over the line, you read a small non-zero value despite having completed the calibration.  Here, it is important to ask how accurate and precise you need your sensors to be.  It is likely that you do not need perfect performance.  For example, a small bias (+/-0.1) will be corrected by the closed-loop line following behaviour you will have programmed.  Trying to remove a small error will take a lot of time, and it is likely unncessary to do so.

When you work on this exercise, it is recommended that you save your prior work, and start a new file.  Once you have calibration working, you might consider merging the new calibration code with prior work into a new subsequent file.  This process will help to reduce bugs, and ensure that any progress you have made so far is not lost through confusion.

The following exercises are suggestions, and you are free to explore other calibration techniques:

1. Decide whether:
  - your robot will move continuously for a period of time, and collect samples of both black and white.  E.g., rotating on the spot, over a black and white surface.
  - take two discrete actions, such as measurements recorded on white, and then measurements recorded on black. E.g., beginning on a white surface, then moving forwards and stopping-on a black surface.

2. Have your robot take `n` number of measurements on both black and white surfaces.  Decide whether:
  - your robot will select the minimum and/or maximum from `n` samples.
  - your robot will utilise the mean, median and/or mode from `n` samples. 
  - how this is acheived, or which are appropriate, also depends on how your robot moves (interacts with the environment).

3. Set persistent variables for each of the 3 sensors to store the offset bias.
  - **help**: the offset bias is the consistent value away from 0 on the y-axis.  Is this measured over a black surface or white surface?

4. Utilsing the calculated range (from black to white surfaces), set persistent variables for each of the 3 sensors to store the independent value $(1/range)$.  This will be the `scaling factor` ($S$) to apply to all subsequent readings for each sensor signal.  

5.  Make a call from `setup()` to your calibration function.  Ensure that the robot can perform the calibration as you expect.

6.  Write a new additional function to report a measurement from a sensor which applies the signal conditioning.  Call this function from within `loop()` reporting the values to the Serial Monitor:
  - $c_{i} = (m_{i} - b_{i}) * S_{i}$
  - where:
    - $c_{i}$ is the resulting conditioned measurement for sensor $i$
    - $m_{i}$ is the unconditioned, or raw measurement of sensor $i$
    - $b_{i}$ is the offset bias for sensor $i$
    - $S_{i}$ is the scaling factor for sensor $i$, in range [ 0 : 1 ]

7. Integrate your new calibration routine, and conditioned readings, into either your bang-bang solution or weighted-measurement line following solution.  
  - Instead of working with old code, look to merge your code into a new file. 
  - You should expect that key parameters will need to be adjusted.  
  - Validate the peformance of your robot through observations (`qualitative evaluation`).  What descriptions of motion are you looking for, how would you communicate the criteria you are using?
  - If you developed a method for your 3Pi+ to calculate a measure of performance (a `metric`) for line following previously, now use the same metric in this new system and compare performance (`quantitative evaluation`).  
