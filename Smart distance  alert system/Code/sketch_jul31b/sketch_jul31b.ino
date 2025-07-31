#include <Servo.h>

Servo myservo;

// Your hardware pins
int trig = 10;
int echo = 11;
int buzzer = 9;
int r = 4;
int g = 5;
int b = 6;

long duration;
float distance;

void setup() {
  // NEW LINE: Starts the communication with the computer
  Serial.begin(9600);

  myservo.attach(3);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
}

void loop() {
  // Loop for sweeping from 0 to 180 degrees
  for (int deg = 0; deg <= 180; deg++) {
    myservo.write(deg);
    delay(15); // A small delay to keep the sweep smooth

    // Your original sensor reading code
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH);
    distance = duration * 0.034 / 2; // More accurate distance formula

    // NEW LINE: Sends the data in the format "angle,distance."
    Serial.print(String(deg) + "," + String(int(distance)) + ".");

    // Your original LED and buzzer logic
    if (distance > 40 || distance <= 0) {
      digitalWrite(g, HIGH);
      digitalWrite(r, LOW);
      digitalWrite(b, LOW);
      noTone(buzzer);
    } else if (distance > 10) {
      digitalWrite(g, HIGH);
      digitalWrite(r, HIGH);
      digitalWrite(b, LOW);
      tone(buzzer, 100);
    } else {
      digitalWrite(r, HIGH);
      digitalWrite(g, LOW);
      digitalWrite(b, LOW);
      tone(buzzer, 500);
    }
  }

  // Loop for sweeping back from 180 to 0 degrees
  for (int deg = 180; deg >= 0; deg--) {
    myservo.write(deg);
    delay(15);

    // Your original sensor reading code
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH);
    distance = duration * 0.034 / 2;

    // NEW LINE: Sends the data for the return sweep
    Serial.print(String(deg) + "," + String(int(distance)) + ".");

    // Your original LED and buzzer logic
    if (distance > 40 || distance <= 0) {
      digitalWrite(g, HIGH);
      digitalWrite(r, LOW);
      digitalWrite(b, LOW);
      noTone(buzzer);
    } else if (distance > 10) {
      digitalWrite(g, HIGH);
      digitalWrite(r, HIGH);
      digitalWrite(b, LOW);
      tone(buzzer, 100);
    } else {
      digitalWrite(r, HIGH);
      digitalWrite(g, LOW);
      digitalWrite(b, LOW);
      tone(buzzer, 500);
    }
  }
}