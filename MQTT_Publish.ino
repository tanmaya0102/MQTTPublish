#include<ESP8266WiFi.h>
#include<Adafruit_MQTT_Client.h>

#define ldr A0 //analog 0
#define wifi "xxxxxx"
#define password "xxxxx"
#define server "io.adafruit.com"
#define port 1883
#define username "xxxxx"
#define key "xxxxxxx"

WiFiClient esp;
Adafruit_MQTT_Client mqtt(&esp,server,port,username,key);
Adafruit_MQTT_Publish feed(&mqtt,username"/feeds/ldr");


void setup() {
  pinMode(16,OUTPUT);
  Serial.begin(115200);
  delay(10);
  Serial.println("\nAdafruit MQTT");
  Serial.print("Connecting to ");
  Serial.println(wifi);
  WiFi.begin(wifi,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    digitalWrite(16,HIGH);
    delay(500);
    digitalWrite(16,LOW);
    delay(500);
   
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.print("Connecting to MQTT");
  while(mqtt.connect())
  {
    Serial.print(".");
    
  }

}
 
void loop() {
  if(mqtt.connected())
  {
    
    int data=analogRead(ldr);
    Serial.print("\nSending LDR val ");
    Serial.print(data);
    Serial.print("..");
    if(feed.publish(data))
    {
      Serial.println("Success");
       digitalWrite(16,HIGH);
    delay(200);
    digitalWrite(16,LOW);
    delay(200);
    }
    else{ 
      Serial.println("Fail!");
      }
      delay(2300);
  }

}
