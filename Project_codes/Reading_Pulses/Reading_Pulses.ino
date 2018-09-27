#include <ESP8266WiFi.h>

static const uint8_t D1 = 5;
volatile byte interruptCounter = 0;
int PulsePin = D1;
int Pulses = 0;
void setup(void)
{
  Serial.begin(115200);
pinMode(PulsePin, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(PulsePin), handleInterrupt, CHANGE);
}

void loop(){
if (interruptCounter > 0) {
      
      Pulses++;
      Serial.println("interruptcounter");
      Serial.println(interruptCounter);
      interruptCounter--;
      Serial.println("inside if");
      
      }
Serial.println(Pulses);
   
  delay(20000);
}
void handleInterrupt() {
  interruptCounter++;
}
