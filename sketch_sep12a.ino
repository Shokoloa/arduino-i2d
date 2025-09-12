#include <Servo.h>
#define Servo_pin 9
Servo servoBase;

void setup() {
  Serial.begin(9600);
  servoBase.attach(Servo_pin);
}

void loop() {
  Serial.println("Position 90");
  //servoBase.write(90);
  delay(5000);

  Serial.println("Position 0");
  //servoBase.write(0);
  delay(5000);
}
