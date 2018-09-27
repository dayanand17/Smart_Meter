#include <ESP8266WiFi.h> // Include the Wi-Fi library
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <HMC5883L.h>
HMC5883L compass;

WiFiClient client;

String thingSpeakAddress= "http://api.thingspeak.com/update?";
String writeAPIKey;
String tsfield1Name;
String request_string;

HTTPClient http;
void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');
  Serial.println("Initialize HMC5883L"); while (!compass.begin()) { Serial.println("Could not find a valid HMC5883L sensor, check wiring!"); delay(500); }

// Set measurement range 
compass.setRange(HMC5883L_RANGE_1_3GA);

// Set measurement mode 
compass.setMeasurementMode(HMC5883L_CONTINOUS); // Set data rate compass.setDataRate(HMC5883L_DATARATE_15HZ);

// Set number of samples averaged 
compass.setSamples(HMC5883L_SAMPLES_8);


  WiFi.begin("Redmi","12345689");          //connecting accesspoint to internet
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
Serial.println(" wifinotconnected");
   }
  Serial.println(WiFi.softAPIP());         // Send the IP address of the ESP8266 to the computer
}
int Xaxis; int Yaxis; int Zaxis; int sumAxis; int lastSumAxis;
void loop() { 
  Serial.println("ihjgsif");  
Vector raw = compass.readRaw(); 

Vector norm = compass.readNormalize();

Xaxis = norm.XAxis;

Yaxis = norm.YAxis;   

Zaxis = norm.ZAxis;

Xaxis = (Xaxis / 1) * 1; 

Yaxis = (Yaxis / 1) * 1;

Zaxis = (Zaxis / 1) * 1;

sumAxis = Xaxis + Yaxis + Zaxis;
Serial.print(" Sum Axis = "); 
Serial.print(sumAxis);
Serial.print(" X Axis = "); 
Serial.print(Xaxis);
Serial.print(" Y Axis = "); 
Serial.print(Yaxis);
Serial.print(" Z Axis = "); 
Serial.print(Zaxis);
Serial.println();
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
      request_string += sumAxis;
      http.begin(request_string);
      http.GET();
      http.end();

    }
    }

