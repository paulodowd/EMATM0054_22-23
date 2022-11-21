// this #ifndef stops this file
// from being included mored than
// once by the compiler. 

#ifndef _MOTORS_H
#define _MOTORS_H

#define LEFT_MOTOR 10 //Left Motor
#define RIGHT_MOTOR 9 //Right Motor
#define RIGHT_DIRECTION 15 ///Right Direction
#define LEFT_DIRECTION 16 ///Left Direction

#define FWD LOW
#define REV HIGH


// Class to operate the motor(s).
class Motors_c {
  public:

    unsigned int powerLeft;
    unsigned int powerRight; 

    // Constructor, must exist.
    Motors_c() {

    } 

    // Use this function to 
    // initialise the pins and 
    // state of your motor(s).
    void initialiseMotor() {
      pinMode( LEFT_MOTOR, OUTPUT);
      pinMode( RIGHT_MOTOR, OUTPUT);
      pinMode( LEFT_DIRECTION, OUTPUT);
      pinMode( RIGHT_DIRECTION, OUTPUT);  
    }

    // Write a function to operate
    // your motor(s)
    // ...

    void setPower(int powerLeftValue, int powerRightValue){
    powerLeft = powerLeftValue;
    powerRight = powerRightValue;
    }
    void leftForward(){
      analogWrite(LEFT_MOTOR, powerLeft);
      }
    void rightForward(){
      analogWrite(RIGHT_MOTOR, powerRight);
    }
    void leftReverse(){
      analogWrite(LEFT_MOTOR,powerLeft);
      digitalWrite(LEFT_DIRECTION, REV);
      }
    void rightReverse(){
      analogWrite(RIGHT_MOTOR,powerRight);
      digitalWrite(RIGHT_DIRECTION, REV);
      }
    void stopMotors(){
      digitalWrite(RIGHT_MOTOR, LOW);
      digitalWrite(LEFT_MOTOR, LOW);
      digitalWrite(RIGHT_DIRECTION, FWD);
      digitalWrite(LEFT_DIRECTION, FWD);
      }

    
};



#endif
