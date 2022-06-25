#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
char* usuario = "mikael";
char* senha = "12345678";
bool statusConexao = false;
char* host = "https://esp8266-82004-default-rtdb.firebaseio.com/";
char* token = "o5r4y9BSVdio6bLBwXy6F4NnVIFP7tUWq6kV7zQ4";

#define lampadaQuarto D3;
#define lampadaQuarto2 D5;
#define lampadaSala D4;
#define lampadaBanheiro D6;
#define lamadaVaranda D7;
#define rele D8;
#define sensorTemperatura A0;

FirebaseData minhaBase;


void atualizarStatus(int comodo, int novaSituacao) {
  
  if (novaSituacao == 0) {
    digitalWrite(comodo,HIGH);
  } else {
    digitalWrite(comodo,LOW);
  }
}

void ligaArcondicionado() {
  if(analogRead(sensorTemperatura > 20)) {
    digitalWrite(rele,HIGH);
  }
}

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
  Firebase.get(minhaBase, "quartoUm/status");
  Firebase.get(minhaBase, "quartaDois/status");
  Firebase.get(minhaBase, "sala/status");
  Firebase.get(minhaBase, "banheiro/status");
  Firebase.get(minhaBase, "varanda/status");
  int led = minhaBase.intData();
  int quartoUm = minhaBase.intData();
  int quartoDois = minhaBase.intData();
  int sala = minhaBase.intData();
  int banheiro = minhaBase.intData();
  int varanda = minhaBase.intData();

  atualizarStatus(lampadaQuarto,quartoUm);
  atualizarStatus(lampadaQuarto2,quartoDois);
  atualizarStatus(lampadaSala,sala);
  atualizarStatus(lampadaBanheiro,banhiro);
  atualizarStatus(lamadaVaranda,varanda);


  switch(led){

    case 0:
      digitalWrite(4,LOW);
      break;

    case 1:
      digitalWrite(4,HIGH);
      break;
    
    
    }
 
  
}
