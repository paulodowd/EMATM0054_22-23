#include "motors.h"
#include "linesensor.h"
#include "encoders.h"
#include "kinematics.h"
#include "pid.h"

#define LED_PIN 13    // Pin to activate the orange LED
#define BUZZER_PIN 6  //Pin to activate buzzer

//Global Definitions of time intervals
#define LINE_SENSOR_UPDATE 10
#define MOTOR_UPDATE 20



int pitch;
unsigned long ls_ts;
unsigned long motor_ts;



Motors_c motors;
LineSensor_c lineSensor;

boolean led_state;  // Variable to "remember" the state of the LED, and toggle it.

// put your setup code here, to run once:
void setup() {

  Serial.begin(9600);
  delay(1000);
  Serial.println("***RESET***");

  // Setting pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Set initial states
  led_state = false;
  digitalWrite(BUZZER_PIN, LOW);

  pitch = 100;

  ls_ts = millis();
  motor_ts = millis();
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

  //beep (pitch);

  // pitch = pitch + 1;
  // if(pitch > 1500) pitch = 100;

  // Serial.println (pitch);

  // Record the time of this execution
  // of loop for coming calucations
  //  ( _ts = "time-stamp" )
  unsigned long current_ts = millis();
  unsigned long elapsed_t;
  
  float e_line;
  e_line = lineSensor.errorCalc();

  float turn_pwm; 
  turn_pwm = 10;

  turn_pwm = turn_pwm * e_line;

  Serial.print(turn_pwm);
  Serial.print("\n");


  int leftPower = 0 - turn_pwm;
  int rightPower = 0 + turn_pwm;

  Serial.print(leftPower);
  Serial.print(rightPower);

  motors.setPower(leftPower, rightPower);
  motors.leftForward();
  motors.rightForward();


  

  //e_line = lineSensor.errorCalc();
  Serial.print("\n");
  Serial.print(e_line);



  // Run our line sensor update
  // every 100ms (10hz).
  // Tracking time for the line sensor (ls)
  elapsed_t = current_ts - ls_ts;
  //Serial.print(" Elapsed: ");
  //Serial.print(elapsed_t);
  if (elapsed_t > LINE_SENSOR_UPDATE) {

    // Conduct a read of the line sensors
    //lineSensor.parallelSensorRead();
    //lineSensor.errorCalc();
    //motors.stopMotors();
    //motors.leftReverse(20);
    //motors.rightReverse(20);


    // Record when this execution happened.
    // for future iterations of loop()
    ls_ts = millis();
    //Serial.print(" LS: ");
    //Serial.print(ls_ts);
  }

  // Just to test this process:
  // Alternate the motor activation
  // every 2 seconds so that the 3Pi+
  // drives fowards, then backwards.
  elapsed_t = current_ts - motor_ts;
  if (elapsed_t > MOTOR_UPDATE) {
    // Toggle motor direction
    // ...


    // Write motor direction and
    // pwm to motors.
    // ...
    //motors.setPower(20, 50);
    //motors.leftForward();
    //motors.rightForward();

    // Record when this execution happened
    // for future iterations of loop()
    motor_ts = millis();
    //Serial.print(" Motor: ");
    //Serial.print(motor_ts);
  }








  // //beep(500);
  // //FWD
  // motors.leftForward(20);
  // motors.rightForward(20);
  // delay(1000);
  // motors.stopMotors();
  // delay(1000);
  // //REV
  // motors.rightReverse(20);
  // motors.leftReverse(20);
  // delay(1000);
  // motors.stopMotors();
  // delay(1000);
  // //Turn Left
  // motors.leftForward(20);
  // motors.rightReverse(20);
  // delay(1000);
  // motors.stopMotors();
  // delay(1000);
  // //Turn Right
  // motors.rightForward(20);
  // motors.leftReverse(20);
  // delay(1000);
  // motors.stopMotors();
  // delay(1000);
  // //Drive on an arc
  // motors.rightForward(50);
  // motors.leftForward(20);
  // delay(10000);
  // motors.stopMotors();
  // motors.rightForward(255);
  // motors.leftReverse(255);
  // delay(2500);
  // motors.stopMotors();
  // delay(50000);


  //Serial.println("loop");
  //delay(100);
}

void beep(int toggle_duration) {
  digitalWrite(BUZZER_PIN, HIGH);
  delayMicroseconds(toggle_duration);
  digitalWrite(BUZZER_PIN, LOW);
  delayMicroseconds(toggle_duration);
}