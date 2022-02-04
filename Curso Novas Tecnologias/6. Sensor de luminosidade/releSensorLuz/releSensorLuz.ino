#include "SoftwareSerial.h"

//variáveis
int led_vermelho = 13;
int sensor_luz = A0;
int rele = 9;
int ligado = 0;
int retorno_sensor_luz = 0;

void setup() {   

  Serial.begin(9600);
               
  // inicializa as variáveis e portas
  pinMode(sensor_luz, INPUT);
    
  pinMode(led_vermelho, OUTPUT);         
  pinMode(rele, OUTPUT);
  
}

void loop() {

  retorno_sensor_luz = analogRead(sensor_luz);
  
  Serial.println("Sensor de luminosidade:");
  Serial.println(retorno_sensor_luz);

  if (retorno_sensor_luz > 40)
  {
      apagar_luz();
  }
  else
  {
      acender_luz();
  }

  delay(10000);  
}

void acender_luz(){

    //Acende o LED
    digitalWrite(led_vermelho, HIGH);
    digitalWrite(rele, HIGH);

    ligado = 1;
}

void apagar_luz(){

    //Apaga o LED
    digitalWrite(led_vermelho, LOW);
    digitalWrite(rele, LOW);

    ligado = 0;  
}
