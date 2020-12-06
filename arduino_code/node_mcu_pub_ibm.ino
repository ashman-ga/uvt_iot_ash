#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

/*
 * connect to local wifi router
*/
const char* ssid="xxxx";//wifi ssid
const char* password="xxxx";//wifi password

#define ORG "xxxx"
#define DEVICE_TYPE "xxxx"
#define DEVICE_ID "xxxx"
#define TOKEN "xxxx"

char server[]=ORG".messaging.internetofthings.ibmcloud.com";
char pubtopic[] = "iot-2/evt/temperature/fmt/json";
char username[]="use-token-auth";
char passwd[]=TOKEN;
char clientid[]="d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClient wifiClient;
PubSubClient client(server,1883,NULL,wifiClient);

void setup() {
  Serial.begin(9600);
  Serial.println();
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.println("IBM Watson IoT NodeMCU practicle");
//----------------------------------------SET UP WIFI CONNECTION--------------------------------------
  Serial.print("connecting to ssid:");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
      Serial.print(".");
      digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off 
      delay(100);  
  }
 Serial.print("\nWiFi connected, IP address: "); 
 Serial.println(WiFi.localIP());
//---------------------------------------CONNECT TO IBM IOT SERVER------------------------------------
 Serial.print("connecting to ssid:");
 Serial.print(server);
  while(!client.connect(clientid,username,passwd)){
    Serial.print(".");
    delay(500);
  }
 Serial.print("\nconnceted to:");
 Serial.println(server);
//----------------------------------------------------------------------------------------------------
}

void loop() {
  String temp_data="{\"temp\":"+String(random(0,50))+"}";
  Serial.println(temp_data);
  if (!client.publish(pubtopic,(char*) temp_data.c_str())){
    Serial.print("failed!!!");
  }
  delay(1000);
}
