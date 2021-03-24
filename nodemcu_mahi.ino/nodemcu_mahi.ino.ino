#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h> 
#include <ArduinoJson.h> 
#include <SoftwareSerial.h> 
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

const char* ssid = "DC 5G";
const char* password = "CastaLia"; 
SoftwareSerial NodeMCU(D2,D3); 

void setup()  
{ 
 Serial.begin(9600); 
 NodeMCU.begin(4800); 
 pinMode(D2,INPUT); 
 pinMode(D3,OUTPUT); 
  
 WiFi.begin(ssid, password); 
 while (WiFi.status() != WL_CONNECTED)  
 { 
 delay(1000); 
 Serial.println("Connecting..."); 
 } 
 Serial.println(WiFi.localIP());

 server.on("/body", handleBody);
 
 server.begin();
 Serial.println("Server listening");
} 

void loop()  
{
  server.handleClient();
} 

void handleBody() { //Handler for the body path
 
      if (server.hasArg("plain")== false){ //Check if body received
 
            server.send(200, "text/plain", "Body not received");
            return;
 
      }
 
      String message = "Body received:\n";
             message += server.arg("plain");
             message += "\n";
 
      server.send(200, "text/plain", message);
      Serial.println(message);
      NodeMCU.println(message);
}
