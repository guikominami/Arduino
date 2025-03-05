// Import the CapacitiveSensor Library.
#include <CapacitiveSensor.h>
#include "pitches.h"
#define speaker 11

// Set the Send Pin & Receive Pin.
CapacitiveSensor   cs_2_3 = CapacitiveSensor(2,3);        
CapacitiveSensor   cs_2_4 = CapacitiveSensor(2,4);         
CapacitiveSensor   cs_2_5 = CapacitiveSensor(2,5);     
CapacitiveSensor   cs_2_6 = CapacitiveSensor(2,6);     
CapacitiveSensor   cs_2_7 = CapacitiveSensor(2,7);      
CapacitiveSensor   cs_2_8 = CapacitiveSensor(2,8);         
//CapacitiveSensor   cs_2_9 = CapacitiveSensor(2,9);  
//CapacitiveSensor   cs_2_10 = CapacitiveSensor(2,10);     

int modo = 1; //modo = 1 (multiplicação de frequência)  modo = 2 (tecla de piano)

int buttonPin = 13;

int contador = 0;

int nota[] = {
    NOTE_B0,
    NOTE_C1,
    NOTE_D1,
    NOTE_E1,
    NOTE_F1,
    NOTE_G1,
    NOTE_A1,
    NOTE_B1,
    NOTE_C2,
    NOTE_D2,
    NOTE_E2,
    NOTE_F2,
    NOTE_G2,
    NOTE_A2,
    NOTE_B2,
    NOTE_C3,
    NOTE_D3,
    NOTE_E3,    
    NOTE_F3,    
    NOTE_G3,
    NOTE_A3,
    NOTE_B3,
    NOTE_C4,
    NOTE_D4,
    NOTE_E4,
    NOTE_F4,
    NOTE_G4,
    NOTE_A4,
    NOTE_B4,
    NOTE_C5,
    NOTE_D5,
    NOTE_E5,
    NOTE_F5,
    NOTE_D5,
    NOTE_G5,
    NOTE_A5,
    NOTE_B5,
    NOTE_C6,
    NOTE_D6,
    NOTE_F6,
    NOTE_G6,
    NOTE_A6,    
};

void setup()                    
{
  cs_2_3.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example

  pinMode(buttonPin, INPUT);
  
  // Arduino start communicate with computer.
  Serial.begin(9600);
}

void loop()                    
{
  // Set a timer.
  long start = millis();
  
  // Set the sensitivity of the sensors.
  long total1 =  cs_2_3.capacitiveSensor(30);
  long total2 =  cs_2_4.capacitiveSensor(30);
  long total3 =  cs_2_5.capacitiveSensor(30);
  long total4 =  cs_2_6.capacitiveSensor(30);
  long total5 =  cs_2_7.capacitiveSensor(30);
  long total6 =  cs_2_8.capacitiveSensor(30);
//  long total7 =  cs_2_9.capacitiveSensor(30);
//  long total8 =  cs_2_10.capacitiveSensor(3000);        

  Serial.println("total 1: "); // tab character for debug window spacing
  Serial.println(total1); // print sensor output 1
  Serial.println("total 2: "); // tab character for debug window spacing
  Serial.println(total2); // print sensor output 1  
  Serial.println("total 3: "); // tab character for debug window spacing
  Serial.println(total3); // print sensor output 1    
  Serial.println("total 4: "); // tab character for debug window spacing
  Serial.println(total4); // print sensor output 1    
  Serial.println("total 5: "); // tab character for debug window spacing
  Serial.println(total5); // print sensor output 1    
  Serial.println("total 6: "); // tab character for debug window spacing
  Serial.println(total6); // print sensor output 1    

  if (digitalRead(buttonPin) == HIGH) {

    //zerar o contador
    if (contador == 36){
      contador = 0;
    }
    else{
      contador = contador + 6; //vez 1      
    }

//    contador = 6; //vez 2
//    contador = 12; //vez 3
//    contador = 18; //vez 4
//    contador = 24; //vez 5
//    contador = 30; //vez 6
//    contador = 36; //vez 7

  }
    
  Serial.println("contador: ");
  Serial.println(contador);

  if (total1 > 200) 
  {
    tone(speaker,nota[0 + contador]);
  }
  else if (total2 > 200) 
  {
    tone(speaker,nota[1 + contador]);
  }
  else if (total3 > 200) 
  {
    tone(speaker,nota[2 + contador]);
  }
  else if (total4 > 200) 
  {
    tone(speaker,nota[3 + contador]);
  }
  else if (total5 > 200) 
  {
    tone(speaker,nota[4 + contador]);
  }
  else if (total6 > 200) 
  {
    tone(speaker,nota[5 + contador]);
  }
  else
  {
    noTone(speaker);
  }    

  delay(100);      

}
