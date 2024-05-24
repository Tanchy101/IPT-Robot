#include <Arduino.h>

// Pin definitions
#define trigger 11
#define echo 12
// Right wheel
#define input3 3
#define input4 4
#define enableB 6
// Left wheel
#define input2 2
#define input1 1
#define enableA 7

#define leftIR 9
#define rightIR 8

int duration;
float distance;

void activeBreak();

bool brakeOnce = false;

const int distanceThreshold = 50;  // Threshold distance in cm

void setup() {
  Serial.begin(9600);
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
  
  if (!brakeOnce){
      activeBreak();
      delay(5000);
      brakeOnce = true;
    }
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

  Serial.println ("Distance: ");
  Serial.println (distance);

  int lval = digitalRead(leftIR);
  int rval = digitalRead(rightIR);
  if (distance <= distanceThreshold && distance >= 0 && lval == HIGH && rval == HIGH) {
    // Move forward
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    analogWrite(enableA, 255);  // Full speed for LEFT motor

    digitalWrite(input3, HIGH);
    digitalWrite(input4, LOW);
    analogWrite(enableB, 255);  // Full speed for RIGHT motor

  } else if(lval == LOW && rval == LOW){
    digitalWrite(input1, LOW);
    digitalWrite(input2, LOW);
    analogWrite(enableA, 0);  // Full speed for left motor (REVERSE)

    digitalWrite(input3, LOW);
    digitalWrite(input4, HIGH);
    analogWrite(enableB, 0.8*255);    //Eto lang yung kaya eh (REVERSE)
    Serial.println("BOTH TRUE");

    } else if(lval == LOW && rval == LOW && distance <= distanceThreshold && distance >= 0){
    digitalWrite(input1, LOW);
    digitalWrite(input2, LOW);
    analogWrite(enableA, 0);  // Full speed for left motor (REVERSE)

    digitalWrite(input3, LOW);
    digitalWrite(input4, HIGH);
    analogWrite(enableB, 0.8*255);    //Eto lang yung kaya eh (REVERSE)
    Serial.println("BOTH TRUE");


  // }  else if(lval == LOW && rval == HIGH){
  //   digitalWrite(input1, HIGH);
  //   digitalWrite(input2, LOW);
  //   analogWrite(enableA, 255);  // Full speed for left motor

  //   digitalWrite(input3, LOW);
  //   digitalWrite(input4, LOW);
  //   analogWrite(enableB, 0);    // Stop the right motor
  //   Serial.println("RIGHT TRUE");

  // } else if(lval == HIGH && rval == LOW){
  //   digitalWrite(input1, LOW);
  //   digitalWrite(input2, LOW);
  //   analogWrite(enableA, 0);  // Full speed for left motor

  //   digitalWrite(input3, HIGH);
  //   digitalWrite(input4, LOW);
  //   analogWrite(enableB, 0.5*255);    // Stop the right motor
  //   Serial.println("LEFT TRUE");

  } else {
    // Turn by moving only the left wheel
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    analogWrite(enableA, 255);  // Full speed for left motor

    digitalWrite(input3, LOW);
    digitalWrite(input4, LOW);
    analogWrite(enableB, 0);  // Full speed for RIGHT motor
    
     // Full speed for RIGHT motor
  }

  delay(100);  // Short delay to stabilize the readings
}

void activeBreak() {
  digitalWrite(input1, LOW);
  digitalWrite(input2, LOW);
  analogWrite(enableA, 0);
  digitalWrite(input3, LOW);
  digitalWrite(input4, LOW);
  analogWrite(enableB, 0);
}