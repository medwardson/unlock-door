#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

AsyncWebServer server(80);

bool running = false;

void ensureConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.disconnect();
    WiFi.reconnect();
    Serial.print("Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }

    Serial.println();
    Serial.print("Connected: ");
    Serial.println(WiFi.localIP());
  }
}


void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin("Guaiguais", "MimiSosoEatsPie");
  
  
  server.on("/unlock", HTTP_GET, [](AsyncWebServerRequest *request){
    running = true;
    
    request->send(200, "text/plain", "Door unlocked");
  });
  

  server.begin();
}

void loop() {
  ensureConnection();
  
  delay(100);
  
  if (running) {
    Serial.println("Call button on...");
    digitalWrite(3, HIGH);
    delay(2000);
    
    Serial.println("Unlock button on...");
    digitalWrite(2, HIGH);
    delay(1000);
    
    Serial.println("Unlock button off...");
    digitalWrite(2, LOW);
    delay(2000);
    
    Serial.println("Call button off...");
    digitalWrite(3, LOW);
    delay(500);
    Serial.println("Call button on...");
    digitalWrite(3, HIGH);
    delay(500);
    Serial.println("Call button off...");
    digitalWrite(3, LOW);

    running = false;
  }
}