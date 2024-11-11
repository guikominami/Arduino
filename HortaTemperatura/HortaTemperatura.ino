#include "SoftwareSerial.h"
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

//variáveis Sensor de Umidade
int rele = 6;
int sensor_presenca = 5;
int sensor_umidade = A0;
int sensor_temperatura = A1;
int retorno_sensor_umidade = 0;
int retorno_sensor_presenca = 0;

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
#define DHTPIN sensor_temperatura // pino que estamos conectado
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

//-------------------------------------------------------------
//  Alterar a quantidade do irrigador ligado
//  30000 = 30 segundos
//-------------------------------------------------------------
int tempo_irrigacao = 30000;

//-------------------------------------------------------------
//  ALTERAR AQUI O VALOR DO LIMITE ENTRE O MOLHADO E O SECO
//-------------------------------------------------------------
int limite_molhado = 500;

void setup() {   

  Serial.begin(9600);

  lcd.init();    
  lcd.begin(31, 2);

  dht.begin();  
               
  // inicializa as variáveis e portas
  pinMode(sensor_umidade, INPUT);
  pinMode(sensor_presenca, INPUT);   
    
  pinMode(rele, OUTPUT);
  
}

void loop() {

  SensorUmidade();

  SensorPresenca();  

  LerTemperatura();

  delay(1000);  
}

void SensorUmidade(){

  retorno_sensor_umidade = analogRead(sensor_umidade);
  Serial.println("Sensor de umidade:");
  Serial.println(retorno_sensor_umidade);

  if (retorno_sensor_umidade < limite_molhado)
  {
    digitalWrite(rele, HIGH);
    delay(tempo_irrigacao);
  }
  else
  {
    digitalWrite(rele, LOW);
  }  
}

void SensorPresenca(){

  retorno_sensor_presenca = digitalRead(sensor_presenca);
  
  Serial.println("Sensor de presença:");
  Serial.println(retorno_sensor_presenca);

  if (retorno_sensor_presenca == 0)
  {
    //liga o rele
    digitalWrite(rele, HIGH);
    delay(tempo_irrigacao);
  }
  else
  {
    //Apaga o rele
    digitalWrite(rele, LOW);
  }

}

void LerTemperatura(){

  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  temperatura_medida = dht.readTemperature();

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
  texto = "T:" + String(temperatura_medida) + "C";
  lcd.print(texto);  
  texto = "Max:" + String(temperatura_padrao_maxima) + "C Min:" + String(temperatura_padrao_minima) + "C";  
  lcd.setCursor(0, 1);
  lcd.print(texto);

}