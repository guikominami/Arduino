#include "SoftwareSerial.h"

//variáveis Sensor de Umidade
int rele = 6;
int sensor_umidade = A0;
int ligado = 0;
int retorno_sensor = 0;
//-------------------------------------------------------------
//  Alterar a quantidade do irrigador ligado
//  30000 = 30 segundos
//-------------------------------------------------------------
int tempo_irrigacao = 30000;

//-------------------------------------------------------------
//  ALTERAR AQUI O VALOR DO LIMITE ENTRE O MOLHADO E O SECO
//-------------------------------------------------------------
int limite_molhado = 500;

void setup() {   

  Serial.begin(9600);
               
  // inicializa as variáveis e portas
  pinMode(sensor_umidade, INPUT);
    
  pinMode(rele, OUTPUT);
  
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
    digitalWrite(rele, LOW);
    delay(tempo_irrigacao);
    digitalWrite(rele, HIGH);    
  }
  else
  {
    digitalWrite(rele, HIGH);
  }  
}
