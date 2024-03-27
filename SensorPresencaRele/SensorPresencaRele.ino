#include "SoftwareSerial.h"

//variáveis
int sensor_presenca = 7;
int rele = 10;
int ligado = 0;
int retorno_sensor_presenca = 0;

void setup() {   

  Serial.begin(9600);
               
  // inicializa as variáveis e portas
  pinMode(sensor_presenca, INPUT);
  pinMode(rele, OUTPUT);
  
}

void loop() {

  retorno_sensor_presenca = digitalRead(sensor_presenca);
  
  Serial.println("Sensor de presença:");
  Serial.println(retorno_sensor_presenca);

  if (retorno_sensor_presenca == 0 && ligado == 0)
  {
    //Acende o LED
    digitalWrite(rele, HIGH);

    ligado = 1;
  }
  else if (retorno_sensor_presenca == 0 && ligado == 1)
  {
    //Apaga o LED
    digitalWrite(rele, LOW);

    ligado = 0;
  }

  delay(200);  
}
