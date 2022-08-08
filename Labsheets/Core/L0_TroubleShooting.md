# Trouble Shooting

This labsheet covers the following topics:

1. <a href="https://github.com/paulodowd/EMATM0054_22-23/blob/main/Labsheets/Core/L0_TroubleShooting.md#1-i-cant-upload-my-code-to-the-3pi--romi-it-wont-connect">I can't upload my code to the 3Pi+ / Romi, it won't connect.</a>
2. I can't upload my code on Ubuntu (linux)
3. I'm using a float for a calculation but I always get a result of 0.
4. My if() statement isn't working.
5. The Timing of my Code changes with Serial.print().
6. Switch Case warning.

## 1. I can't upload my code to the 3Pi+ / Romi, it won't connect.

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
