#include "SoftwareSerial.h"

//variáveis
int led = 13;
int botao = 8;
int ligado = 0;
int retorno_botao = 0;

void setup() {   

  Serial.begin(9600);
               
  // inicializa as variáveis e portas
  pinMode(botao, INPUT);
  pinMode(led, OUTPUT);         
  
}

void loop() {

  retorno_botao = digitalRead(botao);
  
  Serial.println("Botão:");
  Serial.println(retorno_botao);

  if (retorno_botao == 1)
  {
    //Acende o LED
    digitalWrite(led, HIGH);
  }
  else
  {
    //Apaga o LED
    digitalWrite(led, LOW);
  }

  delay(200);  
}
