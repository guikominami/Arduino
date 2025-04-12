//------------------------------------------------
//      Áudio
//------------------------------------------------

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//Inicia a serial por software nos pinos 10 e 11
//portas mp3 substituídas 10 -> 6, 11 -> 7
SoftwareSerial mySoftwareSerial(6, 7); // RX, TX

DFRobotDFPlayerMini myDFPlayer;

//------------------------------------------------

/*
Ligações RFID:
SDA = 10
SCK = 13
MOSI = 11
MISO = 12
RST = 9
*/

#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

char st[20];

char *cartoes[] = {"A6 81 36 90", "0A A5 99 15", "57 F3 5F C9", "67 5A 6A C9", "06 18 59 90",
                   "86 FF 3A 90", "EB 07 8F DB", "3B 0F 05 DC", "0B 13 0B DC", "2B 71 07 DC",
                   "26 1A 02 90", "86 C1 41 90", "DB 2F 97 DB", "46 A1 3F 90", "9B F9 07 DC", 
                   "CB 2D 0D DC", "56 C4 87 46", "4B F4 07 DC", "76 17 03 90", "F6 F5 81 46",
                   "16 CC 01 90", "D6 CC F0 46", "DB 34 0D DC", "86 C9 FD 46", "3A 33 8E 16"};

int contador_audios = 1;
int contador_cartoes = 0;

int botao = 5;

int total_audios = 0;
int audio_desafio_inicial = 26;
int audio_desafio_final = 50;
int audio_resposta_certa = 51;
int audio_resposta_errada = 52;

int led_informativo = 3;
int led_desafio = 4;

int tipo_jogo = 1;
bool audio_tocou = false;

void setup() {
  
  Serial.begin(9600);

  delay(500);

  //RFID - Inicia SPI bus
  SPI.begin();      
  mfrc522.PCD_Init(); 

  iniciaAudioPlayer();  

  pinMode(botao, INPUT);
  pinMode(led_informativo, OUTPUT);  
  pinMode(led_desafio, OUTPUT);  

  digitalWrite(led_informativo, HIGH);
  digitalWrite(led_desafio, LOW);  
  
}
 
void loop() 
{

  int status_mp3 = 0;

  status_mp3 = myDFPlayer.readState();

  //Tipo de jogo Quiz
  if (digitalRead(botao) == HIGH && tipo_jogo == 1) {

    Serial.println("desafio");

    tipo_jogo = 2;
    contador_audios = audio_desafio_inicial;
    contador_cartoes = 0;
    audio_tocou = false;

    digitalWrite(led_informativo, LOW);
    digitalWrite(led_desafio, HIGH);    
    
  }
  //Tipo de jogo Informativo  
  else if (digitalRead(botao) == HIGH && tipo_jogo == 2) {
    
    Serial.println("informativo");
    tipo_jogo = 1;

    digitalWrite(led_informativo, HIGH);
    digitalWrite(led_desafio, LOW);

  }   

  //Serial.println("Tipo de jogo");
  //Serial.println(tipo_jogo);    

  //Informativo
  if (tipo_jogo == 1 && status_mp3 == 512){
     checaRFIDInformativo(); 
  }  
  //Quiz
  else if (tipo_jogo == 2 && status_mp3 == 512){
    if (audio_tocou == false){
      
      delay(1000);

      //tocar o áudio de acordo com o contador 
      //(adicionar 1 ao contador, pois a matriz começa com 0 e o áudio começa com 1)
      myDFPlayer.play(contador_audios);
    
      delay(1000);

      audio_tocou = true;
    }

    checaRFIDSequencial();    
  }

  delay(100);
  
}

void checaRFIDInformativo(){

    String cartao;

    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
    {
      return;
    }
    
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) 
    {
      return;
    }

    //Mostra UID na serial
    Serial.print("UID da tag :");
    String conteudo= "";
    byte letra;
    
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    {
       Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       Serial.print(mfrc522.uid.uidByte[i], HEX);
       conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
       conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    
    //Serial.println();
    conteudo.toUpperCase();

    //UID 1 - Cartão
    if (conteudo != "")
    {
        int indice = 0;
        int encontrou = 0;

        //checar se o cartão está dentro da matriz de cartões e pegar o índice associado ao áudio
        for (int indice = 0; indice < 26; indice++) {

          cartao = cartoes[indice];      

//          Serial.println("conteudo");
//          Serial.println(conteudo);
//          Serial.println("cartao");
//          Serial.println(cartao);
//          Serial.println("Tem na string");
//          Serial.println(conteudo.indexOf(cartao));
          
          //se o número estiver na matriz de cartões
          if (conteudo.indexOf(cartao) != -1){

             Serial.println("Encontrou");

             Serial.println("");
             Serial.println("Cartão na matriz");
             Serial.println(cartao);   
             Serial.println("Índice");
             Serial.println(indice + 1); 

             myDFPlayer.play(indice + 1);

             delay(1000);    
             conteudo = "";
             encontrou = 1;
             break;
          }         
        }

        if (encontrou == 0){
          
           Serial.println("Cartão não está na matriz");
           Serial.println(conteudo);
           conteudo = "";
           delay(1000);

           //RFID - Inicia SPI bus
           SPI.begin();      
           mfrc522.PCD_Init();            
           
        }         
    }
   
}

void checaRFIDSequencial(){

    String cartao_identificado;

    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
    {
      return;
    }
    
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) 
    {
      return;
    }

    //Mostra UID na serial
    Serial.print("UID da tag :");
    String conteudo= "";
    byte letra;
    
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    {
       Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       Serial.print(mfrc522.uid.uidByte[i], HEX);
       conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
       conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    
    //Serial.println();
    conteudo.toUpperCase();       

    //UID 1 - Cartão
    if (conteudo.substring(1) != "")
    {
       //Checar na matriz se o valor cartoes[contador_cartoes] é igual ao conteúdo da tag
       cartao_identificado = cartoes[contador_cartoes];

       //Serial.println("tag identificada:");
       //Serial.println(cartao_identificado);    
              
       if (conteudo.substring(1) == cartao_identificado){

          Serial.println();
          Serial.println("ACERTOU");
          Serial.println("");
          Serial.println("");

          //tocar o áudio com a resposta certa
          myDFPlayer.play(audio_resposta_certa);
          
          delay(5000);
          
          //passa para o próximo áudio
          contador_audios ++; 
          contador_cartoes ++;

          audio_tocou = false;

          //verificar o total de áudios
          if (contador_audios > audio_desafio_final){
            Serial.println("FIM DE JOGO");

            //reiniciar jogo
            contador_audios = audio_desafio_inicial;
            contador_cartoes = 0;
            audio_tocou = false;             
          }

          conteudo = "";
       }
       else{
          Serial.println();
          Serial.println("ERROU");
          Serial.println("");
          Serial.println("");

          //tocar o áudio da resposta errada
          myDFPlayer.play(audio_resposta_errada);
              
          delay(5000);

          myDFPlayer.play(contador_audios);

          delay(5000);            

          conteudo = "";
       }
          
    }
}

void iniciaAudioPlayer(){

  //Definicoes iniciais
  mySoftwareSerial.begin(9600);
  myDFPlayer.begin(mySoftwareSerial); //inicia módulo MP3, essa linha ficava dentro da Serial
  
  myDFPlayer.setTimeOut(500); //Timeout serial 500ms
  myDFPlayer.volume(30); 
  myDFPlayer.EQ(0); //Equalizacao normal

  total_audios = myDFPlayer.readFileCounts(DFPLAYER_DEVICE_SD);

  //Mostra o menu de comandos
  Serial.println();
  Serial.print("Numero de arquivos no cartao SD: ");
  Serial.println(total_audios);
    
}
