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

int duration;
float distance;

const int distanceThreshold = 45;  // Threshold distance in cm

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

  if (distance <= distanceThreshold && distance >= 0) {
    // Move forward
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    analogWrite(enableA, 255);  // Full speed for left motor
    digitalWrite(input4, LOW);
    digitalWrite(input3, HIGH);
    analogWrite(enableB, 255);  // Full speed for right motor

  } else {
    // Turn by moving only the left wheel
    digitalWrite(input1, LOW);
    digitalWrite(input2, LOW);
    analogWrite(enableA, 0);  // Full speed for left motor
    digitalWrite(input4, LOW);
    digitalWrite(input3, HIGH);
    analogWrite(enableB, 255);    // Stop the right motor
  }

  delay(100);  // Short delay to stabilize the readings
}