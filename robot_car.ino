#include <AFMotor.h>
#include <Servo.h>


#define taillights A6
#define headlights A7
#define leftindercator 40
#define rightindercator 41
#define highbeams 50
#define servo 51
Servo servo1;
int pos = 0;
int val;
int xPosition = 0;
int yPosition = 0;
int x2Position = 0;
int y2Position = 0;
int buttonState = 0;
int headlight = 0;
int rightindercators = 0;
int leftindercators = 0;

AF_DCMotor FrontLeft(1);
AF_DCMotor RearLeft(2);
AF_DCMotor RearRight(3);
AF_DCMotor FrontRight(4);

int motorspeed1 = 0;
int motorspeed2 = 0;
int motorspeed3 = 0;
int motorspeed4 = 0;

const int trigPin = 22;
const int echoPin = 23;

int y = analogRead(A15);
int y2 = analogRead(A13);
int x = analogRead(A14);
int x2 = analogRead(A12);

float duration, distance;
unsigned long Time = 0;
const long flasher = 100;
const long Blinker = 500;

void setup() {

  Serial.begin(115200);  // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  servo1.attach(9);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(headlights, OUTPUT);
  pinMode(taillights, OUTPUT);
  pinMode(leftindercator, OUTPUT);
  pinMode(rightindercator, OUTPUT);
  pinMode(highbeams, INPUT_PULLUP);
}

void Distance() {

  int y = analogRead(A15);
  int x = analogRead(A14);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * .0343) / 2;
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 10) {
    Serial.println("fucked");

    hazard();
//    for (pos = 0; pos <= 180; pos += 10) {  // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      servo1.write(180);  // tell servo to go to position in variable 'pos'
      delay(500);
      servo1.write(90); 
  //  }
  } else if (y > 525) {
    int motorspeed1 = map(y, 525, 1023, 0, 255);
    int motorspeed2 = map(y, 525, 1023, 0, 255);
    int motorspeed3 = map(y, 525, 1023, 0, 255);
    int motorspeed4 = map(y, 525, 1023, 0, 255);
    FrontLeft.setSpeed(motorspeed1);
    FrontLeft.run(BACKWARD);
    RearLeft.setSpeed(motorspeed2);
    RearLeft.run(BACKWARD);
    RearRight.setSpeed(motorspeed3);
    RearRight.run(BACKWARD);
    FrontRight.setSpeed(motorspeed4);
    FrontRight.run(BACKWARD);
    digitalWrite(taillights, 1);


  } else if ((distance > 50) && (headlights != 0)) {
    analogWrite(headlights, 150);
    Serial.println("Headlights on");
  }
}
void Headlights() {

  int y = analogRead(A15);
  int x = analogRead(A14);
  buttonState = digitalRead(highbeams);

  if (y < 500) {
    int headlight = map(y, 500, 0, 0, 150);
    analogWrite(headlights, headlight);
  } else if (buttonState == LOW) {
    digitalWrite(headlights, HIGH);
    Serial.println("HIGHBEAMS on");
  } else {
    digitalWrite(headlights, LOW);
    Serial.println("headlights off");
  }
}
void hazard() {
    unsigned long Realtime = millis();


  digitalWrite(headlights, 1);
  Serial.println("hazards");
  digitalWrite(leftindercator, 1);
  digitalWrite(rightindercator, 0);
  if (Realtime - Time >= flasher) {
    Time = Realtime;
    digitalWrite(leftindercator, 0);
    digitalWrite(rightindercator, 1);
  } else {
    if (Realtime - Time >= flasher) {
      Time = Realtime;

      digitalWrite(leftindercator, 1);
      digitalWrite(rightindercator, 0);

    }
  }
  }

  void motors() {
    unsigned long Realtime = millis();

    int y = analogRead(A15);
    int x = analogRead(A14);
    int y2 = analogRead(A12);
    int x2 = analogRead(A13);

    Serial.print("x");
    Serial.println(x);
    Serial.print("y");
    Serial.println(y);
    Serial.print("x2");
    Serial.println(x2);
    Serial.print("y2");
    Serial.println(y2);

    val = analogRead(A12);            // reads the value of the potentiometer (value between 0 and 1023)
    val = map(val, 0, 1023, 0, 180);  // scale it for use with the servo (value between 0 and 180)
    servo1.write(val);                // sets the servo position according to the scaled value

    if (y < 500) {
      int motorspeed1 = map(y, 500, 0, 0, 255);
      int motorspeed2 = map(y, 500, 0, 0, 255);
      int motorspeed3 = map(y, 500, 0, 0, 255);
      int motorspeed4 = map(y, 500, 0, 0, 255);
      FrontLeft.setSpeed(motorspeed1);
      FrontLeft.run(FORWARD);
      RearLeft.setSpeed(motorspeed2);
      RearLeft.run(FORWARD);
      RearRight.setSpeed(motorspeed3);
      RearRight.run(FORWARD);
      FrontRight.setSpeed(motorspeed4);
      FrontRight.run(FORWARD);
    } else if (y > 520) {
      int motorspeed1 = map(y, 520, 1023, 0, 255);
      int motorspeed2 = map(y, 520, 1023, 0, 255);
      int motorspeed3 = map(y, 520, 1023, 0, 255);
      int motorspeed4 = map(y, 520, 1023, 0, 255);
      FrontLeft.setSpeed(motorspeed1);
      FrontLeft.run(BACKWARD);
      RearLeft.setSpeed(motorspeed2);
      RearLeft.run(BACKWARD);
      RearRight.setSpeed(motorspeed3);
      RearRight.run(BACKWARD);
      FrontRight.setSpeed(motorspeed4);
      FrontRight.run(BACKWARD);
      digitalWrite(taillights, 1);
    } else {
    }
    if (x < 500) {
      int motorspeed1 = map(x, 500, 0, 0, 255);
      int motorspeed2 = map(x, 500, 0, 0, 255);
      int motorspeed3 = map(x, 500, 0, 0, 255);  //right
      int motorspeed4 = map(x, 500, 0, 0, 255);
      FrontLeft.setSpeed(motorspeed1);
      FrontLeft.run(FORWARD);
      RearLeft.setSpeed(motorspeed2);
      RearLeft.run(FORWARD);
      RearRight.setSpeed(motorspeed3);
      RearRight.run(BACKWARD);
      FrontRight.setSpeed(motorspeed4);
      FrontRight.run(BACKWARD);

      if (Realtime - Time >= Blinker) {
        // save the last time you blinked the LED
        Time = Realtime;

        if (rightindercators == LOW) {
          rightindercators = HIGH;
        } else {
          rightindercators = LOW;
        }

        // set the LED with the ledState of the variable:
        digitalWrite(rightindercator, rightindercators);
      }


    } else if (x > 520) {

      int motorspeed1 = map(x, 520, 1023, 0, 255);
      int motorspeed2 = map(x, 520, 1023, 0, 255);
      int motorspeed3 = map(x, 530, 1023, 0, 255);  //left
      int motorspeed4 = map(x, 530, 1023, 0, 255);
      FrontLeft.setSpeed(motorspeed1);
      FrontLeft.run(BACKWARD);
      RearLeft.setSpeed(motorspeed2);
      RearLeft.run(BACKWARD);
      RearRight.setSpeed(motorspeed3);
      RearRight.run(FORWARD);
      FrontRight.setSpeed(motorspeed4);
      FrontRight.run(FORWARD);
      if (Realtime - Time >= Blinker) {
        // save the last time you blinked the LED
        Time = Realtime;

        if (leftindercators == LOW) {
          leftindercators = HIGH;
        } else {
          leftindercators = LOW;
        }

        // set the LED with the ledState of the variable:
        digitalWrite(leftindercator, leftindercators);
      }
    }
  }
  void loop() {

    Distance();
    Headlights();
    motors();
  }
