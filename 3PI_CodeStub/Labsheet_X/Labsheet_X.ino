#include "motors.h"
#include "linesensor.h"
#include "encoders.h"
#include "kinematics.h"
#include "pid.h"

#define LED_PIN 13  // Pin to activate the orange LED
boolean led_state;  // Variable to "remember" the state
                    // of the LED, and toggle it.


// put your setup code here, to run once:
void setup() {

  Serial.begin(9600);
  delay(1000);
  Serial.println("***RESET***");

  // Set LED pin as an output
  pinMode(LED_PIN, OUTPUT);

  // Set initial state of the LED
  led_state = false;
}


// put your main code here, to run repeatedly:
void loop() {

  // Using an if statement to toggle a variable
  // with each call of loop()
  if (led_state == true) {
    led_state = false;
  } else {
    led_state = true;
  }

  // We use the variable to set the
  // debug led on or off on the 3Pi+
  digitalWrite(LED_PIN, led_state);

  Serial.println("loop");
  delay(500);
}