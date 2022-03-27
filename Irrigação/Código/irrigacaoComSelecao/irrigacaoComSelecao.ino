#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//------------------------------------------
// Inicializa o display no endereco 0x27
//SCL: A5
//SDA: A4
LiquidCrystal_I2C lcd(0x27,16,2);
//------------------------------------------

//ULTRASSOM
//ligar VCC no 5V
//ligar GND no GND
//ligar TRIG no 10
//ligar ECHO no 9
int gatilho = 10;
int echo = 9;
  
int potenciometro = A0;
int botao = 6;
int rele = 8;

int tipo_sistema = 0;
int tipo_sistema_antigo = 0;

float minuto = 60;
float hora = 60 * minuto;
float quantidadeEspera = 1;

//o contador não está na escala milisegundos porque no loop ele precisa esperar um delay
float contadorIrrigacaoEspera = quantidadeEspera * minuto; //MUDAR PRA HORA 

//o tempo de espera será o delay em milisegundos
int tempoIrrigacaoLigado = 6000;

int contador = 0;
    
void setup() 
{
    Serial.begin(9600);

    lcd.init();
    
    pinMode(potenciometro, INPUT);
    pinMode(botao, INPUT);
    
    pinMode(rele, OUTPUT);
  
    //ultrassom
    pinMode(gatilho,OUTPUT);
    digitalWrite(gatilho,LOW);
    delayMicroseconds(10);
    pinMode(echo,INPUT);    
  
    MostrarDadosLCD();

    DesligarIrrigacao();
}

void loop() 
{
    SelecionarSistema();

    Serial.println("tipo_sistema: ");
    Serial.println(tipo_sistema);  

    //botão
    if (tipo_sistema == 1)
    {
        VerificarBotao();

        contador = 0;
    }      
    else if (tipo_sistema == 2)
    {
        VerificarUltrassomTimer();  

        contador = 0;
    }
    else if (tipo_sistema == 3)
    {
        VerificarUltrassom();  

        contador = 0;
    }    
    else if (tipo_sistema == 4)
    {
        contador ++;

        Serial.println("contador: ");
        Serial.println(contador); 
        
        if (contador == int(contadorIrrigacaoEspera)){
           
           LigarIrrigacaoTimer();
           contador = 0;
        }
    }
          
    delay(1000);
}

void VerificarBotao(){

  int retorno_botao = digitalRead(botao);
  
  Serial.println("Botão:");
  Serial.println(retorno_botao);
  
  if (retorno_botao == 1)
  {
     LigarIrrigacaoTimer();
  }
  
  delay(200); 
  
}

float LerUltrassom(){

  float tempo;
  float distancia_cm;    

  // disparar pulso ultrassônico
  digitalWrite(gatilho, HIGH);
  delayMicroseconds(10);
  digitalWrite(gatilho, LOW);
  
  // medir tempo de ida e volta do pulso ultrassônico
  tempo = pulseIn(echo, HIGH);
  
  // calcular as distâncias em centímetros e polegadas
  distancia_cm = tempo / 29.4 / 2;
  
  Serial.println(distancia_cm);

  return distancia_cm;
    
}

void VerificarUltrassomTimer(){

  int distancia_cm = LerUltrassom();

  if (distancia_cm < 10){
    
      LigarIrrigacaoTimer();
  }
  
  delay(500);
}

void VerificarUltrassom(){

  int distancia_cm = LerUltrassom();

  if (distancia_cm < 10){
    
      LigarIrrigacao();
  }
  
  else{
    
      DesligarIrrigacao();
  }  

  delay(500);

}

void SelecionarSistema(){
    
    //1 = ligar relê por botão, 2 = ligar relê por presença, 3 = ligar relê por timer
    //potenciometro: 0 a 1012

    int retorno_potenciometro = analogRead(potenciometro);

    if (retorno_potenciometro < 250)
    {
        tipo_sistema = 1;
    }
    else if (retorno_potenciometro > 250 && retorno_potenciometro < 500)
    {
        tipo_sistema = 2;
    }
    else if (retorno_potenciometro > 500 && retorno_potenciometro < 750)
    {
        tipo_sistema = 3;
    }
    else if (retorno_potenciometro > 750)
    {
        tipo_sistema = 4;
    }       

    if (tipo_sistema_antigo != tipo_sistema)
    {
        Serial.println("tipo_sistema_antigo:");
        Serial.println(tipo_sistema_antigo);
        
        MostrarDadosLCD();
        DesligarIrrigacao();
    }

    tipo_sistema_antigo = tipo_sistema;

}

void LigarIrrigacaoTimer(){

    digitalWrite(rele, LOW);
    
    lcd.setCursor(0, 1);
    lcd.print("Irrigando");

    //aguardar tempo de irrigação ligada
    delay(tempoIrrigacaoLigado);

    digitalWrite(rele, HIGH);
    
    lcd.setCursor(0, 1);
    lcd.print("Desligada");    
    
}

void LigarIrrigacao(){

    digitalWrite(rele, LOW);
    
    lcd.setCursor(0, 1);
    lcd.print("Irrigando");  
    
}

void DesligarIrrigacao(){
  
    digitalWrite(rele, HIGH);
    
    lcd.setCursor(0, 1);
    lcd.print("Desligada");     
}

void MostrarDadosLCD(){

  String texto_sistema;

  if (tipo_sistema == 1)
  {
      texto_sistema = "Botao";
  }
  else if (tipo_sistema == 2)
  {
      texto_sistema = "Presenca Tempo";
  }
  else if (tipo_sistema == 3)
  {
      texto_sistema = "Presenca";
  }  
  else if (tipo_sistema == 4)
  {
      texto_sistema = "Timer " + String(int(quantidadeEspera)) + "h";
  }
  
  lcd.setBacklight(HIGH);
  lcd.clear();
  //Posiciona o cursor na coluna 0, linha 0;
  lcd.setCursor(0, 0);
  //lcd.setCursor(0, 1);
  lcd.print(texto_sistema);

}
