#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <AltSoftSerial.h>

#define RXPIN 9
#define TXPIN 8

float datas[2];

AltSoftSerial altSerial;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

float getDataFromLightBoard(){
  float lux = 0;
  if (Serial.available() >= 4) {
    lux = Serial.parseFloat();
  } 
  return lux;

}

// void getDataFromThBoard(){
//   char c;
//   int i=0;
//   int status = 0; // 0: initial, 1: humidity, 2: temperature
//   Serial.println("we are here out of while");
//   while(altSerial.available()) {
//     Serial.println("we are here");
//     c = altSerial.read();
//   }
//   // floatBytes bn;
//   // char c= '!';
//   // int i = 0;
//   // while(altSerial.available() && c != '#')
//   // { 
//   //   c = altSerial.read();
//   //   bn.binary[i++] = c;
//   //   Serial.println(bn.binary[i]);
//   // }
//   // Serial.println(bn.fb);
//   // return bn.fb;
// }

void printResponseInLcd(float humidity, float temp, float lux) {
  if (humidity > 80) {
    lcd.print("Abyari soorat nagirad");
  }
  else if (humidity > 50){
    if (temp <= 25) {
      if (lux < 600)
        lcd.print("Abyari ba nerkhe 10 ghatre/min");
      else if (lux >= 600)
        lcd.print("Abyari ba nerkhe 5 ghatre/min");
    }
    else {
      lcd.print("Abyari ba nerkhe 10 ghatre/min");
    }
  }
  else {
    lcd.print("Abyari ba nerkhe 15cc/min");  
  }
}

void setup() {
  pinMode(RXPIN, INPUT);
  pinMode(TXPIN, OUTPUT);

  lcd.begin(16,4);
  Serial.begin(9600);
  altSerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float lux = getDataFromLightBoard();
  // float humidity = datas[0];
  // float temperature = datas[1];
  Serial.print("lux: ");
  Serial.println(lux);
  // getDataFromThBoard();
  // Serial.print("humidity: ");
  // Serial.println(humidity);
  // Serial.print("temp: ");
  // Serial.println(temperature);
  // lcd.print(response);
  // printResponseInLcd(humidity, temperature, lux);
  delay(100);
}