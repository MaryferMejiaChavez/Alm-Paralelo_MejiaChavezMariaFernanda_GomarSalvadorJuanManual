//#############################################
//#          Gomar Salvador Juan Manuel       #
//#          Mejía Chávez María Fernanda      #
//#############################################

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

String server = "";

const char *ssid = "INFINITUM0934";
const char *password = "KRfwCKEUdT";

const int btnP12 = 4; //D2    
const int btnP1 = 2; //D4    


int p1 = 0;
int act1 = 0;
int p12 = 0;
int act12 = 0;


void setup() {
  
  Serial.begin(115200);

  // led
  pinMode(btnP1, INPUT);
  pinMode(btnP12, INPUT_PULLUP);

  Serial.println("WiFi connected");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }


  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {


  if (WiFi.status() == WL_CONNECTED) {
    if (digitalRead(btnP1) == HIGH) {
      act1 = 1;
      if (p1 != act1) {
        Serial.println("P1 OFF Right");
        post("P1", "OFF Right");
        delay(1000);
        p1 = 1;
      }

    }
    else {
      p1 = 0;
      if (p1 != act1) {
        Serial.println("P1 ON Left");
        post("p1", "OFF Left" );
        delay(1000);
        act1=0;
      }
    }
    // BOTON 2
    if (digitalRead(btnP12) == HIGH) {
      act12 = 1;
      if (p12 != act12) {
        Serial.println("P2 OFF Right");
        post("P2", "OFF Right");
        delay(1000);
        p12 = 1;
      }

    }
    else {
      p12 = 0;
      if (p12!=act12) {
        Serial.println("P2 ON Left");
        post("p2","OFF Left");
        delay(1000);
        act12=0;
      }
    }
    
  }

  delay(2000);

}

//-------------------------------------------------------------------------------------

void post(String boton, String posicion) {
  Serial.println("Inicio post");
  HTTPClient http;
  String json;
  server = "http://192.168.43.179:80/api/btn";

  StaticJsonDocument<256> doc;
  doc["boton"] = String(boton);
  doc["posicion"] = String(posicion);
  serializeJson(doc, json);

  http.begin(server);
  http.addHeader("Content-Type", "application/json");
  http.POST(json);
  http.writeToStream(&Serial);
  http.end();
  Serial.println("Termino post");

}
