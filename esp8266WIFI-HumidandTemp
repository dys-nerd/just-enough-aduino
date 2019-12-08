#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22
 
//WiFi router edit start
const char* ssid = "Your-SSID";
const char* password = "WIFI-Password";

ESP8266WebServer server(80); 
IPAddress ip(192,168,0,9);   
IPAddress gateway(192,168,0,1);   
IPAddress subnet(255,255,255,0);   
//Edit End


DHT dht(DHTPIN, DHTTYPE); 
void handleRoot() {
 
 float h = dht.readHumidity();
 float t = dht.readTemperature();
 float f = dht.readTemperature(true);
 String hs = String(h, 1) ; 
 String ts = String(t, 1) ;
 server.send(200, "text/html", hs+"-"+ts); 
 
}

void setup(void){
  dht.begin();
  WiFi.begin(ssid, password);     
  WiFi.config(ip, gateway, subnet);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  
  }
 
  server.on("/", handleRoot);    
  server.begin();                
  
}

void loop(void){
  server.handleClient();
}
