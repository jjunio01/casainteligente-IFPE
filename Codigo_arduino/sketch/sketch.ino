#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
char* usuario = "mikael";
char* senha = "12345678";
bool statusConexao = false;
char* host = "https://esp8266-82004-default-rtdb.firebaseio.com/";
char* token = "o5r4y9BSVdio6bLBwXy6F4NnVIFP7tUWq6kV7zQ4";

FirebaseData minhaBase;


void setup() {
  
  Serial.begin(115200);
  pinMode(4,OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(usuario, senha);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
    }
    
  statusConexao = true;
  Firebase.begin(host, token);

}

void loop() {
  
  Firebase.get(minhaBase, "led/status");
  int led = minhaBase.intData();

  switch(led){

    case 0:
      digitalWrite(4,LOW);
      break;

    case 1:
      digitalWrite(4,HIGH);
      break;
    
    
    }
 
  
}
