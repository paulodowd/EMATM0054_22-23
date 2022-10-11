#define LS_LEFT_PIN A0
#define LS_CENTRE_PIN A2
#define LS_RIGHT_PIN A4
#define EMIT 11

 // Define the max number of sensors to use.
# define NB_LS_PINS 3

// We can create an array ("list") of sensors to check.  This becomes very useful to allow us to write code which iterates, rather than
//needing to repeat lines of similar code. Note, we should match the number of entries to the max number of sensors we are reading. 
int ls_pin[NB_LS_PINS] = { LS_LEFT_PIN, LS_CENTRE_PIN, LS_RIGHT_PIN };

int which;
int timeout;

void setup() {

//Initialise Pins
 pinMode(EMIT, OUTPUT);
 pinMode(LS_LEFT_PIN, INPUT);
 pinMode(LS_CENTRE_PIN, INPUT);
 pinMode(LS_RIGHT_PIN, INPUT);

 //Set Emit Pin High
 digitalWrite(EMIT, HIGH);

//Start Serial Output
 Serial.begin(9600);
 delay(1000);
 Serial.println("RESET");

}

//Function to read a line sensor
// - which sensor to read
// - return the result
// unsigned long readLineSensor( int which_pin ){

// // Charge capacitor by setting input pin
// // temporarily to output and HIGH
// pinMode( which_pin, OUTPUT );
// digitalWrite(which_pin, HIGH );

// // Tiny delay for capacitor to charge.
// delayMicroseconds(10);

// //  Turn input pin back to an input
// pinMode(which_pin, INPUT );

// // Places to store microsecond count
// unsigned long start_time; // t_1
// unsigned long end_time;   // t_2

// // Store current microsecond count
// start_time = micros();

// // Stay in a loop whilst the capacitor
// // is still registering as "HIGH".
// while( digitalRead( which_pin ) == HIGH ) {
// // Do nothing, waiting for LS_LEFT_PINT to
// // go to LOW state.
// }

// // LS_LEFT_PIN must have gone LOW,
// // store microsecond count afterwards
// end_time = micros();

//   // Calculate elapsed time
// unsigned long elapsed_time; // t_elapsed
// elapsed_time = end_time - start_time;

// return elapsed_time;

// }

void loop() {


parallelSensorRead();

// elapsed_time = readLineSensor(LS_LEFT_PIN); //read the output for the left pin .
// Serial.print( elapsed_time ); // Print output
// Serial.print(",");

// elapsed_time = readLineSensor(LS_CENTRE_PIN); //read the output for the centre pin .
// Serial.print( elapsed_time ); // Print output
// Serial.print(",");


// elapsed_time = readLineSensor(LS_RIGHT_PIN); //read the output for the right pin .
// Serial.print( elapsed_time ); // Print output
// Serial.print(",");

// end_time = micros();
// elapsed_time = end_time - start_time;
// Serial.print(elapsed_time);
// Serial.print("\n");


// Delay, just so that we have time toread the 
// values when using Serial.print().
delay(100);


}

void chargeCapacitors() {
for (which = 0; which < NB_LS_PINS; which++){
// Charge capacitor by setting input pin
// temporarily to output and HIGH
pinMode( ls_pin[which], OUTPUT );
digitalWrite(ls_pin[which], HIGH );
  } //end  for loop 

// Tiny delay for capacitor to charge.
delayMicroseconds(10);

for (which = 0; which < NB_LS_PINS; which++){
//  Turn input pin back to an input
pinMode(ls_pin[which], INPUT );

}//end for loop 


}//end charge capcitor function

void parallelSensorRead()  {


chargeCapacitors();


// We still need to record the start time.
unsigned long elapsed_time;
unsigned long current_time;
unsigned long start_time;
unsigned long end_time;
start_time = micros();

// Multiple sensors, needs multiple places
// to store the measurement result. 
// We follow the convention above to create
// another array to store 3 values. 
unsigned long sensor_read[ NB_LS_PINS ];

//Set end time to 0, which is a flag for when the sensor has not finished 
for (which = 0; which < NB_LS_PINS; which++){
  sensor_read[which] = 0;
}

// This time, let's use a count to check how
// many sensors have finished reading.  Let's
// set it to NB_LS_PINS (3), and count down to
// zero.  Therefore, remaining == 0 will mean all
// sensors complete. 
int remaining = NB_LS_PINS;


// While we still have sensors to read.
while( remaining > 0 ) {

  // Whilst we are not done, we repeatedly attempt
  // to read the sensors.  We read the sensors in
  // a loop.  "which" will be 0,1,2 before moving on
  // with the code in this while loop.
  for( which = 0; which < NB_LS_PINS; which++ ) {
    // Add code to calculate the current elapsed time
    // here. 
    current_time = micros();
    elapsed_time = current_time - start_time;
    // We can instruct a digitalRead() using our
    // array variable to drop in the correct pin
    // number.  Here, "which" is incrementing
    // 0, 1, 2, looking up the pin value inside
    // ls_pin[]. 
    // Here, if digitalRead() returns LOW, it means
    // this sensor has completed.  
    if( digitalRead( ls_pin[which] ) == LOW ) {
      //Sensor has finished decrease count
      //When the remaining count is 0, all sensors are done
      //remaining = remaining - 1;

        // Check if this sensor has had a previous
        // value of elapsed time stored before.
        // We only want to store the EARLIEST 
        // elapsed time, not store subsequent values.
        if( sensor_read[ which ] ==  0) {

          // record the elapsed time on this iteration
          // of the while() loop as the completion time
          // for this sensor
          sensor_read[which] = elapsed_time;

          // Inside this if() means it is the first
          // and only time this sensor ("which") will
          // be updated.  Therefore, we reduce the 
          // "remaining" count toward 0.
          // Therefore, each decrement corresponds to
          // a unique sensor.
          remaining = remaining - 1;

        } 

    } // end of if( digitalRead() )

  } // end of for() looping through each sensor.

  // Here, we make a final check to see if the 
  // whole read operation is taking too long.
  if( elapsed_time >= timeout ) {

      // Here, you may need to set an appropriate
      // sensor_read[ which ] value to indicate a
      // timeout.  An appropriate initial value of
      // sensor_read[] could mean this step isn't 
      // necessary.
      timeout = 3500; 
    

      // Set remaining to 0 to force end of while()
      remaining = 0;
  }
  



} // end of while( remaining > 0 )

//Here we will print our sensor readings from left to right
Serial.print("Sensor readings L -> R: ");
for (which = 0; which < NB_LS_PINS; which++){
Serial.print(sensor_read[which]);
Serial.print(", ");
}//end the for loop
end_time = micros();
elapsed_time = end_time - start_time;
Serial.print("Overall time: ");
Serial.print(elapsed_time);
Serial.print("\n");
}//end the function
