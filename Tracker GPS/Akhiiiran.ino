#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "TinyGPS++.h"
#include "SoftwareSerial.h"



SoftwareSerial serial_connection(5, 4); // TX, RX 
TinyGPSPlus gps; // Objet GPS pour traiter les données NMEA


const char* ssid = "Wifi";
const char* password = "password";

//Your Domain name with URL path or IP address with path
String serverName = "http://demo4.traccar.org:5055/?id=espesto&lat=34.6472449&lon=-1.908572";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

void setup() {
  Serial.begin(115200); 
  serial_connection.begin(9600); // Démarre la communication série avec le GPS

  Serial.println("GPS Start"); // Affiche un message pour indiquer que le sketch a démarré
  
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {


  while (serial_connection.available()) {
    // Lire et encoder les données NMEA provenant du GPS
    gps.encode(serial_connection.read());
  }
  if (gps.location.isUpdated()) { 

    String traccar_id = "test123";   

    String serverName = "http://demo4.traccar.org:5055/?id="+traccar_id;
    // String serverName = "http://demo4.traccar.org:5055/?id=espesto&lat=34.6472449&lon=-1.908572";
    serverName += "&lat="+String(gps.location.lat());
    serverName +="&lon="+String(gps.location.lng());

    


    if ((millis() - lastTime) > timerDelay) {
      //Check WiFi connection status
      if(WiFi.status()== WL_CONNECTED){
        WiFiClient client;
        HTTPClient http;

        String serverPath = serverName;
        
        // Your Domain name with URL path or IP address with path
        http.begin(client, serverPath.c_str());
    
        // If you need Node-RED/server authentication, insert user and password below
        //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
          
        // Send HTTP GET request
       
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode);
          String payload = http.getString();
          Serial.println(payload);
        }
        else {
          Serial.print("Error code: ");
          Serial.println(httpResponseCode);
        }
        // Free resources
        http.end();
      }
      else {
        Serial.println("WiFi Disconnected");
      }
      lastTime = millis();
    }
  }

  //Send an HTTP POST request depending on timerDelay
  
}