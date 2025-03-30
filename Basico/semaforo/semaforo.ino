
//variáveis
int ledVermelho = 13;
int ledAmarelo = 12;
int ledVerde = 11;

void setup() {                
  // inicializa as variáveis e portas
  pinMode(ledVermelho, OUTPUT);         
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);  
}

void loop() {

  //Acende o LED
  digitalWrite(ledVermelho, HIGH);
  //aguarda 6 segundos
  delay(6000);
  //Apaga o LED
  digitalWrite(ledVermelho, LOW);
  delay(500);   

  //Acende o LED
  digitalWrite(ledAmarelo, HIGH);
  //aguarda 1 segundo
  delay(1000);
  //Apaga o LED
  digitalWrite(ledAmarelo, LOW);
  delay(200);  

  //Acende o LED
  digitalWrite(ledVerde, HIGH);
  //aguarda 4 segundos
  delay(4000);
  //Apaga o LED
  digitalWrite(ledVerde, LOW);
  delay(200);

}
