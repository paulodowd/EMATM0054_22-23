#include "motors.h"
#include "linesensor.h"
#include "encoders.h"
#include "kinematics.h"
#include "pid.h"

#define LED_PIN 13    // Pin to activate the orange LED
#define BUZZER_PIN 6  //Pin to activate buzzer

//Global Definitions of time intervals
#define LINE_SENSOR_UPDATE 40
#define LINE_LOST_UPDATE 1000

int Line = 0;
int pitch;
unsigned int lineLostCount;
unsigned long ls_ts;
unsigned long motor_ts;
unsigned long linelost_ts;


Motors_c motors;
LineSensor_c lineSensor;

boolean led_state;  // Variable to "remember" the state of the LED, and toggle it.
boolean lineFound;  // Variable to know when the line has been found
boolean lineLost;   // Variable to know when the line has been lost


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
  lineFound = false;
  lineLost = false;

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

  // Run our line sensor update
  // every 100ms (10hz).
  // Tracking time for the line sensor (ls)
  elapsed_t = current_ts - ls_ts;
  if (elapsed_t > LINE_SENSOR_UPDATE) {

    // Conduct a read of the line sensors
    lineSensor.parallelSensorRead();

    ls_ts = millis();
  }
  //switch case to allow my code to have different states that can be entered into if certain parameters are met
  switch (Line) {
    case 0:
      //initialising each of the motor states
      motors.initialiseMotor();
      Line = 1;
      break;
    case 1:

      //are all 3 sensors on white
      if (lineSensor.sensor_read[1] && lineSensor.sensor_read[2] && lineSensor.sensor_read[3] < 1500) {
        if (lineFound == false) {
          driveForwards();
          Line = 2;
        }
      }
      Line = 2;
      break;
    case 2:
      //if all 3 sensors are black stop & turn on the line
      if (lineSensor.sensor_read[1] && lineSensor.sensor_read[2] && lineSensor.sensor_read[3] > 1500) {
        if (lineFound == false) {
          turnOn();
          lineFound = true;
          Line = 3;
        }
      }
      Line = 3;
      break;
    case 3:
      //line following or if line lost switch to the line lost case
      if (lineFound == true) {
        lineFollowing();
        Line = 3;
      }
      if (lineLost == true) {
        Line = 4;
      }
      Line = 4;
      break;
    case 4:
      //Protocol if the line is lost
      while (lineLost == true) {


        lineLostCount += 1;
        Serial.print(lineLostCount);
        Serial.print("\n");


        Serial.print("Line Lost");
        Serial.print("\n");

        if (lineSensor.sensor_read[0] || lineSensor.sensor_read[1] || lineSensor.sensor_read[2] || lineSensor.sensor_read[3] || lineSensor.sensor_read[4] > 1500) {
          lineFound = true;
          Line = 3;
        }
        //if the line is lost for more than the update turn around 180 degrees and look for the line to re-enter the line following case
        if (lineLostCount > LINE_LOST_UPDATE) {
          Serial.print("Stopped");
          Serial.print("\n");
          motors.stopMotors();
          delay(2000);
          turnAround();
          Serial.print(totalTurns);
          Serial.print("\n");
          if (lineSensor.sensor_read[0] || lineSensor.sensor_read[1] || lineSensor.sensor_read[2] || lineSensor.sensor_read[3] || lineSensor.sensor_read[4] > 1500) {
            lineFound = true;
            Line = 3;
          }

          if (current_ts > 60000) {  //will only stop if its been longer than 60secs
            motors.stopMotors();
            delay(10000);
          }
        }
        break;
      }

      Line = 5;
      break;
    case 5:

      Line = 0;
  }
}

//functions used throughout main

void beep(int toggle_duration) {
  digitalWrite(BUZZER_PIN, HIGH);
  delayMicroseconds(toggle_duration);
  digitalWrite(BUZZER_PIN, LOW);
  delayMicroseconds(toggle_duration);
}



void driveForwards() {

  motors.setPower(20, 20);
  motors.leftForward();
  motors.rightForward();
  Serial.print("drive forwards");
  Serial.print("\n");
}

void turnOn() {
  motors.stopMotors();
  delay(1000);
  motors.setPower(20, 0);
  motors.rightForward();
  motors.leftForward();
  Serial.print("turning on");
  Serial.print("\n");
  delay(1500);
}

void turnAround() {
  motors.setPower(20, 20);
  motors.leftReverse();
  motors.rightForward();
  delay(1800);
  motors.stopMotors();
  driveForwards();
  delay(1000);
}

void lineFollowing() {

  lineLost = false;


  Serial.print("line Following");
  Serial.print("\n");


  float e_line;
  e_line = lineSensor.errorCalc();

  float turn_pwm;
  turn_pwm = 20;

  turn_pwm = turn_pwm * e_line;

  float leftPower = 20 - turn_pwm * 2;
  float rightPower = 20 + turn_pwm * 2;
  leftPower = int(leftPower);
  rightPower = int(rightPower);
  motors.setPower(leftPower, rightPower);
  motors.leftForward();
  motors.rightForward();

  if (e_line < 0.1) {
    if (lineSensor.sensor_read[2] > 1500) {
      lineLostCount = 0;
      lineFound = true;
      Serial.print("line found");
      Serial.print("\n");
    }
    if (lineSensor.sensor_read[0] && lineSensor.sensor_read[1] && lineSensor.sensor_read[2] && lineSensor.sensor_read[3] && lineSensor.sensor_read[4] < 1500) {
      lineLost = true;
    }
  }
}