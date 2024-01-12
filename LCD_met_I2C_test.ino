#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//-----Hardware Adressierung-----
//Bei falscher Funktion bitte obere Zeile auskommentieren,
//und untere Zeile freigeben
LiquidCrystal_I2C lcd(0x27,20,4);
//LiquidCrystal_I2C lcd(0x27,20,4);
void setup()
{
 lcd.init();
}
void loop()
{
 lcd.backlight();
 //Nachricht ausgeben
 lcd.setCursor(0,0);
 lcd.print(" Rij 1");
 lcd.setCursor(0,1);
 lcd.print(" Rij 2");
}
