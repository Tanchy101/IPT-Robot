// #include <Arduino.h>

// // Ultrasonic sensor
// #define echo 12
// #define trigger 11

// // Right line tracking
// #define lineRight 8
// // Left line tracking
// #define lineLeft 9

// // Right wheel
// #define input3 3
// #define input4 4
// #define enableB 5
// // Left wheel
// #define input2 2
// #define input1 1
// #define enableA 0

// int distance;
// long duration;

// void setup() {
//   pinMode(trigger, OUTPUT);
//   pinMode(echo, INPUT);

//   pinMode(lineLeft, INPUT);
//   pinMode(lineRight, INPUT);

//   pinMode(enableA, OUTPUT);
//   pinMode(input4, OUTPUT);
//   pinMode(input3, OUTPUT);

//   pinMode(enableB, OUTPUT);
//   pinMode(input2, OUTPUT);
//   pinMode(input1, OUTPUT);

// }

// void loop() {
//   // Trigger the ultrasonic sensor
//   digitalWrite(trigger, LOW);
//   delayMicroseconds(5);
//   digitalWrite(trigger, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigger, LOW);

//   // Read the echo pin
//   duration = pulseIn(echo, HIGH);
//   distance = duration * 0.034 / 2;  // Corrected distance calculation

  

//   if (distance <= 10) {
//     digitalWrite(input4, HIGH);
//     digitalWrite(input3, LOW);
//     analogWrite(enableB, 255);
//     delay(500);        
//   } else if (distance <= 20) {
//     digitalWrite(input4, LOW);
//     digitalWrite(input3, LOW);
//     analogWrite(enableB, 0.2 * 255);
//   } else {
//     digitalWrite(input4, LOW);
//     digitalWrite(input3, LOW);
//     analogWrite(enableB, 0);
//   }
//   delay(100);  // Reduced delay for better responsiveness
// }

#include <Arduino.h>

// Pin definitions
#define trigger 11
#define echo 12
#define lineLeft 9
#define lineRight 8
// Right wheel
#define input3 3
#define input4 4
#define enableB 5
// Left wheel
#define input2 2
#define input1 1
#define enableA 0

int duration;
float distance;
int measureDistance;

const int enemyDistThreshold = 30;
const int lineSensorThreshold = 500;

 // Full speed for motor B

void setup() {
  // Initialize pins
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(lineLeft, INPUT);
  pinMode(lineRight, INPUT);
  pinMode(enableA, OUTPUT);
  pinMode(input4, OUTPUT);
  pinMode(input3, OUTPUT);
  pinMode(enableB, OUTPUT);
  pinMode(input2, OUTPUT);
  pinMode(input1, OUTPUT);

  analogWrite(enableA, 255); // Full speed for motor A
  analogWrite(enableB, 255);
}

void loop() {

  // Spin initially
  digitalWrite(input1, LOW);
  digitalWrite(input2, HIGH);
  analogWrite(enableA, 255);
  digitalWrite(input4, HIGH);
  digitalWrite(input3, LOW);
  analogWrite(enableB, 255);

  // If an object is detected within 10cm, move forward
  if (distance <= 10) {
    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
    analogWrite(enableA, 255);
    digitalWrite(input4, LOW);
    digitalWrite(input3, HIGH);
    analogWrite(enableB, 255);
    delay(500); // Delay to ensure the robot moves forward for a short duration
  }

  // Trigger the ultrasonic sensor
  digitalWrite(trigger, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  int distance = measureDistance();
  int rightLineSensorValue = analogRead(lineRight);
  int leftLineSensorValue = analogRead(lineLeft);
  // Read the echo pin
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;  // Calculate distance

  //for line tracking
  if (leftLineSensorValue > lineSensorThreshold || rightLineSensorValue > lineSensorThreshold) {
    moveBackward();
    delay(500);
  } else {
    stopMoving();
  }
}
  // for measuring distance
  int measureDistance() {
  // Send a 10us pulse to trigger pin
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  // Measure the duration of the echo pin
  long duration = pulseIn(echo, HIGH);
  
  // Calculate the distance in centimeters
  int distance = duration * 0.034 / 2;
  
  return distance;
}
  


void moveBackward() {
  digitalWrite(input1, LOW);
  digitalWrite(input2, HIGH);
  digitalWrite(input3, LOW);
  digitalWrite(input4, HIGH);
}

void stopMoving() {
  digitalWrite(input1, LOW);
  digitalWrite(input2, LOW);
  digitalWrite(input3, LOW);
  digitalWrite(input4, LOW);
}
// void loop() {




//   //line tracking
//   RightSensor = digitalRead(lineRight);
//   LeftSensor = digitalRead(lineLeft);



//   // if (RightSensor == HIGH || LeftSensor == HIGH) {
//   //   // Reverse both motors
//   //   digitalWrite(input1, HIGH);
//   //   digitalWrite(input2, LOW);
//   //   analogWrite(enableA, 255);
    
//   //   digitalWrite(input3, LOW);
//   //   digitalWrite(input4, HIGH);
//   //   analogWrite(enableB, 255);
//   // } else {
//   //   // Stop both motors
//   //   digitalWrite(input1, LOW);
//   //   digitalWrite(input2, LOW);
//   //   analogWrite(enableA, 0);
    
//   //   digitalWrite(input3, LOW);
//   //   digitalWrite(input4, LOW);
//   //   analogWrite(enableB, 0);
//   // }
  
//   // delay(100); 


//   else { 
//     digitalWrite(input1, LOW);
//     digitalWrite(input2, LOW);
//     analogWrite(enableA, 255); 

//     digitalWrite(input4, LOW);
//     digitalWrite(input3, LOW);
//     analogWrite(enableB, 0);      
//   }
//   delay(500);
// }