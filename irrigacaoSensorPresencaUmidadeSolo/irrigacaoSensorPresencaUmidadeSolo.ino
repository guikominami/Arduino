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
//12h de espera
long tempo_irrigacao_espera = 43200;
int tempo_irrigacao_ligado = 60;

int contador_espera = 0;

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
  if (contador_espera < tempo_irrigacao_espera){
    contador_espera ++;

    Serial.println("contador_espera:");
    Serial.println(contador_espera);    
    
    delay(1000);
  }
  else{
    SensorUmidade();        
    contador_espera = 0;
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
    Irrigar();  
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
    Irrigar();
  }
  else
  {
    //Apaga o rele
    digitalWrite(rele, HIGH);
  }

}

void Irrigar(){

  int contador_irrigar = 0;

  //liga o rele
  digitalWrite(rele, LOW); 

  while (contador_irrigar < tempo_irrigacao_ligado){

    Serial.println("contador_irrigar:");
    Serial.println(contador_irrigar);

    delay(1000);
    contador_irrigar ++;
  }

  digitalWrite(rele, HIGH);  

}
