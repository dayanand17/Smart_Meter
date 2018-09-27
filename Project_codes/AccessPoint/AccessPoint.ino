#include <ESP8266WiFi.h> // Include the Wi-Fi library
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>

WiFiClient client;

String thingSpeakAddress= "http://api.thingspeak.com/update?";
String writeAPIKey;
String tsfield1Name;
String request_string;

HTTPClient http;


const char *ssid = "AccessPoint2"; // The name of the Wi-Fi network that will be created
const char *password = "openforall";   // The password required to connect to it, leave blank for an open network

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  WiFi.softAP(ssid, password);             // Start the access point
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");

  Serial.print("IP address:\t");
 WiFi.begin("Redmi","12345689");          //connecting accesspoint to internet
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
Serial.println(" wifinotconnected");
   }
  Serial.println(WiFi.softAPIP());         // Send the IP address of the ESP8266 to the computer
}

void loop() { 
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
      request_string += "15";
      http.begin(request_string);
      http.GET();
      http.end(); 

  }
}
