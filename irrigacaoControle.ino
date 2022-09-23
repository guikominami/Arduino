#include <IRremote.h>
#include "Arduino.h"
#include "SoftwareSerial.h"

int controle_remoto = 8;
int botao = 4;
int rele = 6;

//int tipo_sistema = 0;
//int tipo_sistema_antigo = 0;

int contador = 0;

bool timer = false;
int contadorIrrigacaoTimer = 10; //10 segundos

int ligado = 0;
    
void setup() 
{
  Serial.begin(9600);

  IrReceiver.begin(controle_remoto);    
    
  pinMode(botao, INPUT);
  pinMode(rele, OUTPUT);   

  DesligarIrrigacao();
}

void loop() 
{
  
  VerificarBotao();

  VerificarControleRemoto();

  VerificarTimer();

  delay(100);
  
}

void VerificarBotao(){

  int retorno_botao = digitalRead(botao);
  
  if (retorno_botao == 1 && ligado == 0)
  {
     LigarIrrigacao();
     ligado = 1;
  }
  else if (retorno_botao == 1 && ligado == 1)
  {
    DesligarIrrigacao();
    ligado = 0;
  }
  
  delay(200); 
  
}

void VerificarControleRemoto(){

   if(IrReceiver.decode()){

   Serial.println(IrReceiver.decodedIRData.command);

   switch(IrReceiver.decodedIRData.command){

       //botão 1
       case 22:  
          Serial.println("Botão 1 - Ligar irrigação");

          timer = false;
          contador = 0;

          LigarIrrigacao();
           
          break;

       //botão 2
       case 25:  
           Serial.println("Botão 2 - Desligar irrigação");

           timer = false;
           contador = 0;

           DesligarIrrigacao();
           
           break;

       //botão 3
       case 13:
           Serial.println("Botão 3 - Timer");

           timer = true;
           contador = 0;
           
           break;   
           
       default:   
           Serial.println("Ooops, wrong key!");
           IrReceiver.begin(controle_remoto);

    }
    delay(100);
    IrReceiver.resume();
  }  
  
}

void VerificarTimer(){

  if (timer == true){
  
   Serial.println("contador: ");
   Serial.println(contador); 
  
   if (contador == 0){
  
     LigarIrrigacao();
     
   }
   else if (contador > contadorIrrigacaoTimer){
    
     DesligarIrrigacao();
  
     contador = 0;
     timer = false;
     
   }
  
   delay(1000);
  
   contador ++;
  }
  
}

void LigarIrrigacao(){

  digitalWrite(rele, LOW);
}

void DesligarIrrigacao(){
  
  digitalWrite(rele, HIGH);
}
