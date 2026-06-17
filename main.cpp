# IoT-Transformer-Monitor
IoT-Based Transformer Monitoring &amp; Alert System using ESP32 and ThingSpeak

#include <WiFi.h>
#include "DHT.h"

const int potPin = 34; 
const String apiKey = "6FDPYI1XA2830ZUB"; 

DHT dht(13, DHT22);
WiFiClient client;

int temp_ticks = 0;
int load_ticks = 0;

bool temp_locked = false;
bool load_locked = false;
bool crit_locked = false;

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  WiFi.begin("Wokwi-GUEST", "");
  Serial.print("Connecting to WiFi");
  
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");
}

void loop() {
  float t = dht.readTemperature();
  int load = analogRead(potPin);
  
  if(isnan(t)){
    Serial.println("DHT read failed");
    return;
  }

  Serial.printf("Temp: %.2f | Load: %d\n", t, load);

  int alert_val = 0; // 0=normal, 1=temp, 2=load, 3=both

  if(t > 75.0) {
    temp_ticks++;
  } else {
    temp_ticks = 0; 
    temp_locked = false; 
  }

  if(load > 3000) {
    load_ticks++;
  } else {
    load_ticks = 0;
    load_locked = false; 
  }

  // trigger alerts if active for ~15s (2 ticks)
  if(temp_ticks >= 2 && !temp_locked) {
    Serial.println("Temp warning triggered");
    alert_val = 1; 
    temp_locked = true; 
  }

  if(load_ticks >= 2 && !load_locked) {
    Serial.println("Load warning triggered");
    alert_val = 2; 
    load_locked = true; 
  }

  if(temp_ticks >= 2 && load_ticks >= 2) {
    if(!crit_locked) {
      Serial.println("CRITICAL: Both thresholds exceeded");
      alert_val = 3; 
      crit_locked = true; 
    }
  } else {
    crit_locked = false;
  }

  if(client.connect("api.thingspeak.com", 80)) {
    String url = "/update?api_key=" + apiKey + "&field1=" + String(t) + "&field2=" + String(load) + "&field3=" + String(alert_val);
    
    client.print(String("GET ") + url + " HTTP/1.1\r\nHost: api.thingspeak.com\r\nConnection: close\r\n\r\n");
    Serial.println("Data pushed to cloud.");
    
    delay(500); 
    
    while(client.available()){
      client.readStringUntil('\n');
    }
  }
  
  client.stop();
  delay(15000); 
}
