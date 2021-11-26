#include "DHT.h"
#include <Adafruit_Sensor.h>

#include <Wire.h>
#include <SPI.h>  
#include <RTClib.h>             //library เวลา
RTC_DS3231 RTC;

#define DHT_A_PIN 3             //humidity จากขาdigital
#define DHT_A_TYPE DHT11   
DHT dht1(DHT_A_PIN, DHT11);
#define DHT_B_PIN 2 
#define DHT_B_TYPE DHT11 
DHT dht(DHT_B_PIN, DHT11);

const int moisture_A_Pin = A0; // moisture จากขาanalog
int MoistureA;               
const int moisture_B_Pin = A1; 
int MoistureB; 

int sensor = A3;
void setup() 
{
  dht.begin();
  dht1.begin();
  Wire.begin();
  RTC.begin(); 
   
  pinMode (13,OUTPUT);            //กำหนดขาdigital
  pinMode (12,OUTPUT);
  pinMode (11,OUTPUT);
  pinMode (10,OUTPUT);
  pinMode (9,OUTPUT);
  Serial.begin(9600);           // config port
  Serial.println(F("DHT11 was Begun "));
 
   
  RTC.adjust(DateTime(2020,4,29, 10,59,50));   //ตั้งเวลาปัจจุบันให้ปั้มทำงาน

  DateTime now = RTC.now();

  
}  //วงเล็บvoid setup

void loop() 
{                                                             //วงเล็บ void loop

 DateTime now = RTC.now();
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.println(now.second());
  
int ldr_sensor = map(analogRead(A3),0,1023,100,0);
  Serial.print(" แสง : ");
  Serial.print(ldr_sensor);
  Serial.println("%");
  
    MoistureA = map(analogRead(moisture_A_Pin),0,1023,0,100);         //ความชื้นในดิน A
    Serial.print("MoistureA : "); 
    Serial.print(MoistureA); 
    Serial.println("%");  
    MoistureB = map(analogRead(moisture_B_Pin),0,1023,0,100);         //ความชื้นในดิน B
    Serial.print("MoistureB : "); 
    Serial.print(MoistureB);                  
    Serial.println("%"); 
    int averageMOISTURE = (MoistureA + MoistureB)/2 ;                 //ความชื้นเฉลี่ยจากกระถาง
    Serial.print("AVERAGE MOISTURE IN SOIL : ");
    Serial.print(averageMOISTURE);  
     Serial.println("%");              
   
    
    
    float h1 = dht1.readHumidity();                                     //ความชื้นในบรรยากาศ ตัวที่ 1
    float t1 = dht1.readTemperature();
    float f1 = dht1.readTemperature(true);
    if (isnan(h1) || isnan(t1) || isnan(f1)) 
      {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
      }
    Serial.print(F("Humidity1: "));
    Serial.print(h1);
    Serial.print(F("%  Temperature: "));
    Serial.print(t1);
    Serial.println(F("°C "));
    
    float h = dht.readHumidity();                                       //ความชื้นบรรยากาศ ตัวที่ 2
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);
    if (isnan(h) || isnan(t) || isnan(f)) 
      {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
      }
    Serial.print(F("Humidity2: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.println(F("°C "));
    float averageHUMIDITY = (h + h1)/2;                                 //ความชื้นบรรยากาศเฉลี่ย
    Serial.print("AVERAGE HUMIDITY IN AIR : ");
    Serial.print(averageHUMIDITY);
     Serial.println("%");
              



 if (now.hour()== 6)
        {
          if(now.minute()<30)
            {
              if(now.second()==0)
                {
                  Serial.println("JOM is Watering.");
                  delay(1000);
                  digitalWrite(13,HIGH);
                  digitalWrite(12,HIGH);
                  digitalWrite(11,HIGH);
                  digitalWrite(10,HIGH);
                  digitalWrite(9,HIGH);
                }
            }
          if(now.minute()==30)
            {
              if(now.second()==00)
                  {
                 Serial.println("Pump was stopped.");
                 delay(1000);
                 digitalWrite(13,LOW);
                 digitalWrite(12,LOW);
                 digitalWrite(11,LOW);
                 digitalWrite(10,LOW);
                 digitalWrite(9,LOW);
                  }
           
            }
        }
        


  else if(now.hour()>9 && now.hour() <15){
       if(averageMOISTURE<70)
        {
            digitalWrite(13,HIGH); 
            Serial.println("Water Pump A is ON");
        } 
      if(averageMOISTURE>=70)
        {
          Serial.println("Water Pump A is OFF");
          digitalWrite(13,LOW); 
        }
       if(averageMOISTURE<70)
        {
            digitalWrite(12,HIGH); 
            Serial.println("Water Pump B is ON");
        } 
      if(averageMOISTURE>=70)
        {
          Serial.println("Water Pump B is OFF");
          digitalWrite(12,LOW); 
        }
       if(averageMOISTURE<70)
        {
            digitalWrite(11,HIGH); 
            Serial.println("Water Pump C is ON");
        } 
      if(averageMOISTURE>=70)
        {
          Serial.println("Water Pump C is OFF");
          digitalWrite(11,LOW); 
        }
        if(averageMOISTURE<70)
        {
            digitalWrite(10,HIGH); 
            Serial.println("Water Pump D is ON");
        } 
      if(averageMOISTURE>=70)
        {
          Serial.println("Water Pump D is OFF");
          digitalWrite(10,LOW); 
        }
        if(averageMOISTURE<70)
        {
            digitalWrite(9,HIGH); 
            Serial.println("Water Pump E is ON");
        } 
      if(averageMOISTURE>=70)
        {
          Serial.println("Water Pump E is OFF");
          digitalWrite(9,LOW); 
        }

  } 


else if (now.hour()== 16)
        {
          if(now.minute()<30)
            {
              if(now.second()==0)
              {
                Serial.println("Watering");
                delay(1000);
                digitalWrite(13,HIGH);
                digitalWrite(12,HIGH);
                digitalWrite(11,HIGH);
                digitalWrite(10,HIGH);
                digitalWrite(9,HIGH);
              }
            }
          if(now.minute()==30)
            {
            if(now.second()==00)
                {
               Serial.println("Stopping");
               delay(1000);
               digitalWrite(13,LOW);
               digitalWrite(12,LOW);
               digitalWrite(11,LOW);
               digitalWrite(10,LOW);
               digitalWrite(9,LOW);
                }
           
            }
        }
   
 
else{
      digitalWrite(13,LOW);
      digitalWrite(12,LOW);
      digitalWrite(11,LOW);
      digitalWrite(10,LOW);
      digitalWrite(9,LOW);
      Serial.println("Water Pump A is OFF");
      Serial.println("Water Pump B is OFF");
      Serial.println("Water Pump C is OFF");
      Serial.println("Water Pump D is OFF");
      Serial.println("Water Pump E is OFF");
  }    
    
  delay(1000);
}
