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
#define LINE_LOST_UPDATE 1000

// //Declare my FSM
// #define STATE_INITIAL 0
// #define STATE_LOST_LINE 1
// #define STATE_DRIVE_FORWARD 2
// #define STATE_FOUND_LINE 3
// #define STATE_FOLLOW_LINE 4
// // #define STATE_TURN_AROUND 5
// // #define STATE_GAP 6

int Line = 0;
int state = 0;
int pitch;
unsigned long ls_ts;
unsigned long motor_ts;
unsigned long linelost_ts;


Motors_c motors;
LineSensor_c lineSensor;

boolean led_state;  // Variable to "remember" the state of the LED, and toggle it.
boolean lineFound;  // Variable to know when the line has been found
boolean lineLost;


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
  //state = STATE_INITIAL;
  lineFound = false;
  lineLost = false;

  pitch = 100;

  ls_ts = millis();
  motor_ts = millis();
  linelost_ts = millis();
}

// put your main code here, to run repeatedly:
void loop() {

  // Record the time of this execution
  // of loop for coming calucations
  //  ( _ts = "time-stamp" )
  unsigned long current_ts = millis();
  unsigned long elapsed_t;

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


  switch (Line) {
    case 0:
      motors.initialiseMotor();
      Line = 1;
      break;
    case 1:
      //are all 3 sensors on white
      lineFound = false;
      if (lineSensor.sensor_read[1] && lineSensor.sensor_read[2] && lineSensor.sensor_read[3] < 1500) {
          if (lineFound = false) { 
          driveForwards();
          Line = 2;
        }
      }
      break;
    case 2:
      //if all 3 sensors are black stop turn to the right
      if (lineSensor.sensor_read[1] && lineSensor.sensor_read[2] && lineSensor.sensor_read[3] > 1500) {
        if (lineFound = false) { 
          turnOn();
          //lineFound = true;
          Line = 1;
        }
      }
      Line = 3;
      break;
    case 3:  //Line lost
      //when the sensors have been all white for 3 seconds turn around 180 deg
      if (lineSensor.sensor_read[0] && lineSensor.sensor_read[1] && lineSensor.sensor_read[2] && lineSensor.sensor_read[3] && lineSensor.sensor_read[4] < 1500) {
         if (lineFound = true) {
        lineLost = true;
        linelost_ts = millis();
        motors.stopMotors();
      }
    }

  elapsed_t = linelost_ts;

  if (elapsed_t > LINE_LOST_UPDATE) {
      if (lineLost = true) {
      turnAround();
      linelost_ts = millis();
    }
  }
  Line = 0;
  break;
  }
}








void beep(int toggle_duration) {
  digitalWrite(BUZZER_PIN, HIGH);
  delayMicroseconds(toggle_duration);
  digitalWrite(BUZZER_PIN, LOW);
  delayMicroseconds(toggle_duration);
}



void driveForwards() {

  motors.setPower(25, 25);
  motors.leftForward();
  motors.rightForward();
}

void turnOn() {
  motors.stopMotors();
  delay(5000);
  motors.setPower(40, 0);
  motors.rightForward();
  motors.leftForward();
  delay(2150);
}

void turnAround() {
  motors.stopMotors();
  delay(2000);
  motors.setPower(40, 40);
  motors.leftForward();
  motors.rightReverse();
  delay(2000);
}
void lineFollowing() {

  lineFound = false;

  float e_line;
  e_line = lineSensor.errorCalc();

  float turn_pwm;
  turn_pwm = 20;

  turn_pwm = turn_pwm * e_line;

  // Serial.print(turn_pwm);
  // Serial.print("\n");

  float leftPower = 20 - turn_pwm * 2;
  float rightPower = 20 + turn_pwm * 2;
  leftPower = int(leftPower);
  rightPower = int(rightPower);
  motors.setPower(leftPower, rightPower);
  motors.leftForward();
  motors.rightForward();

  if (e_line < 0.1) {
    if (lineSensor.sensor_read[2] > 1500 ){
    lineFound = true;
    }
  }
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


// if (state == STATE_INITIAL) {

//     motors.initialiseMotor();
//     state = STATE_LOST_LINE;

//   } else if (state = STATE_LOST_LINE) {

//     motors.setPower(20, 20);
//     motors.leftForward();
//     motors.rightForward();
//     Serial.print("driving");

//   if (lineSensor.sensor_read[1] v && lineSensor.sensor_read[2] && lineSensor.sensor_read[3] > 1500) {
//       motors.setPower(0, 20);
//       motors.leftForward();
//       motors.rightForward();
//       delay(1150);
//       Serial.print("turned");
//       lineFound = true;
//       state = STATE_DRIVE_FORWARD;
//       Serial.print(state);
//       Serial.print("\n");

//     } else if (state == STATE_DRIVE_FORWARD) {
//       Serial.print(state);
//       Serial.print("Driving Forward ");
//       Serial.print("\n");
//       motors.setPower(20, 20);
//       motors.leftForward();
//       motors.rightForward();

//      }if (lineFound = true) {

//         state = STATE_FOUND_LINE;
//       }
//       if (lineFound = false) {

//         state = STATE_LOST_LINE;


//       }else if (state = STATE_FOUND_LINE)

//         led_state = true;
//         state = STATE_FOLLOW_LINE;

//     } else if(state == STATE_FOLLOW_LINE){

//       Serial.print(state);
//       Serial.print("\n");
//       lineFollowing();
//       state = STATE_DRIVE_FORWARD;
//     }
//   }