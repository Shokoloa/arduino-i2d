#include <SoftwareSerial.h>
#include <Servo.h>

// Définition de variables
#define Servo_pin 9
#define ForceSensor A0

SoftwareSerial hc05(2,3);
Servo servoBase;
String msg;

void setup() {
  Serial.begin(9600);
  hc05.begin(9600);
  servoBase.attach(Servo_pin);
  servoBase.write(88);
}

void moveServoUntilForce(int v = 88) {
  int forceValue = analogRead(ForceSensor);
  int threshold = 102; // 10% de 1023

  while (forceValue < threshold) {
    servoBase.write(v);
    delay(20);
    forceValue = analogRead(ForceSensor);
    Serial.print("Force: ");
    Serial.println(forceValue);
  }

  servoBase.write(88);
  Serial.println("Seuil atteint, servo arrêté.");
}

void loop() {
  readSerialPort();

  if(msg!=""){
    msg.toLowerCase();
    
    Serial.print("Master sent : " );
    Serial.println(msg);
    hc05.print(msg);
  }

  if (msg.indexOf("garmin") != -1) {
    moveServoUntilForce(120);
  }

  if (msg.indexOf("jacky") != -1) {
    moveServoUntilForce(60);
  }
  
  msg="";
}

void readSerialPort() {
 while (hc05.available()) {
   delay(10);
   if (hc05.available() >0) {
     char c = hc05.read();
     msg += c;
   }
 }
 hc05.flush();
}
