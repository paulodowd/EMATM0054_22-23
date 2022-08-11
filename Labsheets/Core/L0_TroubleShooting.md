# Trouble Shooting

This labsheet covers the following topics:

1. <a href="https://github.com/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Core/L0_TroubleShooting.md#1-i-cant-upload-my-code-to-the-3pi--romi-it-wont-connect"> No Serial Port / I can't upload my code to the 3Pi+.</a>
2. I can't upload my code on Ubuntu (linux)
3. My float calculation isn't working
4. My if() statement isn't working.
5. Faster / Slower / Strange behaviour with Serial.print()
6. Switch Case warning.

<br><br><br><br>

## 1. No Serial Port / I can't upload my code to the 3Pi+.

The 3Pi+ can sometimes lose its ability to connect to your computer. 
You can find <a href="https://www.pololu.com/docs/0J83/10.1">official documentation on how to fix this here</a>.
You can also follow these steps to fix it. 
On rare occasions, this problem can keep re-occuring, but this method can be repeated quickly and easily.

### Step1
- Open the Arduino IDE
- Open the Blink Example
- Go to File -> Examples -> Basics -> Blink
- Check that the board type Arduino Leonardo is selected
- Go to Tools -> Board -> Select Arduino Leonardo from the list.
### Step 2
- Enable Show verbose output during: upload
- Go to File -> Preferences
- Check the upload tick box, so that it is ticked.

<p align="center">
<img src="https://github.com/paulodowd/EMATM0054_22-23/blob/main/Images/verbose_upload.png?raw=true">
</p>

### Step 3
- Plug in your Romi to your computer via the USB cable.
- Your computer might say "device not recognised", don't let this trouble you.
- Go to Tools -> Port and make a note of which ports are available. You may have many or none.

### Step 4
- Press the reset button twice - quickly
- The reset button is circled red in the image below.
- When you do this correctly, you should see the built in LED fading (cirlced green on Romi image).
- Note that, thetes LED should fade in and out, not blink on and off.

### Step 5
Whilst the LED is fading:
- Go to Tools -> Port and select the newest Port which has shown up.
- If there isn't a new port, select the one with the highest value (e.g., COM10)
- Wait for the Fading LED to go out.
- If you check Tools -> Port again, this new port may have gone. This is OK.

### Step 6
- Click the upload icon to upload the Blink code to your Romi.
- Wait for the code to compile. Wait until the Arduino IDE is searching for the port to connect to. You will see something like the the white text appearing in the image below.
- When you see the Arduino IDE searching for a port, press the reset button twice (quickly) again to get the fading LED.

<p align="center">
<img src="https://github.com/paulodowd/EMATM0054_22-23/blob/main/Images/searching_for_port.png?raw=true">
</p>

### Step 7
- Wait, and you should see text like the below image confirming the correct upload. 
- If not, try the process again. Sometimes it can go wrong if you don't successsfully double-press the reset button quickly enough. 
- If, after a few attempts, you cannot get this to work, contact one of the teaching staff for the unit.

<p align="center">
  <img src="https://github.com/paulodowd/EMATM0054_22-23/blob/main/Images/success.png?raw=true">
  </p>

### Step 8
- share this technique with your peers if they need help.

<br><br><br><br>

## 2. I can't upload my code on Ubuntu (linux)

### Disabling ModemManager in Linux
If you are using Linux and have trouble following the instructions above, your issue might be caused by a program called ModemManager. This program automatically connects to serial ports and sends modem commands to them, interfering with other software using those ports. You can run `ps ax | grep -i Modem` to see if ModemManager is running. On Ubuntu, the command to permanently disable ModemManager is:

`sudo systemctl disable ModemManager`

**You should also check that you have access rights to the Serial port as it appears on your system.** If you install Arduino through a package manager (e.g. `apt get intall`), this may have been resolved for you.

<br><br><br><br>

## 3. My float calculation isn't working

If you are performing a calculation and your result is always 0 or NaN, it is highly likely that you have an issue with the type of your variable. Remember that an integer, long, char, byte (etc) can only represent a whole number, whilst a float or a double can store fractional parts. Therefore, dividing two integers (or other similar type) will often result in a rounding error.

When we are writing calculations for the Arduino it is important to understand a general rule:

read the operation from right-to-left, excepting the normal mathematical rules.
It is good practice to assume the compiler (or Arduino) is very stupid, and will make the worst choice for you. Therefore, you should try to make sure you are always using the appropriate variable type. If you have a good (smart) compiler which handles types well, lucky you! But why take that risk?

The following example within Arduino 1.8.13 will always report a result of 0, when (if done properly) it should report 0.5:
```c
  float result;
  int a;
  int b;

  a = 1;
  b = 2;

  result = a / b;

  Serial.println( result );
```
In the above, if we read left-to-right, it appears as if the following line is going to operate as a float:

`result = a / b;`

...because we declared result as a float. However, if we annotate our types and re-read the line from right-to-left:

`[float]result = [int]a / [int]b;`

...we can see that a/b takes place as integers. In this case, the compiler assumes the type on the right-hand side is (int), and executes the operation as int in working memory, and only afterwards stores the result into a float. So your result will always store a 0 (rounding error).

To perform the above calculation a safer manner, the calculation can be broken into explicit steps, making use of typecasting, which also helps with the readability of your code:
```c
  float result;
  int a;
  int b;

  a = 1;
  b = 2;

  result = (float)a;
  result = result / (float)b;

  Serial.println( result );
```
You will also see this phenomenon when working with hard-coded constants ("magic numbers"). The following code example will also produce a result of 0 on Arduino 1.8.13:
```c
  float result;
  result = 1 / 2;
  Serial.println( result );
```
In the above, "1" and "2" have not been declared as variables, and therefore the compiler has to make a decision for you about what type they are. Because they are written as whole numbers, the compiler decides they are integers, causing the same error as above.

You can work successfully with declared constants with the following minor adjustment, which prompts the compiler to treat the numbers as type float:
```c
  float result;
  result = 1.0 / 2.0;
  Serial.println( result );
```


<br><br><br><br>
### I'm using a float for a calculation but I always get a result of 0

If you are performing a calculation and your result is always 0 or `NaN`, it is highly likely that you have an issue with the **type** of your variable.  Remember that an `integer`, `long`, `char`, `byte` (etc) can only represent a whole number, whilst a `float` or a `double` can store fractional parts. Therefore, dividing two integers (or other similar type) will often result in a rounding error.   

When we are writing calculations for the Arduino it is important to understand a general rule: 
- **read the operation from right-to-left**, excepting the normal mathematical rules.

It is good practice to assume the compiler (or Arduino) is very stupid, and will make the worst choice for you.  Therefore, you should try to make sure you are always using the appropriate variable type.  If you have a good (smart) compiler which handles types well, lucky you!  But why take that risk?

The following example within Arduino 1.8.13 will always report a result of 0, when (if done properly) it should report 0.5:
```c
  float result;
  int a;
  int b;

  a = 1;
  b = 2;

  result = a / b;
  
  Serial.println( result );
```
In the above, if we read left-to-right, it appears as if the following line is going to operate as a float:
```c
  result = a / b;
```
...because we declared `result` as a `float`.  However, if we annotate our types and re-read the line from right-to-left:

```c
  [float]result = [int]a / [int]b;
```
...we can see that `a/b` takes place as integers.  In this case, the compiler assumes the type on the right-hand side is (`int`), and executes the operation as `int` in working memory, and only afterwards stores the result into a `float`.  So your `result` will always store a 0 (rounding error).

To perform the above calculation a safer manner, the calculation can be broken into explicit steps, making use of <a href="https://www.arduino.cc/en/Reference/Cast">typecasting</a>, which also helps with the readability of your code:
```c
  float result;
  int a;
  int b;

  a = 1;
  b = 2;

  result = (float)a;
  result = result / (float)b;
  
  Serial.println( result );
```


You will also see this phenomenon when working with hard-coded constants ("magic numbers").  The following code example will also produce a result of 0 on Arduino 1.8.13:


```c
  float result;
  
  result = 1 / 2;
  
  Serial.println( result );
```

In the above, "1" and "2" have not been declared as variables, and therefore the compiler has to make a decision for you about what type they are.  Because they are written as whole numbers, the compiler decides they are `integers`, causing the same error as above.  

You can work successfully with declared constants with the following minor adjustment, which prompts the compiler to treat the numbers as type `float`:

```c
  float result;
  
  result = 1.0 / 2.0;
  
  Serial.println( result );
```

### My if() statement isn't working

The following compiles without any errors or warnings, but should be considered **incorrect**:

```c
if( 1 < x < 10 ) {
    
}
```

The behaviour of the above is unknown.  A safer, better determined syntax is available.  In C and Arduino, the condition of an if() statement is evaluated to be either true or false as a single entity.  **The above would be better written as**:

```c
if( ( 1 < x ) && ( x < 10 ) ) {
    
}
```

In the above:
- the right-hand condition is evaluated, `1 < x` (true or false)
- the left-hand condition is evaluated, `x < 10` (true or false)
- both results are then evaluated together against `&&` (true of false)
- which results in a single conditional evaluation to pass or fail as true or false.

If we return to the first example, we can imagine `x` has a value of 1:

```c
if( 1 < 1 < 10 ) {
    
}
```

When we attempt to resolve this statement, we can consider that:
- `( 1 < 1 )` is false.
- `( 1 < 10 )` is true.

We don't know whether the machine code will resolve to fail the left-side, or pass the right-side.  So if you wish to make more than one conditional evaluation:
- you should use the `&&` and `||` operators
- or use multiple nested if() statements.

### Another common problem with if() statements:

Another common problem with if() statements is to use the single equals sign `=` which acts as an assignment of value (stores a value), rather than the double equals sign which acts as as evaluation.  Again, unfortunately, the compiler will not prompt you with a warning or error:

```c
int a = 1;
int b = 2;

// This is incorrect.
// a will be assigned b's value.
if( a = b ) {
    // This will run if 'a' receives a positive, non-zero value.
}

// This is correct.
// a will be evaluated against b.
if( a == b ) {
    
}

```

### Yet another common problem with if() statements

It is valid syntax to use an if() statement without curly-braces `{}`.  This can be useful if you have only one line of code to operate.  However, it is advised you always use curly-braces to avoid any potential confusion.  Consider the following example:

```c
if( a == b ) 
    processA();
    discardB();
```

In the above function, it looks like `processA()` and `processB()` will run as a result of the if() statement.  In fact, the way the above will resolve is as following:

```c
if( a == b ) {
    processA();
}
discardB();   //this will always happen, regardless of the if()
```

This can also be confusing if else statements are used, for the same reason:


```c
if( a == b )
    processA();
else
    processB();
    discardA();
```

Again, the above will actually resolve to behave as the following:

```c
if( a == b ) {
    processA();
} else {
    processB();
}
discardA();
```

To save yourself time debugging, make a habit of always using curly-braces - that way the intention of your code is always clear.




<br><br><br><br>


## 4. Faster / Slower / Strange behaviour with Serial.print()

There is a known issue with `Serial.print` and `Serial.println` on the Romi.  You may find that your Romi becomes irratic or the timing of its behaviour changes when you unplug the USB cable.  Sometimes, you may unplug your Romi and it works fine for 2 minutes, and then goes crazy. This appears to be an error with Serial Print.

There are two steps required to fix this problem.  

### Step 1:

Include the following code at the top of your main program (the first tab in the Arduino IDE):

```c
#include <USBCore.h>    // To fix serial print behaviour bug.
u8 USB_SendSpace(u8 ep);
#define SERIAL_ACTIVE (USB_SendSpace(CDC_TX) >= 50)
```

Note that, if you use `Serial.print` or `Serial.println` within other source files, you may need to include this at the top of those files too.  Try to compile your code without it, and see if there are useful errors.  

### Step 2:

At every location you use `Serial.print` or `Serial.println`, you should wrap your code in the following way:

```c
if( SERIAL_ACTIVE ) {

  Serial.print("An example");
  Serial.println(" of fixing the serial bug");
}
```

This will allow you to plug in and remove the USB cable without effecting the performance of your Robot.  

Note that, you can also use `if( SERIAL_ACTIVE ) { }` to create different behaviours depending on whether your robot is plugged into USB or not.


<br><br><br><br>

## 5. Switch Case Warning

From previous experience on this unit, there is occasionally an issue where the standard `switch case` selection mechanism does not operate properly.  You may find that even though your conditional statement is valid, the `switch case` fails to enter the valid case and execute code.  It is not known why this happens - presumably there is a bug in the compiler.

**It is strongly advised to avoid using a Switch Case statements.** Even though this bug is intermittent, it is best to not risk encountering the error.

A switch case looks like:

```c
switch( my_variable_to_evaluate ) {
        
    case value_1: someCode1();
        break;
    case value_2: someCode2();
        break;
        // etc
    default:
        someCode3();
}
```

The same functionality can be gained with `if()elseif` statments, such as:

```c
if( my_variable_to_evaluate == value_1 ) {
    someCode1();
} else if( my_variable_to_evaluate == value_2 ) {
    someCode2();
} else {  // behaves like default:
    someCode3();
}
```
