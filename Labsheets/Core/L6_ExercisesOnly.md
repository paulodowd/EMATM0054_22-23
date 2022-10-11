# Labsheet 6: Odometry (Exercises Only)

## Exercise 1: 3Pi+ Encoders

1. Does the 3Pi+ have `absolute` or `incremental` rotary encoders?  (documentation <a href="https://www.pololu.com/docs/0J83/5.4">1</a>, <a href="https://www.pololu.com/product/3081">2</a>)

2. **Hypothesise (Task):** We could say that the encoders detect the rotation of either the motors (`actuators`), or the wheels (`effectors`).  Which of these (motors or wheels) is the more important description of the nature of the information the 3Pi+ will be able to sense?

3. **Hypothesise (Hardware):** The designers of the 3Pi+ attached the encoders to the motors prior to the reduction gearbox.  
  - What is an advantage of this design choice?  
  - What is a disadvantage of this design choice?

<br><br><hr><br><br>

## Exercise 2: Complete the Encoder ISRs

In this exercise you will need to update the `encoders.h` source file so that the code operates correctly.  After previous labsheets, you might be inclined to refactor into a `class`.  However, this code has special function calls to operate `interrupt service routines`, and so it is not suitable for a `class` implementation.  

1. Given we are using the datatype `long` to store the encoder counts, what is the maximum and minimum values that can be stored? 

2. **Hypothesise (software):** When we update the byte variables `state_e1` and `state_e0` to move `current state` into `prior state` at the end of the ISR, we shift to the right `>>`.  We could imagine writing the whole ISR operation to shift `current state` into `prior state` to the left (`<<`) instead.  What would be the problem with this?  

3. Review and update the template provided for you in `encoders.h`:
  - You do not need to change anything in `setupEncoder0()` or `setupEncoder1()`.
  - **Decompose the problem:** Work on one encoder ISR to start with.  Once you have one encoder ISR working, work to complete the second encoder.  
  - Complete the ISR `if()` statement to properly increment and decrement the count value.  
    - Many required conditional statements are missing.
    - You can refer to the tables presented above for assistance.
  - **Validate:** Ensure that you increment and decrement `count_e0` and `count_e1` within the correct ISR routines.
    - A common error is that one ISR is updating the other's count.

  - **Validate:** Use `Serial.print` within `loop()` to check that your encoder values can consistently go up and down, with forward and backward motion.
    - Ensure you add the function calls `setupEncoder0()` and `setupEncoder1()` to your `setup()` routine, otherwise the ISRs won't work.
    - Should forward motion increment values, or decrement values?  There is no correct answer to this question.  Please decide for your implementation.
    - How many encoder counts do you register for a full rotation of a wheel?
      - Is this what you expect?
      - How close is this to the theoretical answer? (<a href="https://www.pololu.com/docs/0J83/5.4">documentation available here</a>).
      - How might you improve your measurement of total encoder counts for a full rotation of a wheel?
      - It is possible that your encoders may deviate from the theoretical number of counts per revolution - what factors might cause this?
      - Given the total encoder counts per revolution of the wheel, what is the angular resolution of 1 encoder count?
      - Given the dimensions of the wheel, how much distance is travelled by the wheel for 1 encoder count?
  - **Refactor:** The functions and variables have been consistently named `e0` and `e1`:
    - determine which is left and right.
    - consider updating the code to rename e0 and e1 to left/right, or l/r, as appropriate.
    - why might this be useful to do?
    
 <br><br><hr><br><br>
 
 ## Exercise 3: Implement Kinematics

1. Review and update the `class` within `kinematics.h` source file of the 3Pi+ Arduino template available via Github (<a href="https://github.com/paulodowd/EMATM0054_22-23/tree/main/3PI_CodeStub">Github Page</a>, <a href="https://github.com/paulodowd/EMATM0054_22-23/raw/main/3PI_CodeStub/Labsheet_X.zip">Download Link for Zip file</a>), or create your own.  In this first exercise, aim to get a reasonable but not perfect level of performance.  Your main goal should be to ensure there are no bugs in your code.
  - You may wish to implement the kinematics within `loop()` until you feel confident it is working, before working within the `class` construct.
  - For estimating position, it is not necessary to attempt to update position with every change to the encoder count.  Instead, decide a reasonable and regular time interval to perform your kinematic update.  
  - Your code will need to know the change in encoder counts since the last time the kinematics was updated.  Create variables to store and update this information.  
    - Start your kinematic update function by ensuring you can register and update a change of encoder counts.
    - Remember to pay attention to variable `data types` and potential bugs.
  - In a previous exercise, you will have calculated some useful information:
    - the total number of encoder counts per revolution.
    - the mm of travel per encoder count.
  - Use either the measurements of the 3Pi+ provided in the <a href="https://www.pololu.com/docs/0J83">documentation</a>, or take your own measurements of $l$ and $r$.  
  - Start by implementing only the $X$ contribution:
    - **Validate:** Moving the robot backwards and forwards (no rotation), check that the values reported for a full rotation of both left and right wheels together appears correct.
    - Moving the robot slowly by hand (no battery power) will likely make this easier.
    - Select a distance, such as 100mm, to validate your kinematics.
  - Imlpement the $\theta$ contribution:
    - When working on $\theta$, test your robot without any translation motion (forwards/backwards).
    - **Validate:** place your robot on a surface with a known angle marked out.  This could be 90&deg;, or a small chart of angles (plenty are available via a <a href="https://www.google.com/search?q=radians+angles&tbm=isch&ved=2ahUKEwjopoDK5ZfzAhUP_RoKHcq5BVYQ2-cCegQIABAA&oq=radians+angles&gs_lcp=CgNpbWcQAzIFCAAQgAQyBQgAEIAEMgYIABAIEB4yBggAEAgQHjIGCAAQCBAeMgYIABAIEB4yBggAEAgQHjIGCAAQCBAeMgYIABAIEB4yBggAEAgQHjoHCCMQ7wMQJzoECAAQQzoGCAAQBRAeUKbLBFiJ1gRg3NYEaABwAHgAgAE6iAGVA5IBATiYAQCgAQGqAQtnd3Mtd2l6LWltZ8ABAQ&sclient=img&ei=_NxNYei4L4_6a8rzlrAF&bih=937&biw=1920&rlz=1C1GCEB_enGB928GB928">Google Image search</a>).  
    - Move your robot by hand to check that it is calculating a good estimation of rotation.
    - **Validate:** Does $\theta$ increment and decrement clockwise and anti-clockwise as you would expect?  

<br><br><hr><br><br>

## Exercise 4: Improve Odometry

1. Look to improve your odometry.  It is recommended that you collect some data and practice graphing using a `boxplot` to evaluate performance.  A `boxplot` example has been provided below.

- Write some motor operation code so that your robot will drive forwards until it reaches a set distance.
  - For this exercise, do not use time to travel a distance.  Instead, write code to control motors via your global co-ordinate $X$ value.
  - **Evaluate:** Take measurments of your robot's stopping distance, both in terms of the internal measurement (odometry) and the external reality (`ground truth`).
    - Does your robot `overshoot` (stop late), or `undershoot` (stop early)?  
    - How is this visible on your boxplot?
    - Is this a problem with your motor control, or an error in kinematics?
    - In the procedure you have adopted to measure distance, how might you improve the precision and accuracy of your measurements, or your capability to record error?
  - **Hypothesise:** Given the form of the update equations, which parameter is most likely to effect the performance of the $X_{R}$ contribution?  
    - Adjust likely parameters to improve the performance, and repeat your evaluation.
    - Why might parameters deviate from the documented values?
  - **Note:** At this stage in the labsheets, your robot may still accrue some rotation during this forward/backward movement.  We will investigate how to control for this in the next labsheet covering PID.  

- Write some motor operation code so that your robot will rotate on the spot to a specific angle.
  - For this exercise, do not use time to perform a rotation.  Instead, write code to control motors via your global co-ordinate $\theta$ value.
  - **Evaluate:** Perform similar evaluations as the above.  Take a number of measurements to `characterise` the performance of your robot. 
    - In the procedure you have adopted to measure distance, how might you improve the precision and accuracy of your measurements, or your capability to record error?
  - **Hypothesise:** Make a similar hypothesis on which parameter most effects the $\theta$ contribution.  Explore parameters to see if you can improve the error when your robot rotates on the spot.

- Consider the observations you have made of translation and rotation movement for your robot.
 - **Hypothesise:** Which of these generates the more significant error in your odometry.  Discuss:
  - possible causes within your robotic system, across environment, hardware, software and task.
  - a rationale for why rotation or translation has the greater impact.
  
<br><br><hr><br><br>

## Exercise 5: Improve Kinematics

**For the line following challenge, the simple kinematic model provided is sufficient to enable your robot to travel back to where it started with reasonable performance.  The exercises in this section can be considered optional or suitable for further work.**  

In the simple model detailed in this labsheet, we have worked with the assumption that the robot will move or rotate, exclusively (either one or the other). As such, our model translates by some amount $X_{R}$ and then rotates this translation motion by some $\theta_{R}$.  These operations are accounted for by the following motor activations:

- when left and right motors have equal non-zero velocity and in the same direction, $v_{l} = v_{r} \ne 0$, the robot will move forwards or backwards in a straight line.
- when the left and right motors have equal non-zero and inversed velocity, $v_{l} = -v_{r} \ne 0$, the robot will rotate on the spot.

This presents the exceptional case when the left and right motor are of different velocity, including cases where one my be 0.  Under these conditions, the robot will move on an arc. 

In our simplified model, we assume that travel on an arc can be sufficiently approximated by the integrating the rotation of the straight line segments generated by $X_{R}$.  

When the wheels have differing velocity, the point of rotation for the movement moves away from point $p$.  This new point of rotation is referred to as the `instantaneous centre of rotation` (ICR).  The more similar the wheels speeds, the further the ICR moves from point $p$.


1. As a matter of interest:
  - **Hypothesise:** If the ICR moves away from point $p$, and so defines an arc of travel for the robot, will the simplified model under-estimate or over-estimate the resultant position in comparison?
2. Implement ICR and the kinematic update routine. 
  - If you need help with this exercise, discuss the matter with the teaching staff. They will help you to decide if you should insatead continue further with labsheets and come back to this later.
  - When working on this implementation, be aware of divide-by-zero errors.
  - Any gain in performance from this implementation is likely to be more pronounced and visible when you address the full line following challenge, especially the return to home objective.  Therefore, you may need to return to this exercise later.  




 
