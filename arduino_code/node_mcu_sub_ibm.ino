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
char subtopic[] = "iot-2/cmd/state/fmt/json";
char username[]="use-token-auth";
char passwd[]=TOKEN;
char clientid[]="d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

void callback(char* topic, byte* payload, unsigned int payloadLength) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  DynamicJsonDocument doc(1024);
  String input =String((char *)payload);
  deserializeJson(doc, input);
  JsonObject obj = doc.as<JsonObject>();
  String state=obj[String("state")];
  Serial.println(state);
 if(state=="off"){
    digitalWrite(LED_BUILTIN, HIGH);
  }else if(state=="on"){
    digitalWrite(LED_BUILTIN, LOW);
  }
}

WiFiClient wifiClient;
PubSubClient client(server,1883,callback,wifiClient);

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
  //---------------------------------------SUBSCRIBE TO TOPIC------------------------------------------
  if (client.subscribe(subtopic)) {
        Serial.println("subscribe to responses OK");
  } else {
        Serial.println("subscribe to responses FAILED");
  }
}

void loop() {
  if(!client.loop()){
        //---------------------------------------CONNECT TO IBM IOT SERVER------------------------------------
       Serial.print("connecting to ssid:");
       Serial.print(server);
        while(!client.connect(clientid,username,passwd)){
          Serial.print(".");
          delay(500);
        }
       Serial.print("\nconnceted to:");
       Serial.println(server);
      //---------------------------------------SUBSCRIBE TO TOPIC------------------------------------------
      if (client.subscribe(subtopic)) {
            Serial.println("subscribe to responses OK");
      } else {
            Serial.println("subscribe to responses FAILED");
      }
  }
}
