#include "SoftwareSerial.h"

//variáveis
int ledVermelho = 13;
int ledAmarelo = 12;
int ledVerde = 11;
int botao = 8;

void setup() {   

  Serial.begin(9600);
               
  // inicializa as variáveis e portas
  pinMode(ledVermelho, OUTPUT);         
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);  
  pinMode(botao, INPUT);
  
}

void loop() {

  Serial.println(digitalRead(botao));

  if (digitalRead(botao) == HIGH)
  {
    //Acende o LED
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVerde, HIGH);
  }
  else
  {
    //Apaga o LED
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledAmarelo, LOW);    
    digitalWrite(ledVerde, LOW);   
  }
  
}
