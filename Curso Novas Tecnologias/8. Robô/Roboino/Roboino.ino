
//5V DO DRIVER DE MOTOR LIGADO NO VIN DO ARDUINO, PARA LIGAR UM FONTE EXTERNA
//GND DO DRIVER DE MOTOR LIGADO NO GND DO ARDUINO

//INI1 LIGADO NO 8 DO ARDUINO
//INI2 LIGADO NO 9 DO ARDUINO
//INI3 LIGADO NO 10 DO ARDUINO
//INI4 LIGADO NO 11 DO ARDUINO

//Bluetooth
//5v no 5v
//gnd no gnd
//rx no tx do arduino
//tx no rx do arduino

//RETIRAR O RX E TX AO SUBIR O CÓDIGO

//verm tx

//SERVOS
//o lado de cima do servo será sempre o parafuso do lado do dissipador
//o lado de baixo do servo será sempre do lado do parafuso da força

//Servo da esquerda ligado no IN3 e 4.
//Servo da direita ligado no IN1 e 2.

//pino pequeno do Led no GND e grande na porta 13
//Luz ligada W
//Luz desligada w

//int ENA = 5;
int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;
//int ENB = 6;

int pinLed1 = 12;
int pinLed2 = 7;
int pinBuzzer = 13;

int state;
int flag = 0;

int piscaAlertaLigado = 0;

void setup() {

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinLed1, OUTPUT);  
  pinMode(pinLed2, OUTPUT);  

  Serial.begin(9600);
}

void loop() {

  //Caso necessário testar os motores
  //testeMotores();

  if (Serial.available() > 0)     // Ckeck for command Recieved
  {
    state = Serial.read();
    Serial.println(state);
    flag = 0;
  }
  if (state == 'S')     // Checking Command from User
  {
    stp();
    if (flag == 0) {
      Serial.println("Stop");
      flag = 1;
    }
  }
  else if (state == 'F')
  {
    fwd();
    if (flag == 0)
    {
      Serial.println("Forward");
      flag = 1;
    }
  }
  else if (state == 'B')
  {
    back();
    if (flag == 0)
    {
      Serial.println("Backward");
      flag = 1;
    }
  }
  else if (state == 'L')
  {
    left();
    if (flag == 0)
    {
      Serial.println("Left");
      flag = 1;
    }
  }
  else if (state == 'R')
  {
    right();
    if (flag == 0)
    {
      Serial.println("Right");
      flag = 1;
    }
  }
  else if (state == 'W')
  {
    ligaLuz();
    if (flag == 0)
    {
      Serial.println("liga luz");
      flag = 1;
    }
  }
  else if (state == 'w')
  {
    desligaLuz();
    if (flag == 0)
    {
      Serial.println("desliga luz");
      flag = 1;
    }
  }    
  else if (state == 'U')
  {
    ligaLuzTraseira();
    if (flag == 0)
    {
      Serial.println("liga luz trazeira");
      flag = 1;
    }
  }
  else if (state == 'u')
  {
    desligaLuzTraseira();
    if (flag == 0)
    {
      Serial.println("desliga luz traseira");
      flag = 1;
    }
  }      
  else if (state == 'V')
  {
    ligaBuzina();
    if (flag == 0)
    {
      Serial.println("liga buzina");
      flag = 1;
    }
  }
  else if (state == 'v')
  {
    desligaBuzina();
    if (flag == 0)
    {
      Serial.println("desliga buzina");
      flag = 1;
    }
  }   
  else if (state == 'X')
  {
    ligaPiscaAlerta();
    if (flag == 0)
    {
      Serial.println("liga pisca alerta");
      flag = 1;
    }
  }
  else if (state == 'x')
  {
    desligaPiscaAlerta();
    if (flag == 0)
    {
      Serial.println("desliga pisca alerta");
      flag = 1;
    }
  }  
}

void back()
{
  //MOTOR 1
  //analogWrite(ENA, 1000);  //Motor com rotação máxima (0-255)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  //MOTOR 2
  //analogWrite(ENB, 1000);  //Motor com rotação máxima (0-255)
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void fwd()
{
  //MOTOR 1
  //analogWrite(ENA, 1000);  //Motor com rotação máxima (0-255)
  digitalWrite(IN1, LOW);   //desligo 8
  digitalWrite(IN2, HIGH);  //ligo 9

  //MOTOR 2
  //analogWrite(ENB, 1000);  //Motor com rotação máxima (0-255)
  digitalWrite(IN3, LOW);   //desligo 10
  digitalWrite(IN4, HIGH);  //ligo 11
}

void left()
{
  //MOTOR 1
  //analogWrite(ENA, 1000);  //Motor com rotação máxima (0-255)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  //MOTOR 2
  //analogWrite(ENB, 1000);  //Motor com rotação máxima (0-255)
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void right()
{
  //MOTOR 1
  //analogWrite(ENA, 1000);  //Motor com rotação máxima (0-255)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  //MOTOR 2
  //analogWrite(ENB, 1000);  //Motor com rotação máxima (0-255)
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void stp()            // Robot STops
{
  //MOTOR 1
  //analogWrite(ENA, 1000);  //Motor com rotação máxima (0-255)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  //MOTOR 2
  //analogWrite(ENB, 1000);  //Motor com rotação máxima (0-255)
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void ligaLuz()
{
  digitalWrite(pinLed1, HIGH);   // set the LED on
}

void desligaLuz()
{
  digitalWrite(pinLed1, LOW);    // set the LED off
}

void ligaLuzTraseira()
{
  digitalWrite(pinLed2, HIGH);   // set the LED on
}

void desligaLuzTraseira()
{
  digitalWrite(pinLed2, LOW);    // set the LED off
}

void ligaBuzina(){
  tone(pinBuzzer,200);  
}

void desligaBuzina(){
  noTone(pinBuzzer);
}

void ligaPiscaAlerta()
{
  for (int i = 0; i <= 5; i++) {
    digitalWrite(pinLed1, HIGH);   // set the LED on
    delay(500);
    digitalWrite(pinLed1, LOW);   // set the LED on
    delay(500);    
  }  
}

void desligaPiscaAlerta()
{
  digitalWrite(pinLed1, LOW);   // set the LED on  
}

void testeMotores() {

  Serial.println("frente");
  fwd();
  delay(2000);
  Serial.println("stp");
  stp();
  delay(2000);
  Serial.println("ré");
  back();
  delay(2000);
  Serial.println("stp");
  stp();
  delay(2000);
}
