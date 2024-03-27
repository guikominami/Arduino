int sensor_luz = A0;  
int retorno_sensor_luz;

//variáveis
int sensor_presenca = 7;
int rele = 10;
int ligado = 0;
int retorno_sensor_presenca = 0;
  
void setup(){
  
  pinMode(sensor_luz, INPUT);
  pinMode(sensor_presenca, INPUT);
  pinMode(rele, OUTPUT);

  Serial.begin(9600); 
  
} 

void loop(){ 
  
  retorno_sensor_luz = analogRead(sensor_luz);
  Serial.println(retorno_sensor_luz);

  retorno_sensor_presenca = digitalRead(sensor_presenca);
  
  Serial.println("Sensor de presença:");
  Serial.println(retorno_sensor_presenca);

  //se recebeu luminosidade
  if (retorno_sensor_luz < 50)
  {
    //rotina se passar alguém na frente
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
  }

  delay(200);    
  
}
