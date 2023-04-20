#include <ESP32Ping.h>
#include <M5StickCPlus.h>
#include <HTTPClient.h>


unsigned long myChannelNumber = 1695691;
const char * myWriteAPIKey = "TPVT3DDCY3HZJ3HT";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "LF";
char pass[] = "hesloksiti";

const IPAddress remote_ip(192, 168, 0, 98); //hlasny mobil 192.168.0.192 : 192, 168, 1, 3  LF: 192.168.0.98

String serverName ;

unsigned long timerDelay = 6000;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)

void setup()
{
  // Debug console
  M5.begin();
  Serial.begin(115200);
 
 
  WiFi.begin(ssid, pass);
  M5.Lcd.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }
  
  Serial.println("");
  Serial.println("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());

  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
   delay(1000);
}

void loop() 
{
  M5.Lcd.println("loop");

lastTime = millis();
      //Send an HTTP POST request every 10 minutes
      M5.Lcd.println(millis());
      M5.Lcd.println(timerDelay);
M5.Lcd.println(millis() - lastTime);   

IPAddress ip (192, 168, 0, 98); // The remote ip to ping
    bool ret = Ping.ping(ip);
    
    if (ret) {
      M5.Lcd.println("pritomen");
      serverName = "https://api.thingspeak.com/update?api_key=TPVT3DDCY3HZJ3HT&field3=1";

     } else {
      M5.Lcd.println("nepritomen");
      serverName = "https://api.thingspeak.com/update?api_key=TPVT3DDCY3HZJ3HT&field3=0";
     }

  if ((lastTime) > timerDelay) {
    timerDelay += 30000;
    //Check WiFi connection status
    if(WiFi.status() == WL_CONNECTED){
      HTTPClient http;
      M5.Lcd.println("pripojeno");
      String serverPath = serverName;
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());
      
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      M5.Lcd.println("=====");
      M5.Lcd.println(httpResponseCode);
            M5.Lcd.println("======");


      if (httpResponseCode>0) {
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
  }

  // put your main code here, to run repeatedly:  
      
      delay(2000);
      M5.Lcd.fillScreen(BLACK);

      M5.Lcd.println("");
      M5.Lcd.println("Connected to WiFi network with IP Address: ");
      M5.Lcd.println(remote_ip);
      M5.Lcd.println(WiFi.macAddress());
      M5.Lcd.setCursor(0, 110);
}
