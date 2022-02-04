
//variáveis
int led_vermelho = 13;
int led_amarelo = 12;
int led_verde = 11;

//void significa uma função. A função setup só é executado uma vez no código.
void setup() {       
  
  // inicializa as variáveis e portas
  pinMode(led_vermelho, OUTPUT);         
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_verde, OUTPUT);  
  
}

//A função loop fica sendo executada o tempo inteiro.
void loop() {

  //Acende os 3 LEDs
  digitalWrite(led_vermelho, HIGH);
  delay(1000);
  digitalWrite(led_amarelo, HIGH);
  delay(1000);
  digitalWrite(led_verde, HIGH);  
  delay(1000);
  
  //Apaga os 3 LEDs
  digitalWrite(led_vermelho, LOW);
  delay(1000);
  digitalWrite(led_amarelo, LOW);
  delay(1000);
  digitalWrite(led_verde, LOW);
  delay(1000);
 
}
