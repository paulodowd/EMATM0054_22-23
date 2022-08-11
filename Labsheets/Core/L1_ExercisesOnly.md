# Labsheet 1: Getting Started, Uploading, Debugging (Exercises Only)

## Exercise 1: Pololu 3Pi+

1. **Hypothesise (task):** The above image was annotated with `front` and `rear` with respect to the robot chassis.  In theory, the robot can be driven in either direction, regardless of front or rear.  What rationale or justification would you use to support the provided sense of robot direction?
  - **help:** consider:
    - the task requirements we have of line following.
    - the behaviour(s) we might expect from the robot.
    - the physical configuration of the hardware.
    - the `perception`, `decision making` and `actuation` of the robot.

2. **Hypothesise (hardware):** The robot has a ball-caster:
  - Why might this have been included in the design?
  - Why would the ball-caster be more suited at the rear of the robot?
  - What is the difference between a ball-caster and a caster-wheel?  

3. **Hypothesise (task):** In these labsheets, exercises will be given to focus on using the 3 central ground sensors.  When might the left-most and right-most peripheral ground sensors be useful?

<hr>
<br><br><br><br>

## Exercise 2: Upload an Example

1. What is meant by `non-volatile` storage?  What is `volatile` storage or memory?

2. Review the <a href="https://www.arduino.cc/reference/en/">Arduino Reference</a>, investigating any functions that might seem useful.  It is probably a good idea to bookmark this page in your web-browser.

3. Upload the Blink example sketch to the 3Pi+:
  - tell the IDE which type of microcontroller you wish to upload code to. To do this, select: 
    - `Tools --> Board --> Arduino Leonardo`. 
  - tell the IDE which serial port the arduino is connected to. Select:
    - `Tools --> Port --> COM X (Arduino Leonardo)`
    - The correct port may be given different names on PC, Mac and Linux.
  - Plug your 3Pi+ to the computer with an appropriate USB cable.
  - Press the `upload` button on the Arduino IDE. 
  - **Help**: If you have significant issues, read through Labsheet 0: Troubleshooting.  You can also contact a member of the teaching staff.

4. Modify the example code to blink the LED at 5hz.

<hr>
<br><br><br><br>

## Exercise 3: Using Variables

1. Add code to the main loop of the Blink example which stops the LED from flashing after 10 flashes.
    - **Help:** you will need to use an `if()` conditional statement (selection) to check the status of a variable you create to count up to 10.  You can think of this as a way to branch your code (go one direction or another).  As a template, you might want to structure your code like:

```c

if( my_count < 10 ) {
        // do flashing LED behaviour
} else {
        // just keep the LED off.
}

```

  - When you have created your solution, ask yourself questions about what type of errors it may generate over time:
    - does your counting stop at 9, 10, or 11?  How could each of these stopping conditions occur?
    - what would happen if your code starts counting from a negative value?


<hr>
<br><br><br><br>

## Exercise 4: Using Functions

1. Write a function to rapidly toggle the buzzer on your 3Pi+, so that we can hear it beep:
  - Write your function so that everytime it is called the buzzer switches on and then off.  Use `digitalWrite()` to achieve this. 
  - Go to <a href="https://www.pololu.com/docs/0J83/5.9">the pin assignment section of the documentation</a> and find which pin is used to control the buzzer.  You will want to use the value found in the `Arduino pin names` column within your code.
  - Start by using the `delay()` function with a value of 5.  Once this works, what happens to the sound with different argument values provided to `delay()`?
  - **Help**: use the same `pinMode()` and `digitalWrite()` functions we have seen used earlier in this labsheet.  Remember to update which pin you are using.
  - **Help**: are we using the buzzer an `INPUT` to the system, or an `OUTPUT` from the system?
  - **Help**: it is good practice to use `#define` at the top of your program (`global scope`) to set parameters which will not change for the duration of your program.  In this case, the buzzer pin will not change.  Your code will then also be easier to read:

```c
#define BUZZER_PIN ?

// later...
digitalWrite( BUZZER_PIN, ?? );

```

2. Replace `delay()` with `delayMicroseconds()` (<a href="https://www.arduino.cc/reference/en/language/functions/time/delaymicroseconds/">reference page</a>), what happens to the sound?  
  - **Help**: You may need to explore different values sent to `delayMicroseconds()`.
  - **Help**: You can operate the buzzer outside of the human range of hearing.  You should experiment with your time interval between calls to analogWrite().  You might only hear a mechanical clicking, and not the ultrasonic or subsonic tone-sound.
  - **Help**: The buzzer is a useful way to debug your 3Pi+ behaviours but it can get annoying.  You can use a bit of blu-tack or tape to cover the hole of the buzzer to make the beeping much softer to your delicate human ears.

<p><br></p>

3. Write an improved function to control the buzzer which takes an argument to control the duration that the buzzer is on and off.  
  - **Help**: Here is an example function to complete:

```c
void beep( int toggle_duration ) {

}
```  

<p><br></p>

4. Utilise a `global variable` so that every time your main `loop()` iterates it sends an incrementing value to your beep function.  




<hr>
<br><br><br><br>


## Exercise 5: Serial Output

1. Intergrate the above example code with your work from Exercise 4.  Report the current `toggle_duration` being used in your beep function for the buzzer.
  - **Help:** If you do not include a `newline` in your Serial print statement, you will see a long stream of numbers running across the Serial Monitor.  There are two ways to include a `newline`
    - `Serial.println()`, println automatically adds a `newline`.  This is convenient.  However, sometimes you will need to print multiple numbers to a single line, so you would not want a `newline`.
    - `Serial.print("\n");` print does not automatically include a `newline`, but you can add one manually with the `"\n"` special character.  You can also use print in this way to add a comma, e.g. `Serial.print(",");`
    

