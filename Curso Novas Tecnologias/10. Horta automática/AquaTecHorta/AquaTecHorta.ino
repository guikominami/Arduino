int pinoRele = 7;         //variável que indica que conectamos o pino do relê na porta digital 7
int pinoSensorSolo = A0;  //variável que indica que conectamos o pino do sensor de umidade na porta analógica A0

int pinoRele2 = 8;
int pinoSensorSolo2 = A1;

//Variável para definirmos o valor máximo molhado. 
//Para verificar o seu valor, digite após o símbolo "=" o valor máximo quando o sensor estiver dentro do vaso ou água.
int valorMaximoMolhado = 430;

//Void é uma função. A função setup serve pra fazer os ajustes iniciais e é executada uma vez só quando ligamos o Arduino.
void setup() {

  //inicia a leitura da porta Serial
  Serial.begin(9600);
  
  pinMode(pinoRele, OUTPUT);        //Define o pino do relê como saída, pois iremos enviar um comando pra ele.
  pinMode(pinoSensorSolo, INPUT);   //Define o pino do sensor de umidade como entrada, pois iremos ler o resultado dele.

}

//Void é uma função. A função loop fica sendo executada de maneira contínua.
void loop() {

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
    ligarTorneira();

    //apenas um aviso na serial
    Serial.println("seco, ligar torneira");
  }
  //se a leitura do solo for menor que o valor máximo molhado, significa que está molhado
  else if (valorSensorSolo < valorMaximoMolhado){
    
    //chama a função que desliga o relê da torneira
    desligarTorneira();

    //apenas um aviso na serial
    Serial.println("molhado, desligar torneira");
  }

  //aguarda 1 segundo (1000 milisegundos)
  delay (1000);
 
}

//função que liga a torneira
void ligarTorneira(){

  //envia um sinal para ligar o pino que definimos para o relê
  digitalWrite(pinoRele, HIGH);

  //aguarda 1 segundo (1000 milisegundos)
  delay (1000);
  
}

//função que desliga a torneira
void desligarTorneira(){

  //envia um sinal para desligar o pino que definimos para o relê
  digitalWrite(pinoRele, LOW);
    
}
