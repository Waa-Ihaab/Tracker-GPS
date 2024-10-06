Real-Time GPS Tracker  
This project provides a real-time GPS tracker based on the ESP8266 and a GPS module, integrating interactive maps and a user-friendly mobile application. Our solution addresses the growing need for location tracking and management, with potential applications in various sectors such as logistics, security, and fleet management.  


![IMG_1283](https://github.com/user-attachments/assets/914dcee6-e585-4b5a-9cb0-aa4b66be181f)  

How It Works?!  

The GPS tracker code is designed to read location data from the GPS module, process it through the ESP8266, and send the data to a remote server for tracking in real-time. Below is a breakdown of the key components of the code and how they function:

Setup Phase:

The ESP8266 connects to a WiFi network using the provided SSID and password.
The serial communication is initialized to communicate with the GPS module, and a connection to the remote server (such as Traccar) is established.
cpp
Copier le code
const char* ssid = "Wifi";
const char* password = "password";
WiFi.begin(ssid, password);
Reading GPS Data:

The TinyGPS++ library reads and decodes the GPS data received from the module. It continuously checks if the location data (latitude and longitude) is updated.
When new GPS coordinates are available, they are extracted and stored in variables.
cpp
Copier le code
while (serial_connection.available()) {
    gps.encode(serial_connection.read());
}
if (gps.location.isUpdated()) {
    float latitude = gps.location.lat();
    float longitude = gps.location.lng();
}
Sending Data to Server:

The latitude and longitude data are sent as HTTP GET requests to the remote tracking server.
The server's URL is dynamically constructed with the new coordinates and an identifier for the device (id).
cpp
Copier le code
String serverName = "http://demo4.traccar.org:5055/?id=your_device_id&lat=" + String(latitude) + "&lon=" + String(longitude);
Timing & Reconnection:

The tracker sends location updates at specified intervals (e.g., every 5 seconds). If the WiFi connection is lost, it attempts to reconnect before sending the next update.
This ensures continuous tracking even in case of network disruptions.
cpp
Copier le code
if ((millis() - lastTime) > timerDelay) {
    if(WiFi.status() == WL_CONNECTED){
        HTTPClient http;
        http.begin(client, serverPath.c_str());
        int httpResponseCode = http.GET();
    }
}
Real-Time Monitoring:

The server collects and visualizes the GPS data in real-time on the map, allowing users to track the device's movement via the mobile or web app.


ESP8266 Module  
Module GPS Neo-6M  
Traccar  

![nodemcu-gps-wiring](https://github.com/user-attachments/assets/0eea4e2b-4e25-450a-9fa1-b5ee3161e10d)  


![a9bb7bccb7169d1df279e2e50644b5b98cae0009_2_1035x729](https://github.com/user-attachments/assets/9f52d155-77aa-43b6-ad7a-add4d823b87c)  


Result 

![IMG_1222](https://github.com/user-attachments/assets/59d78ec2-5b83-4762-9706-e2a9b3c00782)



