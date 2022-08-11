# Labsheet 3: Line Sensors (Exercises Only)

<hr>
<br><br><br><br>

## Exercise 1: Setup

To begin with, put aside your previous work with the 3Pi+.  When we are first developing for new hardware, we want to keep the process as simple and as error free as possible.  Therefore, for now we do not need any code relating to the operation of the motors (Labshseet 2).  

In this labsheet, we will only work with the 3 central line sensors beneath the 3Pi+ robot.  In this first exercise, we will prepare the information we need to setup the sensors:

1. **Hardware:** Is the ground sensor an **`active`** or **`passive`** sensor?  What informs your answer?

2. Save your previous work, and start a new sketch (source code file).  Give this a useful name, such as "lineSensorTest", or "Labsheet3".

3. Use the standard Arduino template of `setup()` and `loop()`.  If you are unsure, you could open the Arduino IDE example "Blink" and adjust the code therein.  At the top of your file in `global scope`:
  - Add `#define` statements to create references:
  - DN2 should be set as A0 (left most sensor)
  - DN3 should be set as A2 (middle sensor)
  - DN4 should be set as A3 (right sensor)
  - EMIT should be set as 11 (IR LED power)
  - Use meaningful names, such as "LS_LEFT_IN_PIN", "LS_CENTRE_IN_PIN", "LS_RIGHT_IN_PIN" (where LS represents "line sensor").

4. Add code to `setup()` to set:
  - EMIT pin mode as an `OUTPUT`.
  - The 3 line sensor input pins mode as `INPUT`
  - Add `Serial` functionality to help you to later debug your code.  Add a print command to transmit to you that the Arduino has completed setup.  
  - You can refer back to previous work to find examples of all the built-in functions you require.

5. **Hardware:** Thinking ahead, should the `EMIT` pin be set `HIGH`, or `LOW` to enable the IR LEDs for the line sensors?
  - either use the <a href="https://www.pololu.com/docs/0J83/5.5">documentation</a>, or review the circuit schematic and discussion above.
  
<hr>
<br><br><br><br>

## Exercise 2: Sensor Validation

1. Test your knowledge:
  - what is the difference between an `unsigned long` and a `long`?
  - what does an `overflow` error mean for a variable?
  - when an `overflow` error occurs for a variable, what might we expect to observe (what change of value might we see) for:
    - an `unsigned long`?
    - a `long`?

It is important to first validate that the example above works on your 3Pi+.  Use the above example code, and update it according to the following exercise prompts:

2. The above example given in `loop()` has the following assumptions you need to address in your own code to create a working example:
  - Ensure that you have completed your `setup()` routine to set the relevant `GPIO` pins into a good initial state.
  - The example assumes that the IR LEDs were enabled (turned-on) within `setup()`.  What is the initial state of your IR LEDs?
  - To enable the line sensor IR LEDs, does `EMIT` need to be set as an `OUTPUT` in state `HIGH`, or `LOW`?  You can check either the schematic or documentation.  
  - **Help:** A common problem at this stage is that you have not enabled the IR LEDs (EMIT pin), and so your sensors take a very long time to read.  

3. Upload your code to the 3Pi+ and validate that you see a difference in the sensor reading between different surfaces.  
  - Use the Serial Monitor and check the reported elapsed time value.
  - Use the black vinyl tape to create a dark surface  - this will also be the surface of line your 3Pi+ will need to follow (`task requirement`).
  - Quickly explore different surfaces to build your intuition, examples include:
    - a page with printed text.
    - different colour surfaces.
    - glossy and matte surfaces.
    - you can <a href="https://github.com/paulodowd/EMATM0053_21_22/tree/main/PrintableSheets">download and print</a> a grey-scale test sheet from Github.
    
4. Note down the smallest time reported and the largest time reported:
  - How do these correspond to your different surfaces?
  - How many milliseconds is the longest time reported? 
  - **Evaluate:** For the longest time reported, how many bits would be needed to represent this decimal value in binary?  How does this compare to the bit-resolution of the `ADC` available within the 32u4 microcontroller?

5. Inspect the timing values when the IR LEDs are switched off.
  - Remember: to switch of the IR LEDs, you must set the `EMIT` pin to mode `INPUT`.
  - With the IR LEDs switched off, what is being measured?
  - With the IR LEDs switched off, how does the measurement change with respect to the 3Pi+ and it's location in the environment?

6. Use the grey-scale test sheet, or construct your own varied black-to-white surface, and record the results into the code cell below to plot a graph:
  - how would you intepret the shape of the line, the **`sensor response`**.  
    - What does the slope of the line mean in terms of sensor behaviour?
    - What does the error region of the line mean in terms of sensor behaviour?
  - is your sensor consistently reliable across all surfaces?
  - **help**: do not forget that you can write code to make your data collection easier for you.  Your 3Pi+ is capable of collecting multiple results and printing them in a useful format.
    
  

<hr>
<br><br><br><br>

## Exercise 3: Improving the Example

The example code provided above has significant room for improvement.  

The below code extract is the part of the routine that waits for the `digitalRead()` measurement to go `LOW`.  Currently, in extreme cases the sensor may take approximately 2400 microseconds (2.4milliseconds) to complete on a very black surface.  Furthermore, an ambient light measurement (if the IR LEDs are off) can exceed 5000microseconds (5millisceonds).  In both cases, millisecond durations are quite long and undesirable. 

```c

  // Begin measurement of time in 
  // microseconds
  unsigned long start_time;
  unsigned long end_time;
  start_time = micros();
 
  // Stay in a loop whilst the capacitor
  // is still registering as "HIGH".
  while( digitalRead( LS_LEFT_PIN ) == HIGH ) {
    // Do nothing
  }
 
  // record end time
  end_time = micros();
 
  // Calculate elapsed time
  unsigned long elapsed_time;
  elapsed_time = end_time - start_time;

```

In the above code extract, we can see that the `while()` loop is very inefficient.   The `while()` loop **blocks** our code, not executing any instructions beyond checking the `conditional statement`.  The program is left "waiting" for the sensor read to complete.  This `while()` loop could also run for an indeterminate (unknown) amount of time if there was an error or bug somewhere (e.g., if the `digitalRead()` never returned `LOW`)- this is not very safe code.

We can imagine a better algorithm that allows the operation to stop itself if it is taking too long:

```c
void loop() {

  // Add code here to:
  // - configure your IR LEDS (EMIT pin)
  // - Charge the capacitor
  // - configure sensor pins to read

  // We are interested in the elapsed
  // time for the sensor read.
  unsigned long sensor_time;

  // Begin measurement of time in 
  // microseconds
  unsigned long start_time;
  start_time = micros();
 
  // Use a flag to capture if the sensor
  // read is complete.
  // Set to false (not done) initially.
  bool done = false;

  // We want to stop the process if it takes
  // too long. Here, we will set a "time out"
  // value to compare against.
  unsigned long timeout = 5000;

  // We will use the general flag "done" to 
  // decide if we should continue waiting.
  // ( "done is not true", so run while loop)
  while( done != true ) {
    
    // Get current time
    unsigned long current_time = micros();

    // Determine elapsed time
    unsigned long elapsed_time = current_time - start_time;

    // Check if we have been waiting too long
    // If true, break from the loop.
    if( elapsed_time >= timeout ) {

        done = true;
        sensor_time = timeout;
    }

    // If the pin has gone low, then the 
    // read is complete.  Save elapsed time
    // and change done flag to true.
    if( digitalRead( LS_LEFT_PIN ) == LOW ) {

        sensor_time = elapsed_time;
        done = true;
    }

  } // end of while loop


} // end of main loop()
 
```

1. Integrate the above example into your code.  Rememeber to keep or add:
  - code to enable the IR LEDs (EMIT pin).
  - code to charge the capacitor prior to the read operation.
  - code to re-configure the sensor input pins to be read.

2. In the above example, when a "time out" occurs the variable sensor_read is set to the `timeout` value.  We can imagine that elsewhere in your code the variable `sensor_time` will be used to effect a behaviour. 
  - when you write code in the future, how might you `disambiguate` a valid sensor read from a time out value?
  - in the future, you might perform more complex calculations on the value stored in `sensor_time`.  What would be a better datatype?

3. In the above code, `timeout` has been set to `5000`.  What is a more useful or sensible `time out` value?  Inspect the graph you have plot in Exercise 2.5 to justify your decision.  

4.  Once you are happy you have the above code working, create a new function to complete your sensor read operation.  
  - Adjust your main `loop()` to look something similar to:

```c
void loop() {

  // Perform sensor read
  readLineSensor();

}

// Line sensor read function
void readLineSensor() {
  // Code previously developed above.
}
```



<hr>
<br><br><br><br>

## Exercise 4: Implementing Multiple Sensors





In the below example, `for()` loops are being used to iterate over variables declared as arrays.  This may look confusing at first, but it is a very useful and practical way to write code.  For loops have the general form of:

```c
for( <initial value>; <operating condition>; <incrementing operation> ) {

}

// This would loop with `i`, repeating 10 times,
// (e.g. while i < 10 ), incrementing i by 1 on
// each iteration (i++, or i += 1, or i = i + 1):
// i = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
for( int i = 0; i < 10; i++ ) {

}

```

Example parallel sensor read code:
```c

// Define which pins the sensors are 
// attached to. These values are taken
// from the online documentation.
#define LS_LEFT_PIN   A0
#define LS_CENTRE_PIN A2
#define LS_CENTER_PIN A3

// Define the max number of sensors to use.
#define NB_LS_PINS 3

// We can create an array ("list") of sensors 
// to check.  This becomes very useful to allow
// us to write code which iterates, rather than
// needing to repeat lines of similar code.
// Note, we should match the number of entries
// to the max number of sensors we are reading. 
int ls_pin[NB_LS_PINS] = { LS_LEFT_PIN, LS_CENTRE_PIN, LS_RIGHT_PIN };

// We will use "which" to index through each
// sensor.  Naming this variable "which" should
// improve the readability of our code later.
// You could use something else.
int which;

// We still need to record the start time.
unsigned long start_time;
start_time = micros();

// Multiple sensors, needs multiple places
// to store the measurement result. 
// We follow the convention above to create
// another array to store 3 values. 
unsigned long sensor_read[ NB_LS_PINS ];

// This time, let's use a count to check how
// many sensors have finished reading.  Let's
// set it to NB_LS_PINS (3), and count down to
// zero.  Therefore, remaining == 0 will mean all
// sensors complete. 
int remaining = NB_LS_PINS;


// While we still have sensors to read.
while( remaining > 0 ) {
  
  // Add code to calculate the current elapsed time
  // here. 

  // Whilst we are not done, we repeatedly attempt
  // to read the sensors.  We read the sensors in
  // a loop.  "which" will be 0,1,2 before moving on
  // with the code in this while loop.
  for( which = 0; which < NB_LS_PINS; which++ ) {

    // We can instruct a digitalRead() using our
    // array variable to drop in the correct pin
    // number.  Here, "which" is incrementing
    // 0, 1, 2, looking up the pin value inside
    // ls_pin[]. 
    // Here, if digitalRead() returns LOW, it means
    // this sensor has completed.  
    if( digitalRead( ls_pin[ which ] ) == LOW ) {

        // Check if this sensor has had a previous
        // value of elapsed time stored before.
        // We only want to store the EARLIEST 
        // elapsed time, not store subsequent values.
        if( sensor_read[ which ] == ?????? ) {

          // record the elapsed time on this iteration
          // of the while() loop as the completion time
          // for this sensor
          sensor_read[which] = elapsed_time;

          // Inside this if() means it is the first
          // and only time this sensor ("which") will
          // be updated.  Therefore, we reduce the 
          // "remaining" count toward 0.
          // Therefore, each decrement corresponds to
          // a unique sensor.
          remaining = remaining - 1;

        } 

    } // end of if( digitalRead() )

  } // end of for() looping through each sensor.

  // Here, we make a final check to see if the 
  // whole read operation is taking too long.
  if( elapsed_time >= timeout ) {

      // Here, you may need to set an appropriate
      // sensor_read[ which ] value to indicate a
      // timeout.  An appropriate initial value of
      // sensor_read[] could mean this step isn't 
      // necessary.

      // Set remaining to 0 to force end of while()
      remaining = 0;
  }


} // end of while( remaining > 0 )

```

The above code extract contains elements of code which may be useful.  However, in it's current format it will not compile or run.  The code represents some useful "ingredients" for you.  

1. Why might it be useful to `#define` how many line sensors are being used at the top of your program?
  - **Help:** we have discussed a serious error when using arrays.
  - **Help:** how many line sensors does the 3Pi+ have?

2. The above example code is missing the operation to calculate the `elapsed_time` on every iteration of the `while()` loop.  We have used this previously.
  - implement a method to record the `start_time` outside the `while()` loop.  Why must this be outside the `while()` loop?
  - implement a calculation of `elapsed_time` inside the `while()` loop. Why must this be inside the `while()` loop?

3. Integrate the above example code into your existing code for a single sensor.  
  - Remember to keep versions of your code as you work.
  - Remember to keep the operation to **enable the IR LEDs** (EMIT pin).

4. Implement a short routine using a `for()` loop (following a similar structure above) to:
  - Operate the capacitor charging for each sensor, `DN1`, `DN2`, `DN3`.
  - Re-configure the sensor pins `DN1`, `DN2`, `DN3` to be read again.
  - Place this **before** the `while( remaining > 0 )` loop - why must this be before the `while()` loop?

5. In the above example, there is the following comment and statement:

```c
        // Check if this sensor has had a previous
        // value of elapsed time stored before.
        // We only want to store the EARLIEST 
        // elapsed time, not store subsequent values.
        if( sensor_read[ which ] == ?????? ) {
```
  - What would be the effect or problem of storing subsequent values?
  - What would be a potential effect of decreasing our `remaining` variable when only 1 sensor is returning `LOW` on `digitalRead()`?
  - We could set the variables `sensor_read[ ]` to a known initial value, aboev represented as `???????`.  If this initial value is seen, the algorithm would know it has not been updated to a value of `elapsed_time`.  Once `elapsed_time` has been recorded into `sensor_read[]`, it would mean the initial value would be lost and this if() statement would not be true again.
  - What initial value would be effective?  There are three sensible answers to this question.  
  - Replace `?????` with your initial value so the code will compile and work.


6. **Validate:** Use your robot, environment, and the Serial Monitor to confirm that your solution is working.
  - Given your experience of the previous exercises - what would you expect to see in a working solution?
  - Given your experience of the previous exercises what would indicate to you something is going wrong?
  - **Help:** Common bugs in this exercise are:
    - Only 1 sensor is being updated: check that you are decreasing the variable `remaining` only once for each sensor (e.g., each decrement must be a unique occurence).
    - The routine always ends with `timeout`: check that the IR LEDs are enabled (EMIT pin).

7. **Evaluate:** Utilise a new set of variables to capture the execution time for the parallel read procedure.  It should take the general format in the example below.  Compare your execution time with your peers:  
  - Have they achieved more efficient code?  
  - What techniques have they used?  
  - Can they explain it to you so that you understand?  
  - Or can you explain your solution to your peer so they understand?
  - **Help**: explaining code or solutions to others is a great way to solve problems and to improve your understanding.  Don't forget that you can also ask a member of teaching staff to help you.  

```c
void loop() {

  // Store the time before.
  unsigned long exec_time_start;
  exec_time_start = micros();

  // Call the parallel sensor read routine we
  // have been working on.
  doParallelSensorRead();

  // Store the time afterwards
  unsigned long exec_time_end;
  exec_time_end = micros();

  // Report total execution time
  Serial.println( (exec_time_end - exec_time_start) );

  // A short delay to keep the timing
  // of this code consistent for now.
  delay(100);

}

```


<hr>
<br><br><br><br>

## Exercise 5: Refactor (30mins)

At this stage, you should now have a number of variables and processes all related to the operation of your ground sensors (line sensors).  Similar to developing code for the motors, this is likely spread across:
- `global` scope
- `setup()`
- `loop()`
- other functions you may have created.

1. **Refactor:** Take a look at your code and consider any elements of code which could be placed into their own functions.  Doing so will improve the readability of your code and likely decrease your time spent debugging errors.  Three good examples are:
  - `enableIRLEDs();`
  - `disableIRLEDs();`
  - `chargeCapacitors()`;

2. **Refactor:** Follow the same process to populate a `class` specifically for the line sensors. 
  - decide if you will use a class to opeate a single line sensor, or all of them together as a subsystem.  Given the above exercises, what might be more computationally efficient or appropriate for our robot?
  - remember to create an `instance` of your `class` in `global` scope of your main sketch file (.ino).
  - remember to create an initialising function within the class to set the initial mode and state of pins.
  - remember to call this initialising function within `setup()`
  - an empty class template named `linesensor.h` is included in the template Arduino sketch available onGithub (<a href="https://github.com/paulodowd/EMATM0053_21_22/tree/main/3PI_CodeStub">Github Page</a>, <a href="https://github.com/paulodowd/EMATM0053_21_22/raw/main/3PI_CodeStub/Labsheet_X.zip">Download Link for Zip file</a>).
  - work slowly and methodically, testing the code compiles as you go.
  - test that your class file is operating correctly with no bugs.


<hr>
<br><br><br><br>

## Exercise 6: Schedule the Line Sensor Read

1. **Decompose the Problem:** Write a very short program to test how fast `loop()` operates with a minimum of code and without any calls to `delay()`:  
  - use `micros()` and calculate the elapsed time, and report this back to your computer Serial Monitor using `Serial.print()`.
  - because we are timing `loop()` itself, you'll need to use a `global` variable to capture the previous time of execution.
  - given the time interval reported, what is this as a frequency in Hertz?

2.  **Hypothesise:** In the example code provided above, why would it be a bad idea to use the following conditional statement? 

```c
      if( elapsed_t == MOTOR_UPDATE ) { 
```

3. In the above example, the following line of code updates a time-stamp (records the count of milliseconds at that moment) within the `if()` statement that calls the `lineSensorRead()` function.  Why is this necessary?  What would happen if this time-stamp was not updated, in terms of code execution?  
  - **Help**: Consider the calculation of `elapsed_t`.

```c
      // Record when this execution happened.
      // for future iterations of loop()
      ls_ts = millis();
```

4. The above code example is **incomplete** and will not compile without errors.  Complete the code example above so that you can upload it to your 3Pi+:
  - If you have not done so already, it is highly recommended to `refactor` your line sensor reading process code into a function, such as `readLineSensors()`.  
    - in C, it is a little tricky to return more than one variable.  For the level of these exercises, it is acceptable to have your function update variables declared in `global scope`.
  - Refer to your work for Labsheet 2 to operate the motors.  You should have written functions for the safe and confident operation of your motors.
  - Add extra functionality to the example:
    - Use `pinMode()` and `digitalWrite()` to activate the built-in LED when the robot is above a black surface. 
    - It is recommended to use the `Yellow LED` referred to in the <a href="https://www.pololu.com/docs/0J83/5.9"> documentation pin assignments </a>.  Remember to use the pin value in the column `Arduino Pin Names`.
    - Exeperiment with moving this LED activation code into the different scheduled tasks, or outside of them within `loop()`.

