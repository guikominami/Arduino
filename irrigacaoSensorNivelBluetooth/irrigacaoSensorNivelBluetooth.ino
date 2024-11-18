const int pino_rele_bomba = 6;
const int pino_sensor_nivel = 2;

//a cada loop, espera um delay de 1000ms = 1s (3600 = 1 hora, 28800 = 8 horas) 
const long segundo = 1;
const long minuto = segundo * 60;
const long hora   = minuto * 60;
const long meio_dia    = hora * 12;
const long dia    = hora * 24;

//valores padrões de irrigação
long tempo_irrigacao_ligada = 60;
long tempo_irrigacao_espera = dia;

long tempo_irrigacao_espera_antigo = 0;
long contador = 0;

int contador_agua = 0;

int state;

//const int contadorIrrigacaoEspera = 3600; //1 hora

void setup() {

  Serial.begin(9600);
  
  pinMode(pino_rele_bomba, OUTPUT);
  //Se conectar no pino 2 não precisa de resistor, mas define como pullup
  pinMode(pino_sensor_nivel, INPUT_PULLUP);  
  
  digitalWrite(pino_rele_bomba, LOW);
}

void loop() {

  int valor_sensor_nivel;  
  int valor;

  if (Serial.available() > 0) 
  {
    state = Serial.read();
    Serial.println(state);
  }

  if (state == 49){
    Serial.println("Opção tempo de irrigação espera de 1 dia.");
    tempo_irrigacao_espera = dia;
  }

  if (state == 50){
    Serial.println("Opção tempo de irrigação espera de 1 minuto.");
    tempo_irrigacao_espera = minuto;
  }  

  if (state == 51){
    Serial.println("Opção tempo de irrigação espera de meio dia.");
    tempo_irrigacao_espera = meio_dia;    
  } 
  
  if (state == 52){
    Serial.println("Opção tempo de irrigação ligada de 30 segundos.");       
    tempo_irrigacao_ligada = 30;    
  }

  if (state == 53){
    Serial.println("Opção tempo de irrigação ligada de 1 minuto.");    
    tempo_irrigacao_ligada = minuto;
  }      

   if (state == 54){
    Serial.println("Opção tempo de irrigação ligada de 2 minutos.");    
    tempo_irrigacao_ligada = 2 * minuto;
  }  

  Serial.println("tempo_irrigacao_ligada");
  Serial.println(tempo_irrigacao_ligada);   

  //caso seja alterado o tempo no meio do sistema, reiniciar o contador
  if (tempo_irrigacao_espera_antigo != tempo_irrigacao_espera){
    contador = tempo_irrigacao_espera;
    tempo_irrigacao_espera_antigo = tempo_irrigacao_espera;

    delay(1000);
  }

  if (contador == 0)
  {
    //iniciar o procedimento de irrigação e zerar o contador
    contador = tempo_irrigacao_espera;

    //ligar irrigação por um tempo determinado
    for(int contador_irrigacao_ligada = tempo_irrigacao_ligada; contador_irrigacao_ligada > 0; contador_irrigacao_ligada--){

      Serial.println("contador_irrigacao_ligada");
      Serial.println(contador_irrigacao_ligada);

      valor_sensor_nivel = digitalRead(pino_sensor_nivel);    

      Serial.println("valor_sensor_nivel");
      Serial.println(valor_sensor_nivel);      

      //vazio = 0
      if (valor_sensor_nivel == 1)
      {
        digitalWrite(pino_rele_bomba, LOW);

        delay(2000);

        Serial.println("Sem água - desligar bomba");
        break;
      }
      else
      {
        digitalWrite(pino_rele_bomba, HIGH);

        Serial.println("irrigando");
      }

      delay(1000);
    }

    //Verificar quantas vezes vai irrigar até que acabe a água
    if (valor_sensor_nivel == 0)
    {
      contador_agua ++;     
    }

    Serial.println("Quantas irrigações");
    Serial.println(contador_agua);   

    //desligar a bomba depois do tempo de irrigação
    digitalWrite(pino_rele_bomba, LOW);

  }

  Serial.println("contador");
  Serial.println(contador);  

  contador --;

  delay (1000);  
}