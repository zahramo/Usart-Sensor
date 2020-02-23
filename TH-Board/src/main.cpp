#include <Arduino.h>
#include<Wire.h>

// SHT25 I2C address is 0x40(64)ds
#define Addr 0x40

void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{
  unsigned int data[2];   
  Wire.beginTransmission(Addr);    
  Wire.write(0xF5);    // Send humidity measurement command, NO HOLD master
  Wire.endTransmission();  
  delay(500);  
  Wire.requestFrom(Addr, 2);
  if(Wire.available() == 2) // humidity msb, humidity lsb   
  {    
    data[0] = Wire.read();    
    data[1] = Wire.read(); 
    float humidity = (((data[0] * 256.0 + data[1]) * 125.0) / 65536.0) - 6;    
    byte* humidityBytes = (byte*) &humidity; 
    Serial.write("#");    
    Serial.write(humidityBytes, 4);  
  }
  Wire.beginTransmission(Addr);    
  Wire.write(0xF3);   
  Wire.endTransmission();  
  delay(500); 
  Wire.requestFrom(Addr, 2); 
  if(Wire.available() == 2)  
  {    
    data[0] = Wire.read();    
    data[1] = Wire.read();  
    float cTemp = (((data[0] * 256.0 + data[1]) * 175.72) / 65536.0) - 46.85;        
    byte* tempBytes = (byte*) &cTemp;
    Serial.write("*");    
    Serial.write(tempBytes, 4); 
  }  
  Serial.write("@");
  delay(300);
}