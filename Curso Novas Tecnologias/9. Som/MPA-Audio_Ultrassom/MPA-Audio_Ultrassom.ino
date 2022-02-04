#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
      
//Define o pino do Arduino a ser utilizado com o pino Trigger do sensor  
#define gatilho 3
//Define o pino do Arduino a ser utilizado com o pino Echo do sensor  
#define echo 4

int distancia_cm = 0;
int distancia_in = 0;
int tempo = 0;
int contador = 0;

int botao = 8;

//---------------------------------------------------------------------------------
//      Áudio
//---------------------------------------------------------------------------------

//Inicia a serial por software nos pinos 10 e 11
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX

DFRobotDFPlayerMini myDFPlayer;

char buf;
int pausa = 0;
int equalizacao = 0;

int totalMusicasCartao = 0;
int distanciaMaxima = 25;
int intervaloDistancia = 0;
int musicaSelecionada;
int musicaTocada;

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

  //totalMusicasCartao = myDFPlayer.readFileCounts(DFPLAYER_DEVICE_SD);  
  totalMusicasCartao = myDFPlayer.readFileCounts();

  if (totalMusicasCartao == -1){
    totalMusicasCartao = 40;
  }

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

  Serial.print("Numero de arquivos no cartao SD: ");
  Serial.println(totalMusicasCartao);

  pinMode(botao, INPUT);
}
 
// laço principal (executado indefinidamente)
void loop() {    

  if (digitalRead(botao) == HIGH) {
    Serial.println("botao");
    
    myDFPlayer.next();

    delay(1000);
  }  

  // disparar pulso ultrassônico
  digitalWrite(gatilho, HIGH);
  delayMicroseconds(10);
  digitalWrite(gatilho, LOW);
  
  // medir tempo de ida e volta do pulso ultrassônico
  tempo = pulseIn(echo, HIGH);
  
  // calcular as distâncias em centímetros
  distancia_cm = tempo / 29.4 / 2;

  Serial.println("distancia_cm:");
  Serial.println(distancia_cm);

  //máximo sensor = 100cm
  //músicas no meu cartão = 20
  //a cada 7cm toca uma música

  intervaloDistancia = distanciaMaxima/totalMusicasCartao;

  Serial.println("intervaloDistancia:");
  Serial.println(intervaloDistancia);  

  if (distancia_cm > 0 && distancia_cm < distanciaMaxima)
  {  
    musicaSelecionada = distancia_cm / intervaloDistancia;

    Serial.println("música Selecionada:");
    Serial.println(musicaSelecionada);
    
    //musicaTocada = musicaSelecionada.toInt();
    myDFPlayer.play(musicaSelecionada);
    delay(1000);
  }

  // aguardar um pouquinho antes de começar tudo de novo
  //delayMicroseconds(1500);
  delay(1000);
}
