//ULTRASSOM
//ligar VCC no 5V
//ligar GND no GND
//ligar TRIG no 8
//ligar ECHO no 9

//UNO
//Ligar Led pino grande no 13 e pino pequeno no GND
 
// variáveis
int ledVermelho = 13;
int ledAmarelo = 12;
int ledVerde = 11;

int gatilho = 8;
int echo = 9;
float tempo;
float distancia_cm;
  
void setup(){
  
  pinMode(ledVermelho, OUTPUT);         
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);  
  
  // configura pino GATILHO como saída
  pinMode(gatilho,OUTPUT);
  // deixa pino em LOW
  digitalWrite(gatilho,LOW);
  delayMicroseconds(10);
 
  // configura pino ECHO como entrada
  pinMode(echo,INPUT);

  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
 
}
 
// laço principal (executado indefinidamente)
void loop() {
  // disparar pulso ultrassônico
  digitalWrite(gatilho, HIGH);
  delayMicroseconds(10);
  digitalWrite(gatilho, LOW);
  
  // medir tempo de ida e volta do pulso ultrassônico
  tempo = pulseIn(echo, HIGH);
  
  // calcular as distâncias em centímetros e polegadas
  distancia_cm = tempo / 29.4 / 2;
  
  Serial.println(distancia_cm);
  
  if (distancia_cm < 10)
  {
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVerde, LOW);
  }
  else if (distancia_cm > 10 && distancia_cm < 30)
  {
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledVerde, LOW);
  }
  else if (distancia_cm > 30 && distancia_cm < 50)
  {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledAmarelo, LOW);
  }      
  else
  {
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVerde, LOW);
  }
  
  // aguardar antes de começar tudo de novo
  delayMicroseconds(2000);
}
