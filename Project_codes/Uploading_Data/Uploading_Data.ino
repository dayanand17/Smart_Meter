
#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

WiFiClient client;
double Voltage =0;
String thingSpeakAddress= "http://api.thingspeak.com/update?";
String writeAPIKey;
String tsfield1Name;
String request_string;

HTTPClient http;

void setup()
{Serial.begin(9600);
    WiFi.disconnect();
   WiFi.begin("Redmi","12345689");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
Serial.println(" wificonnected");
  }

}


void loop()
{
Voltage = getVPP();
 VRMS = (Voltage/2.0) *0.707; 
 AmpsRMS = (VRMS * 1000)/mVperAmp;
 Serial.print(AmpsRMS);
 Serial.println(" Amps RMS");
delay(50);


  
     Serial.println(" running");
    if (client.connect("api.thingspeak.com",80)) {
       Serial.println(" running1");
      writeAPIKey = "key=B3XA5D14MC0R2ZU6";
      tsfield1Name = "&field1=10";
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "B3XA5D14MC0R2ZU6";
      request_string += "&";
      request_string += "field1";
      request_string += "=";
      request_string += AmpsRMS;
      http.begin(request_string);
      http.GET();
      http.end();

    }
    delay(3000);

}
float getVPP()
{
  float result;
  
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensorIn);
    
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the maximum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
   
     Serial.println(result);
    delay(1000);
   return result;
   
 }
