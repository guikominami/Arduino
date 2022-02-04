#include "SoftwareSerial.h"

//variáveis
int led_vermelho = 13;
int led_amarelo = 12;
int led_verde = 11;
int botao = 8;
int rele = 9;
int ligado = 0;
int retorno_botao = 0;

void setup() {   

  Serial.begin(9600);
               
  // inicializa as variáveis e portas
  pinMode(botao, INPUT);
    
  pinMode(led_vermelho, OUTPUT);         
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_verde, OUTPUT);  
  pinMode(rele, OUTPUT);
  
}

void loop() {

  retorno_botao = digitalRead(botao);
  
  Serial.println("Botão:");
  Serial.println(retorno_botao);

  if (retorno_botao == 1)
  {
    //Acende o LED
    digitalWrite(led_vermelho, HIGH);
    digitalWrite(led_amarelo, HIGH);
    digitalWrite(led_verde, HIGH);
    digitalWrite(rele, HIGH);
  }
  else
  {
    //Apaga o LED
    digitalWrite(led_vermelho, LOW);
    digitalWrite(led_amarelo, LOW);    
    digitalWrite(led_verde, LOW);
    digitalWrite(rele, LOW);
  }

  delay(200);  
}
