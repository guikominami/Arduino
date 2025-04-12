#include <TM1637Display.h>
//#include "display.h"

//Sensores de presença
int pinoSensorMovimento1 = A0;
int pinoSensorMovimento2 = A1;
int acionamentoSensor1;
int acionamentoSensor2;
int contador1 = 0;
int contador2 = 0;
int contadorTotal = 0;

//Display
const int CLK1 = 8;
const int CLK2 = 9;
const int CLK3 = 10;
const int DIO = 7;

int botaoZera = 2;
int botaoTotal = 3;

TM1637Display display1(CLK1, DIO);
TM1637Display display2(CLK2, DIO);
TM1637Display display3(CLK3, DIO);

void setup()
{

  pinMode(pinoSensorMovimento1, INPUT);
  pinMode(pinoSensorMovimento2, INPUT);

  limpaContadores();
  
  Serial.begin(9600);

  pinMode(botaoTotal, INPUT);

}

void loop()
{

    acionamentoSensor1 = digitalRead(pinoSensorMovimento1);
    Serial.println(acionamentoSensor1);
  
    if (acionamentoSensor1 == 0) {
      contador1 = contador1 + 1;
      mostraContador(display1, contador1);
      
      //limpa o contador total para não confundir a soma
      resetDisplay(display3);

      delay(1000);      
    }

    acionamentoSensor2 = digitalRead(pinoSensorMovimento2);
    Serial.println(acionamentoSensor2);
  
    if (acionamentoSensor2 == 0) {
      contador2 = contador2 + 1;
      mostraContador(display2, contador2);

      //limpa o contador total para não confundir a soma
      resetDisplay(display3);      

      delay(1000);      
    }    

    if (digitalRead(botaoTotal) == HIGH) {  
      contadorTotal = contador1 + contador2;
      mostraContador(display3, contadorTotal);
    }

    if (digitalRead(botaoZera) == HIGH) {  
      limpaContadores();
    }    

}

void resetDisplay(TM1637Display &display)
{
  display.setBrightness(0xF);
  uint8_t data[] = { 0x0, 0x0, 0x0, 0x0 };
  display.setSegments(data);
}

void mostraContador( TM1637Display &display, int valor)
{
  display.showNumberDec(valor, false);
}

void limpaContadores(){

  resetDisplay(display1);
  resetDisplay(display2);
  resetDisplay(display3);

  contadorTotal = 0;
  contador1 = 0;
  contador2 = 0; 
}
