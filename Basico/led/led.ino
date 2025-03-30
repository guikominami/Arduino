//variáveis
int led_vermelho = 13;

//void significa uma função. A função setup só é executado uma vez no código.
void setup() {       
  
  // inicializa as variáveis e portas
  pinMode(led_vermelho, OUTPUT);         
  
}

//A função loop fica sendo executada o tempo inteiro.
void loop() {

  //Acende o led
  digitalWrite(led_vermelho, HIGH);
  delay(1000);
  
  //Apaga o led
  digitalWrite(led_vermelho, LOW);
  delay(1000);
 
}
