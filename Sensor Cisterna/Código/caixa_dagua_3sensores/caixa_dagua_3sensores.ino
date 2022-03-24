#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// -------------------- Display ----------------------------------------
// Inicializa o display no endereco 0x27
//SCL: A5
//SDA: A4
LiquidCrystal_I2C lcd(0x27,16,2);
// ---------------------------------------------------------------------

int porta_boia_fundo = 8;
int porta_boia_meio = 9;
int porta_boia_topo = 10;

int retorno_boia_fundo = 0;
int retorno_boia_meio = 0;
int retorno_boia_topo = 0;

int situacao_anterior;

int situacao_3;
int situacao_2;
int situacao_1;

// A função setup é executada uma vez só
void setup() {

  pinMode(porta_boia_fundo, INPUT);
  pinMode(porta_boia_meio, INPUT);
  pinMode(porta_boia_topo, INPUT);

  Serial.begin(9600);

  lcd.init();
}

// A função loop fica sendo executada de maneira contínua
void loop() {

  retorno_boia_fundo = digitalRead(porta_boia_fundo);
  retorno_boia_meio = digitalRead(porta_boia_meio);
  retorno_boia_topo = digitalRead(porta_boia_topo);

//  Serial.println("Fundo");
//  Serial.println(retorno_boia_fundo);
//  Serial.println("Meio");
//  Serial.println(retorno_boia_meio);
//  Serial.println("Topo");  
//  Serial.println(retorno_boia_topo);

  if (retorno_boia_fundo == HIGH && retorno_boia_meio == LOW && retorno_boia_topo == LOW){
    
    Serial.println("1/3 cheio");
    mostraDadosLCD(2); 
    
  }
  else if (retorno_boia_fundo == HIGH && retorno_boia_meio == HIGH && retorno_boia_topo == LOW){  
  
    Serial.println("2/3 cheio");
    mostraDadosLCD(3);
    
  }
  else if (retorno_boia_fundo == HIGH && retorno_boia_meio == HIGH && retorno_boia_topo == HIGH){  
  
    Serial.println("cheio");
    mostraDadosLCD(4);
    
  }
  else if (retorno_boia_fundo == LOW && retorno_boia_meio == LOW && retorno_boia_topo == LOW){
    
    Serial.println("vazio");
    mostraDadosLCD(1); 
    
  }
  else{
    Serial.println("sensor desconectado");
    mostraDadosLCD(5);
  }
  
  delay(3000);
}

void mostraDadosLCD(int situacao){

  int quantidade_caracteres;
  int situacao_porcentagem = 0;

  if (situacao_anterior != situacao){

    Serial.println(situacao);

    //situacao = 4 (100%)
    //situacao = 3 (75%)
    //situacao = 2 (25%)
    //situacao = 1 (0%)
    //situacao = 5 (sensor desconectado)
    
    if (situacao == 4) {
      quantidade_caracteres = 16;
      situacao_porcentagem = 100;
    }
    else if (situacao == 3) {
      quantidade_caracteres = 12;
      situacao_porcentagem = 75;
    }  
    else if (situacao == 2) {
      quantidade_caracteres = 4;
      situacao_porcentagem = 25;
    }
    else if (situacao == 1) {
      quantidade_caracteres = 0;
      situacao_porcentagem = 0;
    } 

    lcd.clear();
    lcd.setBacklight(HIGH);    

    if (situacao != 5){
    
      //Posiciona o cursor na coluna 0, linha 1;
      for (int i = 0; i < quantidade_caracteres; i++){
          lcd.setCursor(i, 0);
          lcd.write(255);
      }
  
      situacao_3 = situacao_2;
      situacao_2 = situacao_1;
      situacao_1 = situacao_porcentagem;
  
      lcd.setCursor(0, 1);
      lcd.print(String(situacao_3) + "% " + String(situacao_2) + "% " + String(situacao_1) + "%");

    }
    else{
      
      lcd.setCursor(0, 0);
      lcd.print("Boia Desconectada");
      lcd.setCursor(0, 1);
      lcd.print("F:" + String(retorno_boia_fundo) + 
              ", M:" + String(retorno_boia_meio) + 
              ", T:" + String(retorno_boia_topo));
    }

    situacao_anterior = situacao;

  }
}
