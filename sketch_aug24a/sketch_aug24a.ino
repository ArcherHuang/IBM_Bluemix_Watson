// Bridge
#include <Bridge.h>

// OLED
#include <Wire.h>
#include <SeeedGrayOLED.h>
#include <avr/pgmspace.h>

#include "DHT.h"
#define DHTPIN A0     
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);


// Touch Sensor
int TouchPin = 5;

void setup() 
{
    Serial.begin(9600); 
    dht.begin();
    Bridge.begin();

    // Touch Sensor
    pinMode(TouchPin, INPUT);

    // OLED
     Wire.begin();
    SeeedGrayOled.init();             //initialize SEEED OLED display
    SeeedGrayOled.clearDisplay();     //Clear Display.
    SeeedGrayOled.setNormalDisplay(); //Set Normal Display Mode
    SeeedGrayOled.setVerticalMode();  // Set to vertical mode for displaying text
    SeeedGrayOled.setTextXY(0,0); //設定啟始坐標
    SeeedGrayOled.putString("Env Info"); 
}

void loop() 
{
    int sensorValue = digitalRead(TouchPin);
    if(sensorValue==1)
    {
      Serial.print(" touch sensor pressed ");
    }else{
      //Serial.print(" touch sensor do not touch ");
    }
    Serial.print("\n");
    

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    // check if returns are valid, if they are NaN (not a number) then something went wrong!
    if (isnan(t) || isnan(h)) 
    {
        Serial.println("Failed to read from DHT");
    } 
    else 
    {
        // DHT
        Serial.print("Humidity: "); 
        Serial.print(h);
        Serial.print(" %\t");
        Serial.print("Temperature: "); 
        Serial.print(t);
        Serial.println(" *C");

        // OLED
       SeeedGrayOled.setTextXY(2,0); //設定啟始坐標
       SeeedGrayOled.putString("Temp: "); 
       SeeedGrayOled.putNumber(t); 
       SeeedGrayOled.putString(" *C"); 
       SeeedGrayOled.setTextXY(4,0); //設定啟始坐標
       SeeedGrayOled.putString("Humi: "); 
       SeeedGrayOled.putNumber(h); 
       SeeedGrayOled.putString(" %"); 

       // Bridge
       Bridge.put("touchSensorStatus", String(sensorValue));
       
    }
    
    delay(1000); //每秒回傳一次資料
    
}


