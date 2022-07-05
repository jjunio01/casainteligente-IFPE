#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include "DHT.h"
char* usuario = "S20";
char* senha = "12345678";
bool statusConexao = false;
char* host = "MEU HOST";
char* token = "MEU TOKEN";

FirebaseData minhaBase;

int comodos[] = {02,04,05,12,13,14};
//              [D4,D2;D1;D6;D7;D5]
//              Quarto D4 
//              Sala D2
//              Garagem D1
//              Cozinha D6
//              Banheiro D7
//              Rele D5

#define sensorDHT11 0
#define DHTTYPE DHT11 

DHT dht(sensorDHT11, DHTTYPE);

void ligaVentilador() {
  if(analogRead(sensorDHT11 > 20)) {
    digitalWrite(14,HIGH);
  }
}

void setup() {

  Serial.begin(9600);
  dht.begin();
  for (int i = 0; i < 6; i++) {
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

 // DHT.read11(sensorDHT11); //LÊ AS INFORMAÇÕES DO SENSOR
  Serial.print("Umidade: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(dht.readHumidity()); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO
  Serial.print("%"); //ESCREVE O TEXTO EM SEGUIDA
  Serial.print(" / Temperatura: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(dht.readTemperature(), 0); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO E REMOVE A PARTE DECIMAL
  Serial.println("*C"); //IMPRIME O TEXTO NA SERIAL

  Firebase.setFloat(minhaBase, "temperatura/valor", dht.readTemperature());
  Firebase.setFloat(minhaBase, "umidade/valor", dht.readHumidity());
  
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

  int novoStatus[] = {quarto, sala, garagem, cozinha, banheiro, rele};
  for (int i = 0; i < 6; i++ ){   
    if (novoStatus[i] == 0) {
      digitalWrite(comodos[i],LOW);
    } else {
      digitalWrite(comodos[i],HIGH);
    }
  }  
}
