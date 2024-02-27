#include <WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "AtanasiPhone";
const char* password =  "otednodoosem";
const char* mqttServer = "mqtt.flespi.io";
const int mqttPort = 1883;
const char* mqttUser = "5EkGEfG77dV4XBdyy07zwvqgCenEmAEf5PLxShuPkgH6FLs3zpsWIG0aLdDXC72x";
const char* mqttPassword = "*";

#define BUTTON_PIN_SATISFIED 13
#define BUTTON_PIN_KINDA_SATISFIED 14
#define BUTTON_PIN_NOT_SATISFIED 25
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {

  pinMode(BUTTON_PIN_SATISFIED, INPUT_PULLUP);
  pinMode(BUTTON_PIN_KINDA_SATISFIED, INPUT_PULLUP);
  pinMode(BUTTON_PIN_NOT_SATISFIED, INPUT_PULLUP);


 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("my/", "Hello from ESP32");
 
}
 
void loop() {
  
  client.loop();

  int button = digitalRead(BUTTON_PIN_NOT_SATISFIED);
  if(button == LOW ){
    Serial.println(button);
  }
  
}


