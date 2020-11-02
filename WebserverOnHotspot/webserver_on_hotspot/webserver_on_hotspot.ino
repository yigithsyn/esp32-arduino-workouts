/*
  OUTPUT: Creating your own hotspot on esp32 wifi+ble module.
  Author: Ankit Rana (Futechiot)
  Board Used: esp32 development board, LolinD32,WEMOS LOLIN32, ESP32 MH-ET live Minikit
  Website: www.futechiot.com
  GitHub: https://github.com/futechiot
  
*/

/*
  Webserver methods are taken from offical HelloServer example.
*/

#include <WiFi.h>              //wifi library for ESp32 to access other functionalities
#include <WebServer.h>

// Set these to your desired credentials.
const char *Apssid = "ESP32-CAM";     //Give AccessPoint name whatever you like. (this will be Name of your esp32 HOTSPOT)
const char *Appassword = "12345678";         //Password of your Esp32's hotspot,(minimum length 8 required)

WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);                   // To enable Serial Commmunication with connected esp32 board
  Serial.println();
  Serial.println("Configuring access point...");
  WiFi.mode(WIFI_AP);                    // Changing ESP32 wifi mode to AccessPoint

  // You can remove the Appassword parameter if you want the hotspot to be open.
  WiFi.softAP(Apssid, Appassword);      //Starting AccessPoint on given credential
  IPAddress myIP = WiFi.softAPIP();     //IP Address of our Esp8266 accesspoint(where we can host webpages, and see data)
  Serial.print("AP IP address: ");
  Serial.println(myIP);                //Default IP is 192.168.4.1

  Serial.println("Scan For Wifi in your Mobile or laptop, you will see this network");

  server.on("/", handleRoot);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
