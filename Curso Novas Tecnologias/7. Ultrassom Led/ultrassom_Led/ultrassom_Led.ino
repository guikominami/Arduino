//ULTRASSOM
//ligar VCC no 5V
//ligar GND no GND
//ligar TRIG no 11
//ligar ECHO no 12

//UNO
//Ligar Led pino grande no 13 e pino pequeno no GND
 
// variáveis
int led = 13;
int led2 = 10;
int led3 = 8;

int gatilho = 11;
int echo = 12;
float tempo;
float distancia_cm;
  
void setup(){
  
  pinMode(led,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  
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
    digitalWrite(led, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
  else if (distancia_cm > 20 && distancia_cm < 40)
  {
    digitalWrite(led2, HIGH);
    digitalWrite(led, LOW);
    digitalWrite(led3, LOW);
  }
  else if (distancia_cm > 50 && distancia_cm < 70)
  {
    digitalWrite(led3, HIGH);
    digitalWrite(led, LOW);
    digitalWrite(led2, LOW);
  }      
  else
  {
    digitalWrite(led, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
  
  // aguardar antes de começar tudo de novo
  delayMicroseconds(2000);
}
