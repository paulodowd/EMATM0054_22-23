# Labsheet 5: Finite State Machine (Exercises Only)


# Exercise 1: Drawing a simple FSM on Paper (15minutes)

Please feel free to discuss these exercises with your peers and tutors:

1. In the above discussion, a one of the states was called `drive forwards`.  We could also name this as `join line`, since this is the desired activity we wish to observe.  Why might `drive forwards` and `join line` be usefully decomposed into two different states?

2. Draw a FSM for the above states.
    - Decide on some useful state names that you can use in code as status flags, such as "STATE_INITIALISE".
    - Annotate your FSM to include the `proprioceptive` and `exteroceptive` information used to inform when a `transition` is needed between `states`.
    - Remember to include elements such as a `time out` if the robot does not encounter a line whilst in the `driving forwards` state.
    - Make notes on your FSM to about pieces of code or techniques that you have developed which will be relevant.
    - If you have not used the on-board LEDs or audible buzzer, you may wish to investigate the built in examples.  These will be useful to signal the activity of the robot to you.
      - why might using the Serial Monitor be problematic?
 
    


<br><br>
<hr>
<br><br>


# Exercise 2:  Code your 3 state FSM

You should now begin to code the 3 state FSM you drew on paper.  Start by coding the framework for your FSM, including:
- a global variable to track which state your system is in.
- `#define` or global variables to enumerate each possible state with a meaningful name.
- routines in `setup()` to initialise your global variables.
- an `if() {} elseif() {}` code block within `loop()` to select appropriate functions for each state.
- test functions associated to each state.


The following code extract provides a minimum framework for you to use.  
- Write in, or copy-and-paste in, code from your previous work, where it is relevant.  You will need all the setup routines for motors, encoders, line sensors, etc. Keep your code as tidy as possible, things will get harder to debug as you increase the system complexity.


- Save **versions** of your code - espcially if you get something working!  When something goes wrong, it is often useful to go back to the last best known working version.
 
 
- Remember that you can use **global variables** to make information available to all parts of your code.  However, global variables will keep their last assigned value, so you'll also have to remember to reset them if need be.

    
- Add **Serial.println()** at key points in your code to track of which state the robot is operating in.  You can remove these later.


- Remember to go back and look at labsheets if you have forgotten something.

<br><br>
<hr>
<br><br>

# Exercise 3:  Build up your FSM

Now incrementally add behaviours to your FSM and ensure that transitions happen when you expect them to.  

- Break down the line following challenge into sub tasks.  Note that, this probably isn't just the different components of the line.  You may need small sub-behaviours between components of the line. You may even require small transition states within your code to set variables.   At this stage, consider adding the following states and behaviours to your robot:
  
- Add code so that your robot indicates a state change to you before moving on to the next system state.  This could be an LED or a beep.

- Return to paper based drawings of the FSM to keep track of how to write your code.  

- Remember that you can use *millis()* to create timestamps and check for elapsed time.  This might be useful to check if you have lost the line, or to wait without using delay().

- Experiment with stating your robot into different states, and disabling states.  Using a FSM can become very useful for debugging code.

- Consider adding a special `debug` state, which you can utilise for general debugging at any point.
    
