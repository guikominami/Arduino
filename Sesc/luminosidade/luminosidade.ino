int porta_sensor_luz = A1;  
int retorno_sensor_luz;

int led = 6; //usar o analógico (portas digitais que tem ~)
  
void setup(){
  
  pinMode(porta_sensor_luz, INPUT);

  Serial.begin(9600); 
  
} 

void loop(){ 
  
  retorno_sensor_luz = analogRead(porta_sensor_luz);
  retorno_sensor_luz = map(retorno_sensor_luz, 0, 1023, 0, 255);
  Serial.println(retorno_sensor_luz);
  
  delay(100);

  analogWrite(led, retorno_sensor_luz);
  
}
