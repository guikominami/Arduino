#include "SoftwareSerial.h"

//variáveis Sensor de Umidade
int rele = 6;
int sensor_presenca = 5;
int sensor_umidade = A0;
int retorno_sensor_umidade = 0;
int retorno_sensor_presenca = 0;

//--------------------------------------------------------------------------------
const long segundo = 1;
const long minuto = segundo * 60;
const long hora = minuto * 60;
const long meio_dia = hora * 12;
const long dia = hora * 24;

//--------------------------------------------------------------------------------
//  valores padrões de irrigação - ALTERAR
//--------------------------------------------------------------------------------
//long tempo_irrigacao_espera = dia;
long tempo_irrigacao_espera = minuto;
int tempo_irrigacao_ligado = minuto;

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
  
}

void loop() {

  //a cada segundo, o contador aumenta 1. Se for maior que o valor definido, checar o sensor de umidade
  if (contador < tempo_irrigacao_espera){
    contador ++;
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

  if (retorno_sensor_umidade < limite_molhado)
  {
    digitalWrite(rele, HIGH);
    delay(tempo_irrigacao_ligado);
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
    delay(tempo_irrigacao_ligado);
  }
  else
  {
    //Apaga o rele
    digitalWrite(rele, LOW);
  }

}