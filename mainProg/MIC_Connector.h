#include <Arduino.h>  // Include for Serial.print
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd; //Use existing LCD object from mainProg

void checkvalue6wire(int state[]){

  lcd.clear();
  for(int i = 0; i < 3; i++){
    lcd.setCursor(0, i);
    if(state[i] == 1)
    { 
      lcd.print(i+1); // Counting from 1 based on connector pin numbering
      lcd.print(": Pair Connected");
    }
    else
    {
      lcd.print(i+1); // Counting from 1 based on connector pin numbering
      lcd.print(": Pair not connected");
    }
  }
  delay(2500);
  if (state[0] == 1 && state[1] == 1 && state[2] == 1)
  { 
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("All 6 pins are connected");
    delay(3000);
  }
  else if (state[0] == 0 && state[1] == 1 && state[2] == 1)
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Check pin 1 or pin 6");
    delay(3000);
  }
  else if (state[0] == 1 && state[1] == 0 && state[2] == 1)
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Check pin 2 or pin 4");
    delay(3000);
  }
  else if (state[0] == 1 && state[1] == 1 && state[2] == 0)
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Check pin 3 or pin 5");
    delay(3000);
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Check the entire wire assembly");
    delay(3000);
  }

}