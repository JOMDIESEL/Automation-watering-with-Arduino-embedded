#include "DHT.h"
#include <Adafruit_Sensor.h>

#include <Wire.h>
#include <SPI.h>  
#include <RTClib.h>             // ไลบรารีเวลา
RTC_DS3231 RTC;

#define DHT_A_PIN 3             // ขาดิจิตอลสำหรับเซ็นเซอร์ความชื้น A
#define DHT_A_TYPE DHT11   
DHT dht1(DHT_A_PIN, DHT11);
#define DHT_B_PIN 2 
#define DHT_B_TYPE DHT11 
DHT dht(DHT_B_PIN, DHT11);

const int moisture_A_Pin = A0; // ขาอะนาล็อกสำหรับเซ็นเซอร์ความชื้น A
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
   
  pinMode(13, OUTPUT);            // กำหนดขาดิจิตอล
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);           // กำหนดค่าพอร์ต
  Serial.println(F("DHT11 พร้อมทำงาน "));
 
   
  RTC.adjust(DateTime(2020, 4, 29, 10, 59, 50));   // ตั้งเวลาปัจจุบันสำหรับการทำงานของปั้ม

  DateTime now = RTC.now();
  
}  // วงเล็บ void setup

void loop() 
{                                                             // วงเล็บ void loop

  DateTime now = RTC.now();
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.println(now.second());
  
  int ldr_sensor = map(analogRead(A3), 0, 1023, 100, 0);
  Serial.print(" แสง : ");
  Serial.print(ldr_sensor);
  Serial.println("%");
  
  MoistureA = map(analogRead(moisture_A_Pin), 0, 1023, 0, 100);         // ความชื้นในดิน A
  Serial.print("MoistureA : "); 
  Serial.print(MoistureA); 
  Serial.println("%");  
  MoistureB = map(analogRead(moisture_B_Pin), 0, 1023, 0, 100);         // ความชื้นในดิน B
  Serial.print("MoistureB : "); 
  Serial.print(MoistureB);                  
  Serial.println("%"); 
  int averageMOISTURE = (MoistureA + MoistureB) / 2 ;                 // ความชื้นเฉลี่ยจากกระถาง
  Serial.print("ความชื้นเฉลี่ยในดิน : ");
  Serial.print(averageMOISTURE);  
  Serial.println("%");              

  float h1 = dht1.readHumidity();                                     // ความชื้นในบรรยากาศ ตัวที่ 1
  float t1 = dht1.readTemperature();
  float f1 = dht1.readTemperature(true);
  if (isnan(h1) || isnan(t1) || isnan(f1)) 
  {
    Serial.println(F("ไม่สามารถอ่านข้อมูลจากเซ็นเซอร์ DHT!"));
    return;
  }
  Serial.print(F("ความชื้น1: "));
  Serial.print(h1);
  Serial.print(F("%  อุณหภูมิ: "));
  Serial.print(t1);
  Serial.println(F("°C "));
  
  float h = dht.readHumidity();                                       // ความชื้นบรรยากาศ ตัวที่ 2
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) 
  {
    Serial.println(F("ไม่สามารถอ่านข้อมูลจากเซ็นเซอร์ DHT!"));
    return;
  }
  Serial.print(F("ความชื้น2: "));
  Serial.print(h);
  Serial.print(F("%  อุณหภูมิ: "));
  Serial.print(t);
  Serial.println(F("°C "));
  float averageHUMIDITY = (h + h1) / 2;                                 // ความชื้นบรรยากาศเฉลี่ย
  Serial.print("ความชื้นเฉลี่ยในอากาศ : ");
  Serial.print(averageHUMIDITY);
  Serial.println("%");
  
  controlWaterPumps(now.hour(), now.minute(), now.second(), averageMOISTURE);

  delay(1000);
}

void controlWaterPumps(int hour, int minute, int second, int averageMoisture) {
  if (hour == 6)
  {
    if (minute < 30 && second == 0)
    {
      startWatering();
    }
    if (minute == 30 && second == 0)
    {
      stopWatering();
    }
  }
  else if (hour > 9 && hour < 15)
  {
    controlWaterPump(13, "A", averageMoisture);
    controlWaterPump(12, "B", averageMoisture);
    controlWaterPump(11, "C", averageMoisture);
    controlWaterPump(10, "D", averageMoisture);
    controlWaterPump(9, "E", averageMoisture);
  }
  else if (hour == 16)
  {
    if (minute < 30 && second == 0)
    {
      startWatering();
    }
    if (minute == 30 && second == 0)
    {
      stopWatering();
    }
  }
  else
  {
    stopAllWaterPumps();
  }
}

void controlWaterP
