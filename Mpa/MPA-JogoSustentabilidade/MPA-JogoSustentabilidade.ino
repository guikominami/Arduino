#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//---------------------------------------------------------------------------------
//      Áudio
//---------------------------------------------------------------------------------

//Inicia a serial por software nos pinos 10 e 11
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX

DFRobotDFPlayerMini myDFPlayer;

char buf;
int pausa = 0;
int equalizacao = 0;

int resultado = 1;

//---------------------------------------------------------------------------------
//      ULTRASSOM
//---------------------------------------------------------------------------------
//ligar VCC no 5V
//ligar GND no GND
//ligar TRIG no 5
//ligar ECHO no 4

int gatilho = 5; 
int echo = 4; 

float tempo; // para armazenar o tempo de ida e volta do sinal em microsegundos
float distancia_cm; // para armazenar a distância em centímetros

//---------------------------------------------------------------------------------
  
// setup (executado apenas uma vez)
void setup() {

  //-------------------------------------------------------
  //  define Audio
  //-------------------------------------------------------
  mySoftwareSerial.begin(9600);
  myDFPlayer.begin(mySoftwareSerial); //inicia módulo MP3, essa linha ficava dentro da Serial
  
  myDFPlayer.setTimeOut(500); //Timeout serial 500ms
  myDFPlayer.volume(30); 
  myDFPlayer.EQ(0); //Equalizacao normal  
  
  //-------------------------------------------------------
  //  define ultrassom
  //-------------------------------------------------------  
  // configura pino GATILHO como saída
  pinMode(gatilho,OUTPUT);
  
  // deixa pino em LOW
  digitalWrite(gatilho,LOW);
  delayMicroseconds(10);
 
  // configura pino ECHO como entrada
  pinMode(echo,INPUT);

  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
  
}
 
// laço principal (executado indefinidamente)
void loop() {  

  medeDistancia();

  //SE DISTÂNCIA FOR MENOR QUE 10 CM
  if (distancia_cm < 10)
  {
    myDFPlayer.play(1);    

//    if (resultado == 3){
//      resultado = 1;
//    }
//    else{
//      resultado = resultado + 1;          
//    }    

    while (distancia_cm < 50){
      delay(1000);
      medeDistancia();      
    }

    delay(3000);
  }
  
  // aguardar um pouquinho antes de começar tudo de novo
  delayMicroseconds(100);
}

void medeDistancia(){
  
  // disparar pulso ultrassônico
  digitalWrite(gatilho, HIGH);
  delayMicroseconds(10);
  digitalWrite(gatilho, LOW);
  
  // medir tempo de ida e volta do pulso ultrassônico
  tempo = pulseIn(echo, HIGH);
  
  // calcular as distâncias em centímetros e polegadas
  distancia_cm = tempo / 29.4 / 2;

  //mostrar o valor no terminal
  Serial.println(distancia_cm);
  
}
