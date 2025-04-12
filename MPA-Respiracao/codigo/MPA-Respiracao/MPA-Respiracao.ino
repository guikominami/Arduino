//------------------------------------------------
//      Áudio
//------------------------------------------------

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//Inicia a serial por software nos pinos 10 e 11
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX

DFRobotDFPlayerMini myDFPlayer;

//------------------------------------------------

#include <FastLED.h>

// How many leds in your strip?
#define numero_leds_pequeno 6
#define numero_leds_medio 18
#define numero_leds_grande 32

#define DATA_PIN1 9
#define DATA_PIN2 8
#define DATA_PIN3 4 //Na nano, eu inverti o DATAPIN3 e DATAPIN4
#define DATA_PIN4 5
#define DATA_PIN5 6

#define pino_led_calma 13
#define pino_led_normal 12
#define pino_led_ofegante 2

// Define the array of leds
CRGB leds_nariz[numero_leds_pequeno];
CRGB leds_boca[numero_leds_pequeno];
CRGB leds_traqueia[numero_leds_medio];
CRGB leds_pulmao1[numero_leds_grande];
CRGB leds_pulmao2[numero_leds_grande];

//com os pinos soldados pra baixo, esquerda 5V, direita GND, meio sinal
int porta_potenciometro = A0;  

void setup() { 

  Serial.begin(9600);

  FastLED.addLeds<NEOPIXEL, DATA_PIN1>(leds_nariz, numero_leds_pequeno);
  FastLED.addLeds<NEOPIXEL, DATA_PIN2>(leds_boca, numero_leds_pequeno);
  FastLED.addLeds<NEOPIXEL, DATA_PIN3>(leds_traqueia, numero_leds_medio);
  FastLED.addLeds<NEOPIXEL, DATA_PIN4>(leds_pulmao1, numero_leds_grande);    
  FastLED.addLeds<NEOPIXEL, DATA_PIN5>(leds_pulmao2, numero_leds_grande);  

  pinMode(pino_led_calma, OUTPUT);  
  pinMode(pino_led_normal, OUTPUT);  
  pinMode(pino_led_ofegante, OUTPUT);  

  iniciaAudioPlayer();    
  
}

void loop() { 

  int retorno_potenciometro = map(analogRead(porta_potenciometro), 0, 1023, 0, 255);

  Serial.println("retorno_potenciometro");  
  Serial.println(retorno_potenciometro);  

  //250/3 - 80
  if (retorno_potenciometro < 80){

    Serial.println("ofegante");

    digitalWrite(pino_led_ofegante, HIGH);
    digitalWrite(pino_led_calma, LOW);
    digitalWrite(pino_led_normal, LOW);

    //Respiração ofegante, inspira boca, solta boca
    iniciarRotinaRespiracaoRapida(15);
     
  }
  else if (retorno_potenciometro > 80 && retorno_potenciometro < 160){

    Serial.println("normal");

    digitalWrite(pino_led_normal, HIGH);
    digitalWrite(pino_led_calma, LOW);
    digitalWrite(pino_led_ofegante, LOW);    

    //Respiração normal, inspira nariz, solta boca
    iniciarRotinaRespiracaoNormal(60);
     
  }
  else if (retorno_potenciometro > 160){

    Serial.println("calma");

    digitalWrite(pino_led_calma, HIGH);
    digitalWrite(pino_led_normal, LOW);
    digitalWrite(pino_led_ofegante, LOW);

    //Respiração calma, inspira nariz 4 segundos, segura 7 segundos, solta boca 8 segundos
    iniciarRotinaRespiracaoCalma(120);
    
  }

}  

void iniciarRotinaRespiracaoNormal(int tempo_respiracao){

  //tocar áudio
  myDFPlayer.play(2);  

  //inspiração nasal
  iniciarInspiracao(numero_leds_pequeno, leds_nariz, tempo_respiracao, 1, 100, 100);
  
  //inspiração traqueal
  iniciarInspiracao(numero_leds_medio, leds_traqueia, tempo_respiracao, 1, 100, 100);  

  //apagar leds
  iniciarInspiracao(numero_leds_pequeno, leds_nariz, tempo_respiracao, 2, 100, 0);  
  iniciarInspiracao(numero_leds_medio, leds_traqueia, tempo_respiracao, 2, 100, 0);  
  
  //pulmao infla
  iniciarPulmaoBrilho(1, 0, numero_leds_grande, tempo_respiracao);
  
  //aguarda
  delay(tempo_respiracao);    
  
  //pulmao relaxa
  iniciarPulmaoBrilho(2, 100, numero_leds_grande, tempo_respiracao);  

  //expiração traqueal
  iniciarExpiracao(numero_leds_medio, leds_traqueia, tempo_respiracao, 1, 100, 100);

  //expiração nasal
  iniciarExpiracao(numero_leds_pequeno, leds_nariz, tempo_respiracao, 1, 100, 100); 

  iniciarExpiracao(numero_leds_medio, leds_traqueia, tempo_respiracao, 2, 100, 0);  
  iniciarExpiracao(numero_leds_pequeno, leds_nariz, tempo_respiracao, 2, 100, 0); 

  //aguarda
  delay(3000);  
    
}

void iniciarRotinaRespiracaoCalmaAnterior(int tempo_respiracao){

  //tocar áudio
  myDFPlayer.play(3);    

  //inspiração nasal
  iniciarInspiracao(numero_leds_pequeno, leds_nariz, tempo_respiracao, 1, 100, 100);
  
  //inspiração traqueal
  iniciarInspiracao(numero_leds_medio, leds_traqueia, tempo_respiracao, 1, 100, 100);  
  
  //aguarda
  delay(tempo_respiracao);  
  
  //pulmao infla
  iniciarPulmaoBrilho(1, 0, numero_leds_grande, tempo_respiracao);
  
  //aguarda
  delay(tempo_respiracao);

  //apagar os leds nasal e traqueal
  iniciarInspiracao(numero_leds_pequeno, leds_nariz, tempo_respiracao, 2, 100, 0);  
  iniciarInspiracao(numero_leds_medio, leds_traqueia, tempo_respiracao, 2, 100, 0);    
  
  //pulmao relaxa
  iniciarPulmaoBrilho(2, 100, numero_leds_grande, tempo_respiracao);  
  
  //aguarda
  delay(tempo_respiracao);  

  //expiração traqueal
  iniciarExpiracao(numero_leds_medio, leds_traqueia, tempo_respiracao, 1, 100, 100);

  //expiração bucal
  iniciarExpiracao(numero_leds_pequeno, leds_boca, tempo_respiracao, 1, 100, 100); 

  //apagar
  iniciarExpiracao(numero_leds_medio, leds_traqueia, tempo_respiracao, 2, 100, 0);
  iniciarExpiracao(numero_leds_pequeno, leds_boca, tempo_respiracao, 2, 100, 0); 

  //aguarda
  delay(3000);  
    
}

void iniciarRotinaRespiracaoRapida(int tempo_respiracao){

  //tocar áudio
  myDFPlayer.play(1);    

  //inspiração bucal
  iniciarInspiracao(numero_leds_pequeno, leds_boca, tempo_respiracao, 1, 100, 100);
  iniciarInspiracao(numero_leds_pequeno, leds_boca, tempo_respiracao, 2, 100, 0);  
    
  //inspiração traqueal
  iniciarInspiracao(numero_leds_medio, leds_traqueia, tempo_respiracao/2, 1, 100, 100);  
  iniciarInspiracao(numero_leds_medio, leds_traqueia, tempo_respiracao/2, 2, 100, 0);    
  
  //pulmao infla
  iniciarPulmaoBrilho(1, 0, numero_leds_grande/2, tempo_respiracao);
  
  //pulmao relaxa
  iniciarPulmaoBrilho(2, 100, numero_leds_grande/2, tempo_respiracao);  

  //expiração traqueal
  iniciarExpiracao(numero_leds_medio, leds_traqueia, tempo_respiracao, 1, 100, 100);
  iniciarExpiracao(numero_leds_medio, leds_traqueia, tempo_respiracao, 2, 100, 0);    

  //expiração bucal
  iniciarExpiracao(numero_leds_pequeno, leds_boca, tempo_respiracao, 1, 100, 100);
  iniciarExpiracao(numero_leds_pequeno, leds_boca, tempo_respiracao, 2, 100, 0);    

  //delay(tempo_respiracao);
    
}

void iniciarRotinaRespiracaoCalma(int tempo_respiracao){

  //tocar áudio
  myDFPlayer.play(3);    

  //inspiração nasal
  iniciarInspiracao(numero_leds_pequeno, leds_nariz, tempo_respiracao/2, 1, 100, 100);
  
  //inspiração traqueal
  iniciarInspiracao(numero_leds_medio, leds_traqueia, tempo_respiracao/2, 1, 100, 100);  
  
  //aguarda
  //delay(tempo_respiracao/2);  
  
  //pulmao infla
  iniciarInspiracao(numero_leds_grande, leds_traqueia, tempo_respiracao, 3, 100, 100);  

  //aguarda
  delay(tempo_respiracao);  

  //apagar os leds nasal e traqueal
  iniciarInspiracao(numero_leds_pequeno, leds_nariz, tempo_respiracao/2, 2, 100, 100);  
  iniciarInspiracao(numero_leds_medio, leds_traqueia, tempo_respiracao/2, 2, 100, 100);   

  delay (1000);  

  //mudar cor do pulmão
  iniciarInspiracao(numero_leds_grande, leds_pulmao1, tempo_respiracao, 5, 100, 100);  

  delay (2000);
  
  //pulmao relaxa
  iniciarExpiracao(numero_leds_grande, leds_traqueia, tempo_respiracao, 4, 100, 100);   
  
  //aguarda
  delay(tempo_respiracao);  

  //apagar
  iniciarExpiracao(numero_leds_medio, leds_traqueia, tempo_respiracao/2, 2, 100, 0);
  iniciarExpiracao(numero_leds_pequeno, leds_boca, tempo_respiracao/2, 2, 100, 0); 

  //aguarda
  delay(3000);  
    
}

void mudarCoresPulmao(){

  int contador = 0;

  while (contador < 10){

    fill_solid(leds_pulmao1, numero_leds_grande, CRGB::Green);
    fill_solid(leds_pulmao2, numero_leds_grande, CRGB::Green);
    FastLED.show();
    delay(50);
  
    fill_solid(leds_pulmao1, numero_leds_grande, CRGB::Purple);
    fill_solid(leds_pulmao2, numero_leds_grande, CRGB::Purple);
    FastLED.show();
    delay(50);
  
    fill_solid(leds_pulmao1, numero_leds_grande, CRGB::Yellow);
    fill_solid(leds_pulmao2, numero_leds_grande, CRGB::Yellow);
    FastLED.show();
    delay(50);
  
    fill_solid(leds_pulmao1, numero_leds_grande, CRGB::Orange);
    fill_solid(leds_pulmao2, numero_leds_grande, CRGB::Orange);
    FastLED.show();
    delay(50); 
  
    fill_solid(leds_pulmao1, numero_leds_grande, CRGB::Red);
    fill_solid(leds_pulmao2, numero_leds_grande, CRGB::Red);
    FastLED.show();
    delay(50);      

    contador ++;
    
  }   
  
}

void iniciarInspiracao(int NUM_LEDS, CRGB leds[], int tempo, int tipo, int brilho_entrada, int brilho_saida){

  int contador = 0;

  FastLED.setBrightness(brilho_entrada);  

  Serial.println("inspiração");

  while (contador < NUM_LEDS) {  

    if (tipo == 1){
       leds[contador] = CRGB::Blue;      
    }
    else if (tipo == 3){
       leds_pulmao1[contador] = CRGB::Blue;
       leds_pulmao2[contador] = CRGB::Blue;
    }
    else if (tipo == 4){
       leds_pulmao1[contador] = CRGB::Black;
       leds_pulmao2[contador] = CRGB::Black;
    }
    else if (tipo == 5){
       leds_pulmao1[contador] = CRGB::Green;
       leds_pulmao2[contador] = CRGB::Green;
    }  
    else{
       leds[contador] = CRGB::Black;
    }
    
    delay(tempo);
    FastLED.show(); 
    contador ++;
    
  }

  FastLED.setBrightness(brilho_saida);   
  
}

void iniciarExpiracao(int NUM_LEDS, CRGB leds[], int tempo, int tipo, int brilho_entrada, int brilho_saida){

  int contador = NUM_LEDS;
  int contador_traqueia = numero_leds_medio;
  int contador_boca = numero_leds_pequeno;

  FastLED.setBrightness(brilho_entrada);

  Serial.println("expiração");

  while (contador >= 0) {

    if (tipo == 1){
       leds[contador] = CRGB::Red;
    }
    else if (tipo == 3){
       leds_pulmao1[contador] = CRGB::Red;
       leds_pulmao2[contador] = CRGB::Red;
    }
    else if (tipo == 4){
       leds_pulmao1[contador] = CRGB::Black;
       leds_pulmao2[contador] = CRGB::Black;

       if (contador_traqueia > 0){
         //acender a traquéia e boca assim que esvaziar o pulmão
         leds_traqueia[contador_traqueia] = CRGB::Red;
         contador_traqueia --;
       }

       if (contador_traqueia <= 0 && contador_boca >= 0){
         leds_boca[contador_boca] = CRGB::Red;     
         contador_boca --;    
       }       
    }        
    else{
       leds[contador] = CRGB::Black;
    }
    
    delay(tempo);
    FastLED.show();    
    contador--;
    
  }

  FastLED.setBrightness(brilho_saida);

}

void iniciarPulmaoBrilho(int tipo, int brilho, int num_leds, int tempo){

  bool fim = false;

  do{

    FastLED.setBrightness(brilho);
  
    for ( byte i = 0; i < num_leds; i++ ) {
      
      leds_pulmao1[i] = CRGB::Blue;
      leds_pulmao2[i] = CRGB::Blue;
  
    }
    FastLED.show();     

    if (tipo == 1 && brilho < 100){
      brilho = brilho + 10;       
    }
    else if (tipo == 2 && brilho > 0){
      brilho = brilho - 10;          
    }
    else if (tipo == 1 && brilho == 100 || tipo == 2 && brilho == 0){
      fim = true;
    }

    delay (tempo);    
    
  }while (fim == false);

  if (tipo == 2){

    for ( byte i = 0; i < num_leds; i++ ) {
      
      leds_pulmao1[i] = CRGB::Black;
      leds_pulmao2[i] = CRGB::Black;
      FastLED.show();      
       
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

  //Mostra o menu de comandos
  Serial.println();
  Serial.print("Numero de arquivos no cartao SD: ");
  Serial.println(myDFPlayer.readFileCounts(DFPLAYER_DEVICE_SD));
    
}
