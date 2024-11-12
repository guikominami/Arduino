#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

//----------------------------------------------------------------------
//  Display LCD
//----------------------------------------------------------------------
//Inicializa o display no endereco 0x27
// 1. GND
// 2. 5V
// 3. SDA: A4
// 4. SCL: A5
LiquidCrystal_I2C lcd(0x27,16,2);

//----------------------------------------------------------------------
//  Sensor de temperatura
//----------------------------------------------------------------------
#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

// Conecte pino 1 do sensor (esquerda) ao +5V
// Conecte pino 2 do sensor ao pino de dados definido em seu Arduino
// Conecte pino 4 do sensor ao GND
// Conecte o resistor de 10K entre pin 2 (dados) 
// e ao pino 1 (VCC) do sensor
DHT dht(DHTPIN, DHTTYPE);

int temperatura_padrao_maxima = 0;
int temperatura_padrao_minima = 0;
int temperatura_medida = 0;
int umidade_medida = 0;  

//----------------------------------------------------------------------
    
void setup() 
{
    Serial.begin(9600);
    
    lcd.init();    
    lcd.begin(31, 2);

    dht.begin();
  
}

void loop() 
{

  LerTemperatura();

  delay(10000);
    
}

void LerTemperatura(){

  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  temperatura_medida = dht.readTemperature();
  umidade_medida = dht.readHumidity();

  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(temperatura_medida)) 
  {
    Serial.println("Falha ao ler temperatura!");
  } 
  else 
  {
    Serial.print("Temperatura: ");
    Serial.print(temperatura_medida);
    Serial.println(" *C");

    if (temperatura_padrao_minima == 0 && temperatura_padrao_maxima == 0){
      temperatura_padrao_maxima = temperatura_medida;
      temperatura_padrao_minima = temperatura_medida;
    }

    if (temperatura_medida > temperatura_padrao_maxima){
      temperatura_padrao_maxima = temperatura_medida;
    }
    
    if (temperatura_medida < temperatura_padrao_minima){
      if (temperatura_medida > 0){
        temperatura_padrao_minima = temperatura_medida;
      }
    }

    MostraDadosTemperaturaLCD();
  }
}

void MostraDadosTemperaturaLCD(){

  String texto;
  
  lcd.setBacklight(HIGH);
  lcd.clear();
  //Posiciona o cursor na coluna 0, linha 0;
  lcd.setCursor(0, 0);
  texto = "T:" + String(temperatura_medida) + "C Um:" + String(umidade_medida);
  lcd.print(texto);  
  texto = "Max:" + String(temperatura_padrao_maxima) + "C Min:" + String(temperatura_padrao_minima) + "C";  
  lcd.setCursor(0, 1);
  lcd.print(texto);

}
