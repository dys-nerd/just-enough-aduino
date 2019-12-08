#include <ESP8266WiFi.h>

// edit Start  your network credentials
const char* ssid     = "Your-SSID";
const char* password = "Wifi Password";


WiFiServer server(80);
IPAddress ip(192,168,0,7);   
IPAddress gateway(192,168,0,1);   
IPAddress subnet(255,255,255,0);

//edit end
  

String header;
String output13State = "on";
String output12State = "on";
String output15State = "on";
String output14State = "on";

const int output13 = 13;
const int output12 = 12;
const int output15 = 15;
const int output14 = 14;

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup() {
  pinMode(output13, OUTPUT);
  pinMode(output12, OUTPUT);
  pinMode(output15, OUTPUT);
  pinMode(output14, OUTPUT);

  digitalWrite(output13, LOW);
  digitalWrite(output12, LOW);
  digitalWrite(output15, LOW);
  digitalWrite(output14, LOW);

  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.begin();
}

void loop(){
  WiFiClient client = server.available();   

  if (client) {                             
    String currentLine = "";
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { 
      currentTime = millis();         
      if (client.available()) {            
        char c = client.read();            
        header += c;
        if (c == '\n') {  
                 
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
         
            if (header.indexOf("GET /12/off") >= 0) {
              output12State = "off";
              digitalWrite(output12, HIGH);
            } else if (header.indexOf("GET /12/on") >= 0) {
              output12State = "on";
              digitalWrite(output12, LOW);
            
            } else if (header.indexOf("GET /13/off") >= 0) {
              output13State = "off";
              digitalWrite(output13, HIGH);
            } else if (header.indexOf("GET /13/on") >= 0) {
              output13State = "on";
              digitalWrite(output13, LOW);
            
            } else if (header.indexOf("GET /14/off") >= 0) {
              output14State = "off";
              digitalWrite(output14, HIGH);
            
            } else if (header.indexOf("GET /14/on") >= 0) {
              output14State = "on";
              digitalWrite(output14, LOW);
            
            } else if (header.indexOf("GET /15/off") >= 0) {
              output15State = "off";
              digitalWrite(output15, HIGH);
            } else if (header.indexOf("GET /15/on") >= 0) {
              output15State = "on";
              digitalWrite(output15, LOW);
            }
                
            if (output12State=="off") {
              client.print("0");
            } else {
              client.print("1");
            } 
                
            if (output13State=="off") {
              client.print("0");
            } else {
              client.print("1");
            }
            
            if (output14State=="off") {
              client.print("0");
            } else {
              client.print("1");
            }
            
            if (output15State=="off") {
              client.print("0");
            } else {
              client.print("1");
            }
          
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }
      }
    }
    
    header = "";
    
    client.stop();
    }
}
