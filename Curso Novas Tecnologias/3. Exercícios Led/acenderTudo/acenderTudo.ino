
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
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVerde, HIGH);

    delay(1000);
    
    //Apaga o LED
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledAmarelo, LOW);    
    digitalWrite(ledVerde, LOW);   

    delay(1000);
  
}
