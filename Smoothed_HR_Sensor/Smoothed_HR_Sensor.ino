/*
  Smoothing

  Reads repeatedly from an analog input, calculating a running average and
  printing it to the computer. Keeps ten readings in an array and continually
  averages them.

  The circuit:
  - analog sensor (potentiometer will do) attached to analog input 0

  created 22 Apr 2007
  by David A. Mellis  <dam@mellis.org>
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Smoothing
*/

// Define the number of samples to keep track of. The higher the number, the
// more the readings will be smoothed, but the slower the output will respond to
// the input. Using a constant rather than a normal variable lets us use this
// value to determine the size of the readings array.

#include <Adafruit_CircuitPlayground.h>


const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

const int numReadingsPD = 30;
int readingsPD[numReadingsPD];      // the readings from the analog input for peak detection
int readIndexPD = 0;              // the index of the current reading
int totalPD = 0;                  // the running total
int averagePD= 0;                // the average
const int targetDiffPD = 60;             //the amount you want to peak detect
int diffPD = 0;                   //the actual difference measured

int inputPin = 10;

void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);
  smooth();
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  
  // send it to the computer as ASCII digits
  //Serial.println(smooth());
  Serial.println(peakDetect());
  delay(3);        // delay in between reads for stability
}


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

  if(diffPD>=targetDiffPD && readingsPD[readIndexPD]>100){
    return 1;
  }else{
    return 0;
  }
  
}
