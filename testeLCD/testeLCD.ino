#include <LiquidCrystal_I2C.h>

// -------------------- Display ----------------------------------------
//GND: Ligar na linha negativa
//VCC: Ligar na linha positiva
//SCL: A5
//SDA: A4
LiquidCrystal_I2C lcd(0x27,16,2);
// ---------------------------------------------------------------------

String nome = "Guilherme";
String idade = "43";

// A função setup é executada uma vez só
void setup() {

  Serial.begin(9600);

  lcd.init();
  
}

// A função loop fica sendo executada de maneira contínua
void loop() {

  delay (1000);

  mostraDadosLCD();

}

void mostraDadosLCD(){

  String texto;

  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  texto = "Nome: " + nome;
  lcd.print(texto);
  lcd.setCursor(0,1);
  texto = "Idade: " + idade + " anos";  
  lcd.print(texto);
  delay(1000);
  lcd.setBacklight(LOW);
  delay(1000);  

}
