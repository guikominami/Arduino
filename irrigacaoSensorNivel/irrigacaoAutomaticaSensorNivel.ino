//ligação pinos OLED
//SDA no A4
//SCK no A5

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int pino_rele_bomba = 6;
const int pino_sensor_nivel = 2;
const int potenciometro = A0;

//a cada loop, espera um delay de 1000ms = 1s (3600 = 1 hora, 28800 = 8 horas) 
const int tempo_irrigacao_ligada = 30;

int tempo_irrigacao_espera = 0;
int tempo_irrigacao_espera_antigo = 0;
int contador = 0;

//const int contadorIrrigacaoEspera = 3600; //1 hora

void setup() {

  Serial.begin(9600);
  
  pinMode(pino_rele_bomba, OUTPUT);
  //Se conectar no pino 2 não precisa de resistor, mas define como pullup
  pinMode(pino_sensor_nivel, INPUT_PULLUP);  
  pinMode(potenciometro, INPUT);

  digitalWrite(pino_rele_bomba, LOW);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }  
}

void loop() {

  int valor_sensor_nivel;  
  int retorno_potenciometro;

  int valor;

  //com o potenciometro, é possível selecionar o valor da quantidade de tempo de espera para irrigação
  retorno_potenciometro = analogRead(potenciometro); 

  if (retorno_potenciometro > 1000){
    //8h
    tempo_irrigacao_espera = 28800;
  }
  else if (retorno_potenciometro < 1000 && retorno_potenciometro > 500){
    //4h
    tempo_irrigacao_espera = 14400;
  }
  else if (retorno_potenciometro < 500 && retorno_potenciometro > 10){
    //1h
    tempo_irrigacao_espera = 3600;
    //tempo_irrigacao_espera = 30; //ALTERAR
  }  
  else if (retorno_potenciometro < 10){
    //2 minutos
    tempo_irrigacao_espera = 120;
  }
  
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

        EscreverTextoTela(String(contador_irrigacao_ligada), "SEM AGUA");     

        delay(2000);

        Serial.println("desligar bomba");
        break;
      }
      else
      {
        digitalWrite(pino_rele_bomba, HIGH);
 
        EscreverTextoTela(String(contador_irrigacao_ligada), "IRRIGANDO"); 

        Serial.println("irrigando");
      }
      
      delay(1000);
    }

    //desligar a bomba depois do tempo de irrigação
    digitalWrite(pino_rele_bomba, LOW);

  }

  Serial.println("contador");
  Serial.println(contador);  

  EscreverTextoTela(String(contador), "AGUARDO");

  contador --;

  delay (1000);  
}

void EscreverTextoTela(String contador, String info) {

  display.clearDisplay();

  display.setTextSize(3);     
  display.setTextColor(WHITE);
  display.setCursor(0, 0);    
  display.println(contador + "s");

  display.setTextSize(2);  
  display.setCursor(0, 45);    
  display.println(info);  

  display.display();
}