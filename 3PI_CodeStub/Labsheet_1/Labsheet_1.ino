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

//Declare my FSM
#define STATE_INITIAL 0
#define STATE_DRIVE_FORWARD 1
#define STATE_FOUND_LINE 2
#define STATE_FOLLOW_LINE 3
// #define STATE_TURN_AROUND 5
// #define STATE_GAP 6


int state;
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
  state = STATE_INITIAL;

  pitch = 100;

  ls_ts = millis();
  motor_ts = millis();
}

// put your main code here, to run repeatedly:
void loop() {

  // Record the time of this execution
  // of loop for coming calucations
  //  ( _ts = "time-stamp" )
  unsigned long current_ts = millis();
  unsigned long elapsed_t;



  //updateState;


  if (state == STATE_INITIAL) {

    motors.initialiseMotor();
    state == STATE_DRIVE_FORWARD;

  } else if (state == STATE_DRIVE_FORWARD) {

    driveForwards();
    //STATE then changed to FOUND_LINE within the driveForwards function

  } else if (state = STATE_FOUND_LINE) {

    led_state = true;
    state == STATE_FOLLOW_LINE;

  } else (state == STATE_FOLLOW_LINE);
  {

    lineFollowing();

    state == STATE_INITIAL;
  }

  







  // Run our line sensor update
  // every 100ms (10hz).
  // Tracking time for the line sensor (ls)
  elapsed_t = current_ts - ls_ts;
  if (elapsed_t > LINE_SENSOR_UPDATE) {

    // Conduct a read of the line sensors
    lineSensor.parallelSensorRead();

    ls_ts = millis();
  }
  elapsed_t = current_ts - motor_ts;
  if (elapsed_t > MOTOR_UPDATE) {


    motor_ts = millis();
  }
}



void beep(int toggle_duration) {
  digitalWrite(BUZZER_PIN, HIGH);
  delayMicroseconds(toggle_duration);
  digitalWrite(BUZZER_PIN, LOW);
  delayMicroseconds(toggle_duration);
}

void updateState() {}

void driveForwards() {


  //lineSensor.parallelSensorRead();
  int centreSensor = lineSensor.sensor_read[2];
  Serial.print(centreSensor);
  Serial.print("\n");

  if (centreSensor <= 1500) {

    motors.setPower(20, 20);
    motors.leftForward();
    motors.rightForward();
   
  
  }

  if (centreSensor >= 1500) {

    motors.stopMotors();
    state == STATE_FOUND_LINE;

  }  //end function
}

void lineFollowing() {


  float e_line;
  e_line = lineSensor.errorCalc();


  float turn_pwm;
  turn_pwm = 20;

  turn_pwm = turn_pwm * e_line;

  // Serial.print(turn_pwm);
  // Serial.print("\n");

  float leftPower = 20 - turn_pwm;
  float rightPower = 20 + turn_pwm;
  leftPower = int(leftPower);
  rightPower = int(rightPower);
  motors.setPower(leftPower, rightPower);
  motors.leftForward();
  motors.rightForward();
}

//off cuts of code to remeber

// // We use the variable to set the
// // debug led on or off on the 3Pi+
// digitalWrite(LED_PIN, led_state);

//beep (pitch);

// pitch = pitch + 1;
// if(pitch > 1500) pitch = 100;

// Serial.println (pitch);

// // Using an if statement to toggle a variable
// // with each call of loop()
// if (led_state == true) {
//   led_state = false;
// } else {
//   led_state = true;
// }