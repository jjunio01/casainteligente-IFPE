#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include "DHT.h"
char* usuario = "TP-LINK_247C";
char* senha = "12345678";
bool statusConexao = false;
char* host = "https://esp8266-82004-default-rtdb.firebaseio.com/";
char* token = "o5r4y9BSVdio6bLBwXy6F4NnVIFP7tUWq6kV7zQ4";

FirebaseData minhaBase;

int comodos[] = {02,04,05,12,13,14};
//              [D4,D2;D1;D6;D7;D5]
//              Quarto D4 
//              Sala D2
//              Garagem D1
//              Cozinha D6
//              Banhiiro D7
//              Rele D5

#define sensorTemperatura 15
#define DHTTYPE    DHT11 

DHT dht(sensorTemperatura, DHTTYPE);

float t = 0.0;
float U = 0.0;

void ligaArcondicionado() {
  if(analogRead(sensorTemperatura > 20)) {
    digitalWrite(14,HIGH);
  }
}

void setup() {

  Serial.begin(9600);
  dht.begin();
  for (int i = 0; i < sizeof(comodos) -1; i++) {
    pinMode(comodos[i], OUTPUT);
  }
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

  //DHT.read11(sensorTemperatura); //LÊ AS INFORMAÇÕES DO SENSOR
  Serial.print("Umidade: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(dht.readHumidity()); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO
  Serial.print("%"); //ESCREVE O TEXTO EM SEGUIDA
  Serial.print(" / Temperatura: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(dht.readTemperature(), 0); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO E REMOVE A PARTE DECIMAL
  Serial.println("*C"); //IMPRIME O TEXTO NA SERIAL
  delay(2000);

  
  Firebase.get(minhaBase, "rele/status");
  int rele = minhaBase.intData();
  Firebase.get(minhaBase, "quarto/status");
  int quarto = minhaBase.intData();
  Firebase.get(minhaBase, "sala/status");
  int sala = minhaBase.intData();
  Firebase.get(minhaBase, "garagem/status");
  int garagem = minhaBase.intData();
  Firebase.get(minhaBase, "banheiro/status");
  int banheiro = minhaBase.intData();;
  Firebase.get(minhaBase, "cozinha/status");
  int cozinha = minhaBase.intData();

  int novoStatus[] = {quarto, sala, garagem, cozinha, cozinha, rele};
      
  for (int i = 0; i < sizeof(novoStatus) -1; i++ ){
    if (novoStatus[i] == 0) {
      digitalWrite(comodos[i],LOW);
    } else {
      digitalWrite(comodos[i],HIGH);
    }
  }  
}
