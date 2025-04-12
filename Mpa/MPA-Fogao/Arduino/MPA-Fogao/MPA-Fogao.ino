//Som
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

int pontenciometro1 = A0;
int pontenciometro2 = A1;
int pontenciometro3 = A2;
int pontenciometro4 = A3;
int pontenciometro5 = A4;
int pontenciometro6 = A5;

int ultimaPosicaoPotenciometro1 = -1;
int ultimaPosicaoPotenciometro2 = -1;
int ultimaPosicaoPotenciometro3 = -1;
int ultimaPosicaoPotenciometro4 = -1;
int ultimaPosicaoPotenciometro5 = -1;
int ultimaPosicaoPotenciometro6 = -1;

float posicao1 = 0;

//----------------------------------------------------------------
//                 Áudio 
//----------------------------------------------------------------
//Inicia a serial por software nos pinos 10 e 11
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX

DFRobotDFPlayerMini myDFPlayer;

char buf;
int pausa = 0;
int equalizacao = 0;
//----------------------------------------------------------------

void setup() {

  //Definicoes iniciais Áudio
  mySoftwareSerial.begin(9600);
  myDFPlayer.begin(mySoftwareSerial); //inicia módulo MP3, essa linha ficava dentro da Serial
  
  myDFPlayer.setTimeOut(500); //Timeout serial 500ms
  myDFPlayer.volume(30); 
  myDFPlayer.EQ(0); //Equalizacao normal
  
}

void loop() {

  //------------------------------------------------------------
  //  múltiplos de 6
  //  se posicao == 0 desligado
  //  se posicao > 0 e posicao < 43 = audio 1
  //  se posicao > 43 e < 85 = audio 2
  //  se posicao > 85 e < 128 = audio 3
  //  se posicao > 128 e < 170 = audio 4
  //  se posicao > 170 e < 213 = audio 5
  //  se posicao > 213 = audio 6
  //  total: 255
  //------------------------------------------------------------
  //  múltiplos de 4
  //  se posicao == 0 desligado
  //  se posicao > 0 e posicao < 64 = audio 1
  //  se posicao > 64 e < 128       = audio 2
  //  se posicao > 128 e < 191      = audio 3
  //  se posicao > 191              = audio 4
  //  total: 255
  //------------------------------------------------------------  
  //    se primeiraVezPotenciometro1 = true significa que o código 
  //  executou pela primeira vez
  //    não executar o áudio se o botão estiver em alguma posição 
  //  dos controles e marcar como primeiraVezPotenciometro1 = false
  //------------------------------------------------------------
  //    se tocou = 1 significa que já tocou o áudio 1 e não tocará 
  //  novamente se o controle continuar naquela posição
  //------------------------------------------------------------

  posicao1 = map(analogRead(pontenciometro1), 0, 1023, 0, 255);;
  ultimaPosicaoPotenciometro1 = verificaPotenciometro("1", 0, ultimaPosicaoPotenciometro1);
  
  posicao1 = map(analogRead(pontenciometro2), 0, 1023, 0, 255);;
  ultimaPosicaoPotenciometro2 = verificaPotenciometro("2", 4, ultimaPosicaoPotenciometro2);

  posicao1 = map(analogRead(pontenciometro3), 0, 1023, 0, 255);;
  ultimaPosicaoPotenciometro3 = verificaPotenciometro("3", 8, ultimaPosicaoPotenciometro3);

  posicao1 = map(analogRead(pontenciometro4), 0, 1023, 0, 255);;
  ultimaPosicaoPotenciometro4 = verificaPotenciometro("4", 12, ultimaPosicaoPotenciometro4);  

  posicao1 = map(analogRead(pontenciometro5), 0, 1023, 0, 255);;
  ultimaPosicaoPotenciometro5 = verificaPotenciometro("5", 16, ultimaPosicaoPotenciometro5);  

  posicao1 = map(analogRead(pontenciometro6), 0, 1023, 0, 255);;
  ultimaPosicaoPotenciometro6 = verificaPotenciometro("6", 20, ultimaPosicaoPotenciometro6);  
    
  delay (3000);
  
//  Serial.println(posicao3);
//  Serial.println(posicao4);
}

//------------------------------------------------------------------------------------
// parâmetro audio será multiplicado para executar os áudios em múltiplos de 6
//------------------------------------------------------------------------------------
//parametro audio = 0
//1 - Toca do 1 ao 4
//2 - Toca do 5 ao 8
//3 - Toca do 9 ao 12
//4 - Toca do 13 ao 16
//5 - Toca do 17 ao 20
//6 - Toca do 21 ao 24

int verificaPotenciometro(String potenciometro, int audio, int ultimaPosicaoPotenciometro){

  if (posicao1 == 0){
    Serial.println("desligado " + potenciometro);
    ultimaPosicaoPotenciometro = 0;
  }
  
  else if (posicao1 > 0 && posicao1 < 64 && ultimaPosicaoPotenciometro != 1){

      if (ultimaPosicaoPotenciometro > -1){
        Serial.println(audio + 1);  
        myDFPlayer.play(audio + 1);
        delay(1000);    
      }

      ultimaPosicaoPotenciometro = 1;
  }

  else if (posicao1 > 64 && posicao1 < 128 && ultimaPosicaoPotenciometro != 2){

      if (ultimaPosicaoPotenciometro > -1){
        Serial.println(audio + 2); 
        myDFPlayer.play(audio + 2);
        delay(1000);    
      }

      ultimaPosicaoPotenciometro = 2;    
  }

  else if (posicao1 > 128 && posicao1 < 191 && ultimaPosicaoPotenciometro != 3){

      if (ultimaPosicaoPotenciometro > -1){
        Serial.println(audio + 3);  
        myDFPlayer.play(audio + 3);
        delay(1000);            
      }

      ultimaPosicaoPotenciometro = 3;              
  }

  else if (posicao1 > 191 && ultimaPosicaoPotenciometro != 4){

      if (ultimaPosicaoPotenciometro > -1){
        Serial.println(audio + 4);  
        myDFPlayer.play(audio + 4);
        delay(1000);    
      }

      ultimaPosicaoPotenciometro = 4;
  }

  return ultimaPosicaoPotenciometro;
}
