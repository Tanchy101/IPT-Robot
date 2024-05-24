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

int duration;
float distance;

const int distanceThreshold = 30;  // Threshold distance in cm

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

  if (distance <= distanceThreshold) {
    // Move forward
    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
    analogWrite(enableA, 255);  // Full speed for left motor
    digitalWrite(input4, LOW);
    digitalWrite(input3, HIGH);
    analogWrite(enableB, 255);  // Full speed for right motor
  } else {
    // Turn by moving only the left wheel
    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
    analogWrite(enableA, 255);  // Full speed for left motor
    digitalWrite(input4, LOW);
    digitalWrite(input3, LOW);
    analogWrite(enableB, 0);    // Stop the right motor
  }

  delay(100);  // Short delay to stabilize the readings
}