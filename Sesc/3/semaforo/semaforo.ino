
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

  //-----------------------------------
  
  //acende o LED vermelho carro
  digitalWrite(ledVermelho, HIGH);
  
  //aguarda 6 segundos
  delay(6000);
  
  //apaga o LED vermelho carro
  digitalWrite(ledVermelho, LOW);

  //-----------------------------------

  //acende o LED amarelo carro
  digitalWrite(ledAmarelo, HIGH);

  //aguarda 1 segundo
  delay(1000);
  
  //Apaga o LED amarelo carro
  digitalWrite(ledAmarelo, LOW);

  //-----------------------------------

  //Acende o LED verde carro
  digitalWrite(ledVerde, HIGH);
  
  //aguarda 4 segundos
  delay(4000);
  
  //Apaga o LED verde carro
  digitalWrite(ledVerde, LOW);
 
}
