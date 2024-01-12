#include <Arduino.h>
#include "A4988.h"

const int knop = 53;
const int knop_nc = 52;
const int beginschakelaar = 51; 
const int beginschakelaar_nc = 49; 
int buttonState = 0;
int buttonState_nc = 1; 
int buttonState_eind = 0; 
int buttonState_eind_nc = 1; 


int Step = 3; //GPIO14---D5 of Nodemcu--Step of stepper motor driver
int Dire  = 2; //GPIO2---D4 of Nodemcu--Direction of stepper motor driver
int Sleep = 4; //GPIO12---D6 of Nodemcu-Control Sleep Mode on A4988
int MS1 = 7; //GPIO13---D7 of Nodemcu--MS1 for A4988
int MS2 = 6; //GPIO16---D0 of Nodemcu--MS2 for A4988
int MS3 = 5; //GPIO15---D8 of Nodemcu--MS3 for A4988

int Step_2 = 9; //GPIO3 in Arduino UNO --- Step of stepper motor driver
int Dire_2  = 8; //GPIO2 in Arduino UNO --- Direction of stepper motor driver
int Sleep_2 = 10; //GPIO4 in Arduino UNO --- Control Sleep Mode on A4988
int MS1_2 = 13; //GPIO7 in Arduino UNO --- MS1 for A4988
int MS2_2 = 12; //GPIO6 in Arduino UNO --- MS2 for A4988
int MS3_2 = 11; //GPIO5 in Arduino UNO --- MS3 for A4988

//Motor pecs
const int spr = 200; //Steps per revolution
int RPM = 375; //Motor Speed in revolutions per minute
int Microsteps = 16; //Stepsize (1 for full steps, 2 for half steps, 4 for quarter steps, etc)

const int spr_2 = 200; //Steps per revolution
int RPM_2 = 100; //Motor Speed in revolutions per minute
int Microsteps_2 = 16; //Stepsize (1 for full steps, 2 for half steps, 4 for quarter steps, etc)

//Providing parameters for motor control
A4988 stepper(spr, Dire, Step, MS1, MS2, MS3);
A4988 stepper_2(spr_2, Dire_2, Step_2, MS1_2, MS2_2, MS3_2);

void setup() {


  Serial.begin(9600);
  pinMode(Step, OUTPUT); //Step pin as output
  pinMode(Dire,  OUTPUT); //Direcction pin as output
  pinMode(Sleep,  OUTPUT); //Set Sleep OUTPUT Control button as output
  digitalWrite(Step, LOW); // Currently no stepper motor movement
  digitalWrite(Dire, LOW);
  digitalWrite(Sleep, HIGH); //A logic high allows normal operation of the A4988 by removing from sleep
  delay(1000);//Wait 1000 milliseconds (1 second) proceeding
  // Set target motor RPM to and microstepping setting
  stepper.begin(RPM, Microsteps);

    Serial.begin(9600);
  pinMode(Step_2, OUTPUT); //Step pin as output
  pinMode(Dire_2,  OUTPUT); //Direcction pin as output
  pinMode(Sleep_2,  OUTPUT); //Set Sleep OUTPUT Control button as output
  digitalWrite(Step_2, LOW); // Currently no stepper motor movement
  digitalWrite(Dire_2, LOW);
  digitalWrite(Sleep_2, HIGH); //A logic high allows normal operation of the A4988 by removing from sleep
  delay(1000);//Wait 1000 milliseconds (1 second) proceeding
  // Set target motor RPM to and microstepping setting
  stepper_2.begin(RPM_2, Microsteps);

  pinMode(knop, INPUT);
  pinMode(knop_nc, INPUT);
  pinMode(beginschakelaar, INPUT); 
  pinMode(beginschakelaar_nc, INPUT); 
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}
 
void loop() {
  buttonState = digitalRead(knop);
  buttonState_nc = digitalRead(knop_nc);
  buttonState_eind = digitalRead(beginschakelaar); 
  buttonState_eind_nc = digitalRead(beginschakelaar_nc); 


  if( digitalRead(knop) == 1 && digitalRead(knop_nc) == 0){
    while( digitalRead(beginschakelaar) == 0 && digitalRead(beginschakelaar_nc) == 1 ){
    stepper.move(-48);// initialisatie stap
    Serial.print("Beginschakelaar is niet ingedruk\n");
  }
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    Serial.print("Aan\n");
    digitalWrite(Sleep, HIGH); //A logic high allows normal operation of the A4988 by removing from sleep
    stepper.move(1040*16);//Move 400 steps clockwise
    delay(100);//Wait 1000 milliseconds (1 second) before moving again
    
   
    digitalWrite(Sleep, HIGH); //A logic high allows normal operation of the A4988 by removing from sleep
    stepper_2.move(1040*16);//Move 400 steps clockwise
    delay(100);//Wait 1000 milliseconds (1 second) before moving again
    stepper_2.move(-1040*16);//Move 400 steps counter-clockwise
    delay(100);//Wait 1000 milliseconds (1 second) before moving again
    stepper.move(-1040*16);//Move 400 steps counter-clockwise
    delay(100);//Wait 1000 milliseconds (1 second) before moving again
    delay(100);
  }

  else if( digitalRead(knop) == 0 && digitalRead(knop_nc) == 1){
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(100);
  Serial.print("Uit\n");
  }      
   
}
 
