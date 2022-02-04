int pinoReleBoia = 9;   //variável que indica que conectamos o pino do relê na porta digital 9
int pinoBoia = 8;   //variável que indica que conectamos o pino da bóia na porta digital 8

int pinoReleHorta = 7;   //rele do sensor de solo
int pinoSensorSolo = A0;  //variável que indica que conectamos o pino do sensor de umidade na porta analógica A0

//Variável para definirmos o valor máximo molhado. 
//Para verificar o seu valor, digite após o símbolo "=" o valor máximo quando o sensor estiver dentro do vaso ou água.
int valorMaximoMolhado = 430;

//Void é uma função. A função setup serve pra fazer os ajustes iniciais e é executada uma vez só quando ligamos o Arduino.
void setup() {

  //inicia a leitura da porta Serial
  Serial.begin(9600);
  
  pinMode(pinoReleBoia, OUTPUT);  //Define o pino do relê como saída, pois iremos enviar um comando pra ele.
  pinMode(pinoReleHorta, OUTPUT);  //Define o pino do relê como saída, pois iremos enviar um comando pra ele.  
  pinMode(pinoBoia, INPUT);   //Define o pino da bóia como entrada, pois iremos ler o resultado dele.
  pinMode(pinoSensorSolo, INPUT);   //Define o pino do sensor de umidade como entrada, pois iremos ler o resultado dele.
  
}

//Void é uma função. A função loop fica sendo executada de maneira contínua.
void loop() {

   lerBoia();

   lerHorta();
 
}

void lerBoia(){

  //variável que irá receber o valor da bóia
  int valorSensorBoia;  

  //Lê o valor do pino digital que definimos para o sensor de bóia
  valorSensorBoia = digitalRead(pinoBoia);
 
  //Mostra o valor da porta analogica no serial monitor (para ver esse valor, clique na lupa a direita no alto)
  Serial.println("valor Sensor bóia: ");
  Serial.println(valorSensorBoia);  

  //se o valor do sensor da bóia for igual a 1, significa que a bóia virada pra baixo está no nível alto, a caixa está cheia, desligar relê da torneira
  if (valorSensorBoia == 1){

    //chama a função que desliga o relê da torneira
    desligarTorneira(pinoReleBoia);

    //apenas um aviso na serial
    Serial.println("desligar torneira");
  }
  //se o valor do sensor da bóia for igual a 0, significa que a bóia virada pra baixo está no nível baixo, a caixa está vazia, ligar relê da torneira
  else if (valorSensorBoia == 0){

    //chama a função que liga o relê da torneira
    ligarTorneira(pinoReleBoia);

    //apenas um aviso na serial
    Serial.println("ligar torneira");
  }

  //aguarda 1 segundo (1000 milisegundos)
  delay (1000);  
}

void lerHorta(){

  //variável que irá receber o valor do sensor de umidade
  int valorSensorSolo;

  //Lê o valor do pino analógico que definimos para o sensor de umidade de solo.
  valorSensorSolo = analogRead(pinoSensorSolo);
 
  //Mostra o valor da porta analogica no serial monitor (para ver esse valor, clique na lupa a direita no alto)
  Serial.println("valor Sensor solo: ");
  Serial.println(valorSensorSolo);

  //se a leitura do solo for maior que o valor máximo molhado, significa que está seco
  if (analogRead(pinoSensorSolo) > valorMaximoMolhado){
    
    //chama a função que liga o relê da torneira
    ligarTorneira(pinoReleHorta);

    //apenas um aviso na serial
    Serial.println("seco, ligar torneira");
  }
  //se a leitura do solo for menor que o valor máximo molhado, significa que está molhado
  else if (valorSensorSolo < valorMaximoMolhado){
    
    //chama a função que desliga o relê da torneira
    desligarTorneira(pinoReleHorta);

    //apenas um aviso na serial
    Serial.println("molhado, desligar torneira");
  }

  //aguarda 1 segundo (1000 milisegundos)
  delay (1000);
  
}

//função que liga a torneira
void ligarTorneira(int rele){

  //envia um sinal para ligar o pino que definimos para o relê
  digitalWrite(rele, HIGH);
  //aguarda 1 segundo
  delay (1000);
  
}

//função que desliga a torneira
void desligarTorneira(int rele){

  //envia um sinal para desligar o pino que definimos para o relê
  digitalWrite(rele, LOW);
    
}
