#include "SoftwareSerial.h"

//variáveis Sensor de Umidade
int led_vermelho = 13;
int led_verde = 12;
int sensor_umidade = A0;
int ligado = 0;
int retorno_sensor = 0;

//ALTERAR AQUI O VALOR DO LIMITE ENTRE O MOLHADO E O SECO
int limite_molhado = 500;

void setup() {   

  Serial.begin(9600);
               
  // inicializa as variáveis e portas
  pinMode(sensor_umidade, INPUT);
    
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_verde, OUTPUT);
  
}

void loop() {

  SensorUmidade();

  delay(1000);  
}

void SensorUmidade(){

  retorno_sensor = analogRead(sensor_umidade);
  Serial.println("Sensor de umidade:");
  Serial.println(retorno_sensor);

  if (retorno_sensor < limite_molhado)
  {
     LigarLedVermelho();
  }
  else
  {
     LigarLedVerde();
  }  
}

void LigarLedVermelho(){

    digitalWrite(led_vermelho, HIGH);
    digitalWrite(led_verde, LOW);
}

void LigarLedVerde(){

    digitalWrite(led_vermelho, LOW);
    digitalWrite(led_verde, HIGH);
}
