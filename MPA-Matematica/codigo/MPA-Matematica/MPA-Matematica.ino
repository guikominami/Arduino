#include "LedControl.h"
#include "binary.h"
#include <TM1637Display.h>
#include <LiquidCrystal_I2C.h>

//------------------------------------------------------
//  DISPLAY LCD
//------------------------------------------------------
//SCL: A5
//SDA: A4
LiquidCrystal_I2C lcd(0x27,16,2);

//------------------------------------------------------
//  MATRIZ DE LED
//------------------------------------------------------
//LedControl lc=LedControl(DIN,CLK,CS,1); //1 max7219 
LedControl lc=LedControl(7,9,8,1); //1 max7219

//---------------------------------------------------------------------------------------
//  DISPLAY 4 DÍGITOS (ligar os 4 CLK em portas diferentes, DIO na mesma porta)
//---------------------------------------------------------------------------------------
int CLK1 = 2;
int CLK2 = 3;
int CLK3 = 4;
int CLK4 = 5;
int CLK5 = 6;
int DIO = 10;

TM1637Display display1(CLK1,DIO);
TM1637Display display2(CLK2,DIO);
TM1637Display display3(CLK3,DIO);
TM1637Display display4(CLK4,DIO);
TM1637Display display5(CLK5,DIO);

//---------------------------------------------------------------------------------------

int botao1 = A1; 
int botao2 = A2; 
int botao3 = A3; 
int botao_zerar = 11;

int led1 = 12;
int led2 = 13;

int posicao_resposta_correta = 0;
bool operacao_iniciada = false;
int resultado_operacao = 0;
int operacao_matematica = 0;    

int nivel = 0;
int pontuacao = 0;

//com os pinos soldados pra baixo, esquerda 5V, direita GND, meio sinal
int porta_potenciometro = A0;  


//---------------------------------------------
// Definimos padrões binários para cada sinal
//---------------------------------------------
byte zero[] = {
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000};
 
byte soma[] = {
B00000000,
B00011000,
B00011000,
B01111110,
B01111110,
B00011000,
B00011000,
B00000000};
 
byte subtracao[] = {
B00000000,
B00011000,
B00011000,
B00011000,
B00011000,
B00011000,
B00011000,
B00000000};
 
byte multiplicacao[] = {
B00000000,
B01000010,
B00100100,
B00011000,
B00011000,
B00100100,
B01000010,
B00000000};
 
byte divisao[] = {
B00000000,
B00011000,
B00011000,
B01011010,
B01011010,
B00011000,
B00011000,
B00000000};
 
void setup() {
    
  lc.shutdown(0,false);   
 
  // Se o pino de entrada analógica 5 estiver desconectado, leia análogo aleatório
  // o ruído fará com que a chamada para randomSeed () gere
  // diferentes números de sementes cada vez que o programa/sketch é executado. 
  // randomSeed () irá então tornar a função random() aleatória.
  randomSeed(analogRead(0)); 
  
  // Ajustamos o brilho da matriz de leds para um valor médio
  lc.setIntensity(0,7);
  
  // Limpamos o display
  lc.clearDisplay(0); 

  resetDisplay(display1);
  resetDisplay(display2);  
  resetDisplay(display3);
  resetDisplay(display4);
  resetDisplay(display5);

  Serial.begin(9600);

  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  
  pinMode(botao1, INPUT);
  pinMode(botao2, INPUT);
  pinMode(botao3, INPUT);
  pinMode(botao_zerar, INPUT);

  lcd.init();
  lcd.setBacklight(HIGH);

  pinMode(porta_potenciometro, INPUT);  
  
}
 
void loop() {

  if (operacao_iniciada == false){

     lerPotenciometro();

     mostraDadosLCD();  
    
     realizarSorteioNumeros();

     embaralharPosicoesDisplay();
     
     operacao_iniciada = true;
     
  }

  if (digitalRead(botao_zerar) == HIGH){

     reiniciarSistema();

     operacao_iniciada = false;

     pontuacao = 0;
    
  }

  if (digitalRead(botao1) == HIGH && posicao_resposta_correta == 1){
    Serial.println("1");

    mostrarRespostaCorreta(display3);

  }
  else if (digitalRead(botao2) == HIGH && posicao_resposta_correta == 2){
    Serial.println("2");
    
    mostrarRespostaCorreta(display4);
  }

  else if (digitalRead(botao3) == HIGH && posicao_resposta_correta == 3){
    Serial.println("3");
    
    mostrarRespostaCorreta(display5);
  }
  else if (digitalRead(botao1) == HIGH && posicao_resposta_correta != 1 ||
           digitalRead(botao2) == HIGH && posicao_resposta_correta != 2 ||
           digitalRead(botao3) == HIGH && posicao_resposta_correta != 3)
  {
    Serial.println("resposta errada");
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH); 
    delay(1000);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);

    if (pontuacao > 0){
       pontuacao --;
    }

    mostraDadosLCD();  
  }

  delay(500);
}

void mostrarRespostaCorreta(TM1637Display &display){
  
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW); 

  for (int contador = 0; contador < 5; contador++){
     resetDisplay(display);
     delay(500);     
     mostraContador(display, resultado_operacao);
     delay(500);
  }   
  
  delay(1000);

  //Atualiza pontuação
  pontuacao ++;

  reiniciarSistema();
    
}

void reiniciarSistema(){
  
  resetDisplay(display1);
  resetDisplay(display2);  
  resetDisplay(display3);
  resetDisplay(display4);
  resetDisplay(display5);

  mostraOperacaoMatematica(0);  

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);

  posicao_resposta_correta = 0;
  operacao_iniciada = false;
}

void realizarSorteioNumeros(){

  int limite_numero = 0;
  int sorteio1 = 0;
  int sorteio2 = 0;

  if (nivel == 1){
    limite_numero = 10;
  }
  else if (nivel == 2){
    limite_numero = 50;
  }
  else if (nivel == 3){
    limite_numero = 100;
  }
    
  operacao_matematica = sorteiaOperacaoMatematica();

  //sorteio específico para o nível fácil, o primeiro dígito nunca será menor que o segundo
  //para divisão e subtração
  if (nivel == 1 && operacao_matematica == 2 || nivel == 1 && operacao_matematica == 4){
     sorteio1 = random(1, limite_numero);
     sorteio2 = random(1, sorteio1);
  }
  else{
     sorteio1 = random(limite_numero);
     sorteio2 = random(limite_numero);      
  }

  mostraContador(display1, sorteio1);
  mostraContador(display2, sorteio2);  

  //adição
  if (operacao_matematica == 1){
     resultado_operacao = sorteio1 + sorteio2;
  }
  //subtração
  else if (operacao_matematica == 2){  
     resultado_operacao = sorteio1 - sorteio2;
  }
  //multiplicação
  else if (operacao_matematica == 3){
     resultado_operacao = sorteio1 * sorteio2;
  }
  //divisão
  else if (operacao_matematica == 4){
     resultado_operacao = sorteio1/sorteio2;    
  }   

  Serial.println("resultado operacao");
  Serial.println(resultado_operacao);

  delay(1000);
  
}

void embaralharPosicoesDisplay(){

  int sorteio_limites_cima = 0;
  int sorteio_limites_baixo = 0;  

  //embaralhar em qual display ficará a resposta correta  
  posicao_resposta_correta = random(1, 4);

  delay(1000);  

  sorteio_limites_cima = random(1, 4) + resultado_operacao;

  if (nivel == 1){
     sorteio_limites_baixo = resultado_operacao - random(1, 2);
  }
  else{
     sorteio_limites_baixo = resultado_operacao - random(1, 4);  
  }

  Serial.println("sorteio_limites_cima");
  Serial.println(sorteio_limites_cima);  
  Serial.println("sorteio_limites_baixo");
  Serial.println(sorteio_limites_baixo);    

  //se a operação matemática for subtração, o limite pode ser 0
  if (nivel == 1 && sorteio_limites_baixo < 0){
     sorteio_limites_baixo = 0;
  }
  else if (nivel == 1 && sorteio_limites_baixo == sorteio_limites_cima){
     sorteio_limites_cima = resultado_operacao + 1;
  }  
  //se a operação matemática for divisão, o limite deve ser no mínimo 1
  else if (nivel == 1 && sorteio_limites_baixo < 0 && operacao_matematica == 4){
     sorteio_limites_baixo == 1;
  }  

  if (posicao_resposta_correta == 1){
     mostraContador(display3, resultado_operacao);    
     mostraContador(display4, sorteio_limites_cima);
     mostraContador(display5, sorteio_limites_baixo);       
  }
  else if (posicao_resposta_correta == 2){
     mostraContador(display4, resultado_operacao);    
     mostraContador(display3, sorteio_limites_cima);
     mostraContador(display5, sorteio_limites_baixo);     
  }
  else if (posicao_resposta_correta == 3){
     mostraContador(display5, resultado_operacao);    
     mostraContador(display3, sorteio_limites_cima);
     mostraContador(display4, sorteio_limites_baixo);     
  }  
}

void lerPotenciometro(){
  
  int retorno_potenciometro = analogRead(porta_potenciometro);
  retorno_potenciometro = map(retorno_potenciometro, 0, 1023, 0, 255);

  //250/3 - 80
  if (retorno_potenciometro < 80){
     nivel = 1;
  }
  else if (retorno_potenciometro > 80 && retorno_potenciometro < 160){
     nivel = 2;
  }
  else if (retorno_potenciometro > 160){
     nivel = 3;
  } 
   
}

void resetDisplay(TM1637Display &display)
{ 
  display.setBrightness(0xF);
  uint8_t data[] = { 0x0, 0x0, 0x0, 0x0 };
  display.setSegments(data);
}

void mostraContador( TM1637Display &display,int valor){
  
  display.showNumberDec(valor,false);
  
}

void mostraDadosLCD(){

  String texto;
  
  lcd.clear();
  lcd.setCursor(0,0);
  texto = "Modo: " + String(nivel);
  lcd.print(texto);
  lcd.setCursor(0,1);
  texto = "Pontos: " + String(pontuacao);  
  lcd.print(texto);
  delay(1000);  

}

int sorteiaOperacaoMatematica(){

  int tempoDadoRolando = random(10, 15);
  int operacao_matematica = 0;
  
  for(int i=0; i<tempoDadoRolando; i++){
    // A variável resultado vai assumir um valor entre 1 e 4
    operacao_matematica = random(1, 5); 
    mostraOperacaoMatematica(operacao_matematica);
    delay(100 + i * 10);
  }
  
  for(int i=0; i<2; i++){
    mostraOperacaoMatematica(0);
    delay(500);
    mostraOperacaoMatematica(operacao_matematica);
    delay(250);
  }

  return operacao_matematica;

}
 
void mostraOperacaoMatematica(int resultado){
  if(resultado==0){
    lc.setRow(0,0,zero[0]);
    lc.setRow(0,1,zero[1]);
    lc.setRow(0,2,zero[2]);
    lc.setRow(0,3,zero[3]);
    lc.setRow(0,4,zero[4]);
    lc.setRow(0,5,zero[5]);
    lc.setRow(0,6,zero[6]);
    lc.setRow(0,7,zero[7]);
  }
  else if(resultado==1){
    lc.setRow(0,0,soma[0]);
    lc.setRow(0,1,soma[1]);
    lc.setRow(0,2,soma[2]);
    lc.setRow(0,3,soma[3]);
    lc.setRow(0,4,soma[4]);
    lc.setRow(0,5,soma[5]);
    lc.setRow(0,6,soma[6]);
    lc.setRow(0,7,soma[7]);
  }
  else if(resultado==2){
    lc.setRow(0,0,subtracao[0]);
    lc.setRow(0,1,subtracao[1]);
    lc.setRow(0,2,subtracao[2]);
    lc.setRow(0,3,subtracao[3]);
    lc.setRow(0,4,subtracao[4]);
    lc.setRow(0,5,subtracao[5]);
    lc.setRow(0,6,subtracao[6]);
    lc.setRow(0,7,subtracao[7]);
  }
  else if(resultado==3){
    lc.setRow(0,0,multiplicacao[0]);
    lc.setRow(0,1,multiplicacao[1]);
    lc.setRow(0,2,multiplicacao[2]);
    lc.setRow(0,3,multiplicacao[3]);
    lc.setRow(0,4,multiplicacao[4]);
    lc.setRow(0,5,multiplicacao[5]);
    lc.setRow(0,6,multiplicacao[6]);
    lc.setRow(0,7,multiplicacao[7]);
  }
  else if(resultado==4){
    lc.setRow(0,0,divisao[0]);
    lc.setRow(0,1,divisao[1]);
    lc.setRow(0,2,divisao[2]);
    lc.setRow(0,3,divisao[3]);
    lc.setRow(0,4,divisao[4]);
    lc.setRow(0,5,divisao[5]);
    lc.setRow(0,6,divisao[6]);
    lc.setRow(0,7,divisao[7]);
  }
}
