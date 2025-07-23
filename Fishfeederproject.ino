#define REPORT_INTERVAL 10000UL  // 24 hours in milliseconds
unsigned long lastReportTime = 0;
#define BUZZER_PIN 3
#include <NewPing.h>
#include <Servo.h>
int timehour=10;
unsigned long lastMillis;
Servo myservo;
int pos=0;
NewPing mySensor(11,12,400);
void setup()
{
  pinMode(BUZZER_PIN,OUTPUT);
  myservo.attach(9);
  lastMillis=millis();
  Serial.begin(9600);
  
  }
  void loop() 
  {
    unsigned long currentTime = millis();
    if (currentTime - lastReportTime >= REPORT_INTERVAL) {
    int turbidity = analogRead(A0);
    Serial.print("Daily Water Quality Reading: ");
    Serial.println(turbidity);
    
    lastReportTime = currentTime;
    }
    if(millis()-lastMillis>=(1000UL*timehour))
    {
      for(pos=0;pos<=180;pos++)
      {
      myservo.write(pos);
      delay(10);
     }
    for(pos=180;pos>=0;pos--)
    {
      myservo.write(pos);
      delay(10);
    }
    lastMillis=millis();
    }
    int distance = mySensor.ping_cm();
  if (distance >10 && distance < 50)
  {
    analogWrite(BUZZER_PIN, 50);
  }
  else
  {
    analogWrite(BUZZER_PIN, 0);
  }
  delay(1000);
 } 
