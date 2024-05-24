// #include <Arduino.h>

// // Pin definitions
// #define trigger 11
// #define echo 12
// // Right wheel
// #define input3 3
// #define input4 4
// #define enableB 5
// // Left wheel
// #define input2 2
// #define input1 1
// #define enableA 6

// //line tracking sensor
// #define leftIR 9
// #define rightIR 8

// int duration;
// float distance;

// int lVal;
// int rVal;

// void turnBack();
// void stop();
// void moveForward();
// void search();


// const int distanceThreshold = 20;  // Threshold distance in cm

// void setup() {
//   // Initialize pins
//   pinMode(trigger, OUTPUT);
//   pinMode(echo, INPUT);
//   pinMode(enableA, OUTPUT);
//   pinMode(input4, OUTPUT);
//   pinMode(input3, OUTPUT);
//   pinMode(enableB, OUTPUT);
//   pinMode(input2, OUTPUT);
//   pinMode(input1, OUTPUT);
//   pinMode(leftIR, INPUT);
//   pinMode(rightIR, INPUT);
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
//   distance = duration * 0.034 / 2;  // Calculate distance

//   lVal = digitalRead(leftIR);
//   rVal = digitalRead(rightIR); 

//   if (distance <= distanceThreshold) {
//     // Move forward
//     moveForward();
//   } else if (lVal == HIGH && rVal == HIGH){
//     turnBack();
//   } else {
//     // Turn by moving only the left wheel
//     // Stop the right motor
//     search();
//   }

//   delay(100);  // Short delay to stabilize the readings



// }

// // #include <Arduino.h>

// // // Right wheel
// // #define input3 3
// // #define input4 4
// // #define enableB 5
// // // Left wheel
// // #define input2 2
// // #define input1 1
// // #define enableA 6
// // // Line tracking sensors
// // #define leftIR 9
// // #define rightIR 8

// // int lVal;
// // int rVal;

// // void setup() {
// //   // Initialize pins
// //   pinMode(leftIR, INPUT);
// //   pinMode(rightIR, INPUT);
// //   pinMode(enableA, OUTPUT);
// //   pinMode(input4, OUTPUT);
// //   pinMode(input3, OUTPUT);
// //   pinMode(enableB, OUTPUT);
// //   pinMode(input2, OUTPUT);
// //   pinMode(input1, OUTPUT);
// // }

// // void goBack() {
// //   lVal = digitalRead(leftIR);
// //   rVal = digitalRead(rightIR);
//   // Only left sensor detects the line
//   // Turn right
//   void search(){
//     digitalWrite(input1, LOW);
//     digitalWrite(input2, HIGH);
//     analogWrite(enableA, 255);  // Full speed for left motor
//     digitalWrite(input4, LOW);
//     digitalWrite(input3, LOW);
//     analogWrite(enableB, 0);    // Stop the right motor
//   }
//   void turnBack(){
//     digitalWrite(input1, LOW);
//     digitalWrite(input2, HIGH);
//     analogWrite(enableA, 255);  // Full speed for left motor
//     digitalWrite(input4, LOW);
//     digitalWrite(input3, HIGH);
//     analogWrite(enableB, 255);
//   } 
   
   
//   // void turnLeft() { // Only right sensor detects the line
//   //   // Turn left
//   //   digitalWrite(input1, HIGH);
//   //   digitalWrite(input2, LOW);
//   //   analogWrite(enableA, 255);
//   //   digitalWrite(input4, LOW);
//   //   digitalWrite(input3, HIGH);
//   //   analogWrite(enableB, 0);
//   // }
//   void moveForward() { // Both sensors detect the line
//     // Move forward
//     digitalWrite(input4, HIGH);
//     digitalWrite(input3, LOW);
//     analogWrite(enableB, 255);
//     digitalWrite(input1, HIGH);
//     digitalWrite(input2, LOW);
//     analogWrite(enableA, 255);
//   } 
//   void stop() { // Neither sensor detects the line
//     // Stop
//     digitalWrite(input1, LOW);
//     digitalWrite(input2, LOW);
//     analogWrite(enableA, 0);
//     digitalWrite(input4, LOW);
//     digitalWrite(input3, LOW);
//     analogWrite(enableB, 0);    
//   }



#include <Arduino.h>

// Pin definitions
#define trigger 11
#define echo 12
// Right wheel
#define input3 3
#define input4 4
#define enableB 5
// Left wheel
#define input2 2
#define input1 1
#define enableA 6

// Line tracking sensors
#define leftIR 9
#define rightIR 8

int duration;
float distance;

int lVal;
int rVal;

void moveBackward();
void moveLeftWheelBackward();
void moveRightWheelBackward();
void moveForward();
void search();

const int distanceThreshold = 5;  // Threshold distance in cm

void setup() {
  // Initialize pins
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(enableA, OUTPUT);
  pinMode(input4, OUTPUT);
  pinMode(input3, OUTPUT);
  pinMode(enableB, OUTPUT);
  pinMode(input2, OUTPUT);
  pinMode(input1, OUTPUT);
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(trigger, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  // Read the echo pin
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;  // Calculate distance

  lVal = digitalRead(leftIR);
  rVal = digitalRead(rightIR); 

  if (distance < distanceThreshold) {
      digitalWrite(input4, HIGH);
      digitalWrite(input3, LOW);
      analogWrite(enableB, 255);  // Full speed for LEFT motor FORWARD

      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      analogWrite(enableA, 255); // Full speed for RIGHT motor FORWARD

  } else if (lVal == HIGH && rVal == HIGH) {
      digitalWrite(input4, LOW);
      digitalWrite(input3, HIGH);
      analogWrite(enableB, 255);  // Full speed for LEFT motor BACKWARD

      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      analogWrite(enableA, 255); // Full speed for RIGHT motor BACKWARD

  } else if (lVal == HIGH && rVal == LOW) {
      digitalWrite(input4, LOW);
      digitalWrite(input3, HIGH);
      analogWrite(enableB, 255);  // Full speed for LEFT motor BACKWARD

      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      analogWrite(enableA, 0); // STOP for RIGHT motor 

  } else if (lVal == LOW && rVal == HIGH) {
      digitalWrite(input4, LOW);
      digitalWrite(input3, LOW);
      analogWrite(enableB, 0);  // STOP for LEFT motor 

      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      analogWrite(enableA, 255); // Full speed for RIGHT motor BACKWARD

  } else {
      digitalWrite(input4, LOW);
      digitalWrite(input3, LOW);
      analogWrite(enableB, 0);  // STOP for LEFT motor 

      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      analogWrite(enableA, 255); // Full speed for RIGHT motor FORWARD
  }
  delay(100);  // Short delay to stabilize the readings
}

