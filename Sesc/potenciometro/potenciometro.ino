int porta_potenciometro = A0;  
int retorno_potenciometro;

int led = 6; //usar o analógico (portas digitais que tem ~)
  
void setup(){
  
  pinMode(porta_potenciometro, INPUT);

  Serial.begin(9600); 
  
} 

void loop(){ 
  
  retorno_potenciometro = analogRead(porta_potenciometro);
  retorno_potenciometro = map(retorno_potenciometro, 0, 1023, 0, 255);
  Serial.println(retorno_potenciometro);
  delay(1);

  analogWrite(led, retorno_potenciometro);
  
}
