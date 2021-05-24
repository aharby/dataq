#include "max6675.h"  //INCLUDE THE LIBRARY


#include "LiquidCrystal_I2C.h"
#include "Wire.h"


int thermoDO = 9;
int thermoCS = 8;
int thermoCLK = 13;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);


LiquidCrystal_I2C lcd(0x27, 16, 2);
int relayPin = 7;
float T= 0; // temperature (C)
float sec_time;    //variable to hold the time

void setup() {

 
 
  pinMode (relayPin, OUTPUT);
  
  lcd.init();
  lcd.backlight();

 Serial.begin(9600);
  Serial.println("CLEARDATA");
  Serial.println("LABEL,CLOCK,t(sec),T(C)");
  // wait for MAX chip to stabilize
  delay(500);

  
}

void loop() {
  // basic readout test, just print the current temp  

 T = thermocouple.readCelsius();

  sec_time = ((millis())/1000.00);
  Serial.print("DATA,TIME,");
  Serial.print(sec_time);
  Serial.print(",");
  Serial.println(T);
 
  lcd.setCursor(0,0);
  // tell the screen to write “hello, from” on the top row
  lcd.print("Temp (C)");
  // tell the screen to write on the bottom row
  lcd.setCursor(0,1);
  lcd.print(T);

  
  if (T< 22){
    digitalWrite (relayPin, HIGH);
  }
  else{
    digitalWrite (relayPin, LOW);
  }

   delay(500);
}
