#include <SoftwareSerial.h>

int ledPin = 13;
int buzzerPin = 12;
int ldrPin = A0;
int laserPin = 7;
SoftwareSerial sim800l(10,11);

void setup () 
{
  Serial.begin(9600);
  sim800l.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  pinMode( laserPin , OUTPUT);
  digitalWrite( laserPin , HIGH);
}

void loop() 
{
  int ldrStatus = analogRead(ldrPin);
  if (ldrStatus >= 700) 
  {
    SendSMS();
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
  }
  
}

void SendSMS()
{
  sim800l.print("AT+CMGF=1\r");                   //Set the module to SMS mode
  delay(100);
  sim800l.print("AT+CMGS=\"+91**********\"\r");  //Phone number of particular store number
  delay(500);
  sim800l.print("ALERT!!! Rack no. ** is Emptying, Please refill the rack!!!");  //Notification to the store that the rack is empty
  delay(500);
  sim800l.print((char)26);
  delay(500);
  sim800l.println();
  delay(500);
}
