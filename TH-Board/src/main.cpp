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
// Start I2C transmission  
  Wire.beginTransmission(Addr);  
  // Send humidity measurement command, NO HOLD master  
  Wire.write(0xF5);  
  // Stop I2C transmission  
  Wire.endTransmission();  
  delay(500);
  // Request 2 bytes of data  
  Wire.requestFrom(Addr, 2);
// Read 2 bytes of data  
// humidity msb, humidity lsb  
  if(Wire.available() == 2)  
  {    
    data[0] = Wire.read();    
    data[1] = Wire.read();
    // Convert the data    
    float humidity = (((data[0] * 256.0 + data[1]) * 125.0) / 65536.0) - 6;
    // Output data to Serial Monitor   
    byte* humidityBytes = (byte*) &humidity; 
    Serial.write("#");    
    Serial.write(humidityBytes, 4);
  }
  // Start I2C transmission  
  Wire.beginTransmission(Addr);  
  // Send temperature measurement command, NO HOLD master  
  Wire.write(0xF3);  
  // Stop I2C transmission  
  Wire.endTransmission();  
  // Request 2 bytes of data  
  Wire.requestFrom(Addr, 2);
  // Read 2 bytes of data  
  // temp msb, temp lsb  
  if(Wire.available() == 2)  
  {    
  data[0] = Wire.read();    
  data[1] = Wire.read();
  // Convert the data    
  float cTemp = (((data[0] * 256.0 + data[1]) * 175.72) / 65536.0) - 46.85;    
  // Output data to Serial Monitor  
  byte* tempBytes = (byte*) &cTemp;
  Serial.write("*");    
  Serial.write(tempBytes, 4);
  Serial.write("@");
  delay(100);
  }  
}