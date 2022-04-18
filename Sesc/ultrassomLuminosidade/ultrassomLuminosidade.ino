//ULTRASSOM
//ligar VCC no 5V
//ligar GND no GND
//ligar TRIG no 8
//ligar ECHO no 9

int trigger = 8;
int echo = 9;
float tempo;
float distancia_cm;

int led = 6; //usar o analógico (portas digitais que tem ~)
  
void setup(){
  
  // configura pino GATILHO como saída
  pinMode(trigger,OUTPUT);
  // deixa pino em LOW
  digitalWrite(trigger,LOW);
  delayMicroseconds(10);
 
  // configura pino ECHO como entrada
  pinMode(echo,INPUT);

  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
  
} 

void loop(){ 

  int distancia_mapa;
  
  // disparar pulso ultrassônico
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  // medir tempo de ida e volta do pulso ultrassônico
  tempo = pulseIn(echo, HIGH);
  
  // calcular as distâncias em centímetros e polegadas
  distancia_cm = tempo / 29.4 / 2;
  
  Serial.println(distancia_cm);  

  distancia_mapa = map(distancia_cm, 4, 100, 0, 255);
  Serial.println(distancia_mapa);
  
  delay(100);

  analogWrite(led, distancia_mapa);
  
}
