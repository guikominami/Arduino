#include "pitches.h"

//pino do buzzer na 7
#define speaker 7  

//pinos do ultrassom: trig 5, echo 6
#define trigger 5   
#define echo 6   

//botão na porta 8
int buttonPin = 8;

int distance_cm = 0;
int time = 0;
int counter = 0;

//matriz de notas musicais
int note[] = {
  NOTE_B0, NOTE_C1, NOTE_CS1, NOTE_D1, NOTE_DS1, NOTE_E1, NOTE_F1, NOTE_FS1, NOTE_G1, NOTE_GS1, 
  NOTE_A1, NOTE_AS1, NOTE_B1, NOTE_C2, NOTE_CS2, NOTE_D2, NOTE_DS2, NOTE_E2, NOTE_F2, NOTE_FS2,
  NOTE_G2, NOTE_GS2, NOTE_A2, NOTE_AS2, NOTE_B2, NOTE_C3, NOTE_CS3, NOTE_D3, NOTE_DS3, NOTE_E3,
  NOTE_F3, NOTE_FS3, NOTE_G3, NOTE_GS3, NOTE_A3, NOTE_AS3, NOTE_B3, NOTE_C4, NOTE_CS4, NOTE_D4,
  NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4, NOTE_C5, 
  NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, 
  NOTE_B5, NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, 
  NOTE_A6, NOTE_AS6, NOTE_B6, NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, 
  NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7, NOTE_C8, NOTE_CS8, NOTE_D8, NOTE_DS8
};

void setup()                    
{
  //definição do pino do botão
  pinMode(buttonPin, INPUT);
  //saída do motor, poderia ser em uma digital também.
  pinMode(A0, OUTPUT);
  
  Serial.begin(9600);

  //definições dos pinos do ultrasonido
  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, LOW);
  delayMicroseconds(10);
  pinMode(echo,INPUT);

  Serial.begin(9600);
  Serial.println("Sensor...");
}

void loop()                    
{ 
  //leitura dos dados de ultrasonido e armazena o valor em centímetros.
  int distance = readUltrasonic();

  Serial.println("distance");
  Serial.println(distance);

  //se pressionar o botão
  if (digitalRead(buttonPin) == HIGH) {
    
    //toca um som de acordo com a matriz de nota musical e a distância do ultrasonido. 
    //Ex.: Sua mão está a 10cm, a nota selecionada é note[10] da matriz de notas musicais
    //definidas no início do código. NOTE_A1
    tone(speaker, note[distance], 20);

    //encende o motor como porta digital
    digitalWrite(A0, HIGH);
  }
  else{
    //se o botão não estiver sendo pressionado, apaga o motor e o buzzer.
    noTone(speaker);
    digitalWrite(A0, LOW);
  }

  delay(100);      
}

int readUltrasonic(){

  int distance = 0;

  //envia o som do ultrassom
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  //leitura do retorno do ultrassom
  time = pulseIn(echo, HIGH);
  
  //calcula a distância
  distance = time / 29.4 / 2;

  //retorna a distância em cm
  return distance;

}
