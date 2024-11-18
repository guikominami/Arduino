#include "SoftwareSerial.h"

//variáveis Sensor de Umidade
int rele = 6;
int sensor_presenca = 5;
int sensor_umidade = A0;
int retorno_sensor_umidade = 0;
int retorno_sensor_presenca = 0;

//--------------------------------------------------------------------------------
//  valores padrões de irrigação - ALTERAR
//--------------------------------------------------------------------------------
//long tempo_irrigacao_espera = dia;
long tempo_irrigacao_espera = 60;
int tempo_irrigacao_ligado = 10000;

int contador = 0;

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

  //Apaga o rele
  digitalWrite(rele, HIGH);  
  
}

void loop() {

  //a cada segundo, o contador aumenta 1. Se for maior que o valor definido, checar o sensor de umidade
  if (contador < tempo_irrigacao_espera){
    contador ++;

    Serial.println("contador:");
    Serial.println(contador);    
    
    delay(1000);
  }
  else{
    SensorUmidade();        
    contador = 0;
  }

  SensorPresenca();  

  delay(500);  
}

void SensorUmidade(){

  retorno_sensor_umidade = analogRead(sensor_umidade);
  Serial.println("Sensor de umidade:");
  Serial.println(retorno_sensor_umidade);

  delay(5000);

  if (retorno_sensor_umidade < limite_molhado)
  {
    digitalWrite(rele, LOW);
    delay(tempo_irrigacao_ligado);
    digitalWrite(rele, HIGH);    
  }
  else
  {
    digitalWrite(rele, HIGH);
  }  
}

void SensorPresenca(){

  retorno_sensor_presenca = digitalRead(sensor_presenca);
  
  Serial.println("Sensor de presença:");
  Serial.println(retorno_sensor_presenca);

  if (retorno_sensor_presenca == 0)
  {
    //liga o rele
    digitalWrite(rele, LOW);
    delay(tempo_irrigacao_ligado);
    digitalWrite(rele, HIGH);    
  }
  else
  {
    //Apaga o rele
    digitalWrite(rele, HIGH);
  }

}