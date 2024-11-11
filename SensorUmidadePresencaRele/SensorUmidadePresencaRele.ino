#include "SoftwareSerial.h"

//variáveis Sensor de Umidade
int rele = 6;
int sensor_presenca = 5;
int sensor_umidade = A0;
int ligado = 0;
int retorno_sensor_umidade = 0;
int retorno_sensor_presenca = 0;
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
  pinMode(sensor_presenca, INPUT);   
  pinMode(rele, OUTPUT);
  
}

void loop() {

  SensorUmidade();

  SensorPresenca();

  delay(1000);  
}

void SensorUmidade(){

  retorno_sensor_umidade = analogRead(sensor_umidade);
  Serial.println("Sensor de umidade:");
  Serial.println(retorno_sensor_umidade);

  if (retorno_sensor_umidade < limite_molhado)
  {
    digitalWrite(rele, HIGH);
    delay(tempo_irrigacao);
  }
  else
  {
    digitalWrite(rele, LOW);
  }  
}

void SensorPresenca(){

  retorno_sensor_presenca = digitalRead(sensor_presenca);
  
  Serial.println("Sensor de presença:");
  Serial.println(retorno_sensor_presenca);

  if (retorno_sensor_presenca == 0)
  {
    //liga o rele
    digitalWrite(rele, HIGH);
    delay(tempo_irrigacao);
  }
  else
  {
    //Apaga o rele
    digitalWrite(rele, LOW);
  }

}
