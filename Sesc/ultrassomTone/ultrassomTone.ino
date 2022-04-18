#include "pitches.h"

//ULTRASSOM
//ligar VCC no 5V
//ligar GND no GND
//ligar TRIG no 8
//ligar ECHO no 9

int pinBuzzer = 12;
int thisNote = 0;

int trigger = 8;
int echo = 9;
float tempo;
float distancia_cm;

int melody[] = {
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

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {

  // configura pino GATILHO como saída
  pinMode(trigger,OUTPUT);
  // deixa pino em LOW
  digitalWrite(trigger,LOW);
  delayMicroseconds(10);
 
  // configura pino ECHO como entrada
  pinMode(echo,INPUT);

  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
    
}

void loop() {

  // disparar pulso ultrassônico
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  // medir tempo de ida e volta do pulso ultrassônico
  tempo = pulseIn(echo, HIGH);
  
  // calcular as distâncias em centímetros e polegadas
  distancia_cm = tempo / 29.4 / 2;
  
  Serial.println(distancia_cm);  

  tone(pinBuzzer, melody[int(distancia_cm)]);

  delay(100);
  
  // stop the tone playing:
  noTone(pinBuzzer);
  
}
