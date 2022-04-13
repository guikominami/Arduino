
//variáveis
int ledVermelho = 13;
int ledAmarelo = 12;
int ledVerde = 11;

int ledVermelhoPedestre = 10;
int ledVerdePedestre = 9;

void setup() {         
         
  // inicializa as variáveis e portas
  pinMode(ledVermelho, OUTPUT);         
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);  

  pinMode(ledVermelhoPedestre, OUTPUT);  
  pinMode(ledVerdePedestre, OUTPUT);  
  
}

void loop() {

  //-----------------------------------
  
  //acende o LED vermelho carro
  digitalWrite(ledVermelho, HIGH);

  //acende o LED verde pedestre
  digitalWrite(ledVerdePedestre, HIGH);
  
  //aguarda 6 segundos
  delay(6000);
  
  //apaga o LED vermelho carro
  digitalWrite(ledVermelho, LOW);
  
  //delay(500);   

  //-----------------------------------

  //acende o LED amarelo carro
  digitalWrite(ledAmarelo, HIGH);

  //apaga o LED verde pedestre
  digitalWrite(ledVerdePedestre, LOW);  

  //acende o LED vermelho pedestre
  digitalWrite(ledVermelhoPedestre, HIGH);  

  //aguarda 1 segundo
  delay(1000);
  
  //Apaga o LED amarelo carro
  digitalWrite(ledAmarelo, LOW);
  
  //delay(200);  

  //-----------------------------------

  //Acende o LED verde carro
  digitalWrite(ledVerde, HIGH);
  
  //aguarda 4 segundos
  delay(4000);
  
  //Apaga o LED verde carro
  digitalWrite(ledVerde, LOW);

  //apaga o LED vermelho pedestre
  digitalWrite(ledVermelhoPedestre, LOW);
  
  //delay(200);

  
}
