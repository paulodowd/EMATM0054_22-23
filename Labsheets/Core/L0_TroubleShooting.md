# Trouble Shooting

This labsheet covers the following topics:

1. <a href="https://github.com/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Core/L0_TroubleShooting.md#1-i-cant-upload-my-code-to-the-3pi--romi-it-wont-connect"> No Serial Port / I can't upload my code to the 3Pi+.</a>
2. I can't upload my code on Ubuntu (linux)
3. I'm using a float for a calculation but I always get a result of 0.
4. My if() statement isn't working.
5. The Timing of my Code changes with Serial.print().
6. Switch Case warning.

<br><br><br><br>

## 1. No Serial Port / I can't upload my code to the 3Pi+.

The 3Pi+ can sometimes lose its ability to connect to your computer. 
Follow these steps to fix it. On rare occasions, this problem can keep re-occuring, but this method can be repeated quickly and easily.

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

### Step 7
- Wait, and you should see text like the below image confirming the correct upload. 
- If not, try the process again. Sometimes it can go wrong if you don't successsfully double-press the reset button quickly enough. 
- If, after a few attempts, you cannot get this to work, contact one of the teaching staff for the unit.

### Step 8
- share this technique with your peers if they need help.

<br><br><br><br>

## 2. I can't upload my code on Ubuntu (linux)

### Disabling ModemManager in Linux
If you are using Linux and have trouble following the instructions above, your issue might be caused by a program called ModemManager. This program automatically connects to serial ports and sends modem commands to them, interfering with other software using those ports. You can run `ps ax | grep -i Modem` to see if ModemManager is running. On Ubuntu, the command to permanently disable ModemManager is:

`sudo systemctl disable ModemManager`

**You should also check that you have access rights to the Serial port as it appears on your system.** If you install Arduino through a package manager (e.g. `apt get intall`, this may have been resolved for you.

<br><br><br><br>

## 3. I'm using a float for a calculation but I always get a result of 0

If you are performing a calculation and your result is always 0 or NaN, it is highly likely that you have an issue with the type of your variable. Remember that an integer, long, char, byte (etc) can only represent a whole number, whilst a float or a double can store fractional parts. Therefore, dividing two integers (or other similar type) will often result in a rounding error.

When we are writing calculations for the Arduino it is important to understand a general rule:

read the operation from right-to-left, excepting the normal mathematical rules.
It is good practice to assume the compiler (or Arduino) is very stupid, and will make the worst choice for you. Therefore, you should try to make sure you are always using the appropriate variable type. If you have a good (smart) compiler which handles types well, lucky you! But why take that risk?

The following example within Arduino 1.8.13 will always report a result of 0, when (if done properly) it should report 0.5:
```
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
```
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
```
  float result;
  result = 1 / 2;
  Serial.println( result );
```
In the above, "1" and "2" have not been declared as variables, and therefore the compiler has to make a decision for you about what type they are. Because they are written as whole numbers, the compiler decides they are integers, causing the same error as above.

You can work successfully with declared constants with the following minor adjustment, which prompts the compiler to treat the numbers as type float:
```
  float result;
  result = 1.0 / 2.0;
  Serial.println( result );
```
