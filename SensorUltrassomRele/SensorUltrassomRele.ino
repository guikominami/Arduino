//ULTRASSOM
//ligar VCC no 5V
//ligar GND no GND
//ligar TRIG no 8
//ligar ECHO no 9

int pino_gatilho = 8; // pino TRIG do sensor ultrassônico
int pino_echo = 9; // pino ECHO do sensor ultrassônico
float tempo; // para armazenar o tempo de ida e volta do sinal em microsegundos
float distancia_cm; // para armazenar a distância em centímetros

int pino_rele = 10;
int encendido = 0;

void setup()
{
  Serial.begin(9600);
  
  pinMode(pino_rele, OUTPUT);

  pinMode(pino_gatilho, OUTPUT);
  digitalWrite(pino_gatilho, LOW);
  delayMicroseconds(10);
 
  // configura pino ECHO como entrada
  pinMode(pino_echo, INPUT);  
}
 
void loop()
{
    // disparar pulso ultrassônico
    digitalWrite(pino_gatilho, HIGH);
    delayMicroseconds(10);
    digitalWrite(pino_gatilho, LOW);
    
    // medir tempo de ida e volta do pulso ultrassônico
    tempo = pulseIn(pino_echo, HIGH);
    
    // calcular as distâncias em centímetros
    distancia_cm = tempo / 29.4 / 2;
  
    // aguardar um pouquinho antes de começar tudo de novo
    delayMicroseconds(200);

    Serial.println("distância: ");
    Serial.println(distancia_cm);
    
    if (distancia_cm < 10 && encendido == 0)
    {
      digitalWrite(pino_rele, HIGH);   
      encendido = 1;
    }
    else if (distancia_cm < 10 && encendido == 1){
      digitalWrite(pino_rele, LOW);    
      encendido = 0;
    }
    delay(500);
}
