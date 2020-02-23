#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <AltSoftSerial.h>

#define RXPIN 9
#define TXPIN 8

float datas[2];

AltSoftSerial altSerial;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

typedef union{
  float fp;
  byte bin[4];
} FloatBytes;

FloatBytes humidity;
FloatBytes temp;

float getDataFromLightBoard(){
  float lux = 0;
  if (Serial.available() >= 4) {
    lux = Serial.parseFloat();
  } 
  return lux;

}

void getDataFromThBoard(){
  char c;
  int i = 0;
  int status = 0; // 0: initial, 1: humidity, 2: temperature
  Serial.println(altSerial.available());
  if (altSerial.available() >= 11) {
    Serial.println("in hello");
    while (1){
      c = altSerial.read();
      // Serial.print(c);
      if (c == '#') {
        status = 1;
        i = 0;
        continue;
      }
      else if (c == '*'){
        status = 2;
        i = 0;
        continue;
      }
      else if (c == '@')
        break;
      if (status == 1) {
        humidity.bin[i++] = c;
      }
      else if (status == 2){
        temp.bin[i++] = c;
      }
    }
  }
}

void printResponseInLcd(float humidity, float temp, float lux) {
  if (humidity > 80) {
    lcd.print("no watering");
  }
  else if (humidity > 50){
    if (temp <= 25) {
      if (lux < 600)
        lcd.print("10 drop/min");
      else if (lux >= 600)
        lcd.print("5 drop/min");
    }
    else {
      lcd.print("10 drop/min");
    }
  }
  else {
    lcd.print("15 cc/min");  
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
  getDataFromThBoard();
  // Serial.print("hum: ");
  // Serial.println(humidity.fp);
  // Serial.print("tmp: ");
  // Serial.println(temp.fp);
  lcd.setCursor(0, 0);
  lcd.print("hum: ");
  lcd.print(humidity.fp);
  lcd.setCursor(0, 1);
  lcd.print("tmp: ");
  lcd.print(temp.fp);
  lcd.setCursor(0, 2);
  lcd.print("lux: ");
  lcd.print(lux);
  lcd.setCursor(0, 3);
  lcd.print("** ");
  printResponseInLcd(humidity.fp, temp.fp, lux);  
  delay(300);
  lcd.clear();
}