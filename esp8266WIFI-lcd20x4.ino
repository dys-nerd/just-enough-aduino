#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <LiquidCrystal_I2C.h>


//WiFi router Edit Start

const char* ssid = "Your-SSID";
const char* password = "WIFI-Password";
 
ESP8266WebServer server(80); 
IPAddress ip(192,168,0,8);   
IPAddress gateway(192,168,0,1);   
IPAddress subnet(255,255,255,0);   
//Edit End



int lcdColumns = 20;
int lcdRows = 4;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  
 
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
 
<h2>LCD ONLINE<h2>

</html>
)=====";
 

void handleRoot() {
 String s = MAIN_page; 
 server.send(200, "text/html", s); 
}

void handleForm() {
 //lcd.clear();
 String Line1 = server.arg("l1"); 
 String Line2 = server.arg("l2"); 
 String Line3 = server.arg("l3"); 
 String Line4 = server.arg("l4"); 

 lcd.setCursor(0, 0);
 lcd.print(Line1);
 lcd.setCursor(0, 1);
 lcd.print(Line2);
 lcd.setCursor(0, 2);
 lcd.print(Line3);
 lcd.setCursor(0, 3);
 lcd.print(Line4);
 
 server.send(200, "text/html", "done"); 
}

void setup(void){
  lcd.init();
  lcd.backlight();
  
  WiFi.begin(ssid, password);     
  WiFi.config(ip, gateway, subnet);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  
  }
   
  server.on("/", handleRoot); 
  server.on("/action_page", handleForm); 
 
  server.begin();                  
  
}

void loop(void){
  server.handleClient();  
}
