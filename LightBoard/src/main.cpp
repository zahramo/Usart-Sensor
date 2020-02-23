#include <Arduino.h>



float lux=0.00,ADC_value=0.0048828125,LDR_value;
void setup() {
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

void loop() {
  LDR_value=analogRead(A0);

  lux=(250.000000/(ADC_value*LDR_value))-50.000000;

  // String luxStr = String(lux);

  // Serial.write(luxStr.c_str(), luxStr.length());


  byte* luxBytes = (byte*) &lux;
  Serial.write(luxBytes, 4);

  delay(1000);
}