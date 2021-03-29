#include <SoftwareSerial.h>

int buzz = 2
int echo = 3
int trig = 4
int led = 5
SoftwareSerial sim800l(10,11);

void setup()
{
  pinMode(buzz, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led, OUTPUT);
  sim800l.begin(9600);
  Serial.begin(9600);
  
}

void loop()  
{
  digitalWrite(trig, HIGH); 
  delay(1);
  digitalWrite(trig, LOW);
  float duration = pulseIn(echo, HIGH);
  float distance = (duration/2)/29.1;
  if (distance >= rackdis) 
  {
    SendSMS();
    digitalWrite(buzz, HIGH);//Buzz noise for indication
    digitalWrite(led, HIGH);//LED is bright for indication
  } 
  else 
  {
    digitalWrite(buzz, LOW);//Don't Buzz
    digitalWrite(led, LOW); // Don't Glow
  }
}

void SendSMS()
{
  sim800l.print("AT+CMGF=1\r");                   //Set the module to SMS mode
  delay(100);
  sim800l.print("AT+CMGS=\"+91**********\"\r");  //Phone number of particular store number
  delay(500);
  sim800l.print("ALERT!!! Rack no. ** is Emptying, Please refill the rack!!!");  //Notification to store that the rack is empty
  delay(500);
  sim800l.print((char)26);
  delay(500);
  sim800l.println();
  delay(500);
}
