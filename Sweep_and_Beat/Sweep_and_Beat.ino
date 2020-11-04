/* Sweep and Beat
   This combines both the heartbeat sensor and sweeping servo to create a connected system
   If you're having trouble getting this to work, try Sweep_ES and Smoothed_HR_Sensor individually first
   Then, combine all the parts into the finished piece here!
*/




#include <Servo.h>


//initialize servo for heart
Servo myservo;  // create servo object to control a servo



//initialize variables for smoothing function and heartbeat detection
const int numReadings = 5;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

const int numReadingsPD = 40;     //how many readings to average
int readingsPD[numReadingsPD];      // the readings from the analog input for peak detection
int readIndexPD = 0;              // the index of the current reading
int totalPD = 0;                  // the running total
int averagePD= 0;                // the average
const int targetDiffPD = 40;             //the amount you want to peak detect,adjust this for your own system
int diffPD = 0;                   //the actual difference measured

int inputPin = 2;       //the pin with the hr monitor

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

    // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

    // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadingsPD; thisReading++) {
    readingsPD[thisReading] = 0;
  }
}

void loop() {

    myservo.write(0);              // tell servo to go to position in variable 'pos'
    //Serial.println(smooth());
    Serial.println(peakDetect());
    delay(3);                       // waits 15ms for the servo to reach the position
}















//void loop() {
//  
//  // send it to the computer as ASCII digits
//  //Serial.println(smooth());
//  Serial.println(peakDetect());
//  delay(3);        // delay in between reads for stability
//}


int smooth(){
    // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(inputPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  return average;
}

int peakDetect(){
    // subtract the last reading:
  totalPD = totalPD - readingsPD[readIndexPD];
  // read from the sensor:
  readingsPD[readIndexPD] = analogRead(inputPin);
  // add the reading to the total:
  totalPD = totalPD + readingsPD[readIndexPD];
  // advance to the next position in the array:
  readIndexPD = readIndexPD + 1;

  // if we're at the end of the array...
  if (readIndexPD >= numReadingsPD) {
    // ...wrap around to the beginning:
       readIndexPD = 0;
  }

  // calculate the average:
  averagePD = totalPD / numReadingsPD;

  //calculate the difference
  diffPD = abs(averagePD - readingsPD[readIndexPD]);
  
  //if difference is higher than target difference
  if(diffPD>=targetDiffPD){
    //return servo position
    return 40;
    //then wait, just so you don't overwhelm the system
    delay(1);
  }else{
    return 0;
  }
  
}
