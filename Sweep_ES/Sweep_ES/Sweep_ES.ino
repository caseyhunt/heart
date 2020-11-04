/* Sweep Modified
   Based on Arduino Sweep Example
   Use this code to get your heart to beat with the servo motor
   This code is not connected to the heartrate monitor
   Change position maximum to give your heart a more or less pronounced beat
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position


int rate = 3;   //change this to make the heart beat faster or slower

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  for (pos = 0; pos <= 40; pos += 1) { // goes from 0 degrees to 40 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(rate);                       // change this to make the heart beat faster or slower
  }
  for (pos = 40; pos >= 0; pos -= 1) { // goes from 40 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(rate);                       // change this to make the heart beat faster or slower
  }
}
