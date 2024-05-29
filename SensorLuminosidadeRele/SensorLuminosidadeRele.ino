int sensor_luz = A0;  
int retorno_sensor_luz;

//variáveis
int rele = 10;
  
void setup(){
  
  pinMode(sensor_luz, INPUT);
  pinMode(rele, OUTPUT);

  Serial.begin(9600); 
} 

void loop(){ 
  
  retorno_sensor_luz = analogRead(sensor_luz);
  Serial.println(retorno_sensor_luz);

  //se recebeu luminosidade
  if (retorno_sensor_luz < 50)
  {
      digitalWrite(rele, HIGH);
  }
  else
  {
      digitalWrite(rele, LOW);
  }

  delay(1000);    
}
