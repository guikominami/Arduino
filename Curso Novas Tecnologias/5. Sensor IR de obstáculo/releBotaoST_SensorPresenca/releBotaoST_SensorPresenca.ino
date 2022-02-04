#include "SoftwareSerial.h"

//variáveis
int led_vermelho = 13;
int led_amarelo = 12;
int led_verde = 11;
int botao = 8;
int sensor_presenca = 7;
int rele = 9;
int ligado = 0;
int retorno_botao = 0;
int retorno_sensor_presenca = 0;

void setup() {   

  Serial.begin(9600);
               
  // inicializa as variáveis e portas
  pinMode(botao, INPUT);
  pinMode(sensor_presenca, INPUT);
    
  pinMode(led_vermelho, OUTPUT);         
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_verde, OUTPUT);  
  pinMode(rele, OUTPUT);
  
}

void loop() {

  retorno_botao = digitalRead(botao);
  retorno_sensor_presenca = digitalRead(sensor_presenca);
  
  Serial.println("Botão:");
  Serial.println(retorno_botao);
  Serial.println("Sensor de presença:");
  Serial.println(retorno_sensor_presenca);

  if (retorno_botao == 1 && ligado == 0 || retorno_sensor_presenca == 0 && ligado == 0)
  {
    //Acende o LED
    digitalWrite(led_vermelho, HIGH);
    digitalWrite(led_amarelo, HIGH);
    digitalWrite(led_verde, HIGH);
    digitalWrite(rele, HIGH);

    ligado = 1;
  }
  else if (retorno_botao == 1 && ligado == 1 || retorno_sensor_presenca == 0 && ligado == 1)
  {
    //Apaga o LED
    digitalWrite(led_vermelho, LOW);
    digitalWrite(led_amarelo, LOW);    
    digitalWrite(led_verde, LOW);
    digitalWrite(rele, LOW);

    ligado = 0;
  }

  delay(200);  
}
