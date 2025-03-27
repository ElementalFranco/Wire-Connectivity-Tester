#ifndef MIC_CONNECTOR_H
#define MIC_CONNECTOR_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd; //mainProg 

void checkvalue6wire(int state[]) {
  lcd.clear();
  for (int i = 0; i < 3; i++) {
    lcd.setCursor(0, i);
    if (state[i] == 1) {
      lcd.print(i + 1);
      lcd.print(": Pair Connected");
    } else {
      lcd.print(i + 1);
      lcd.print(": Pair NC");
    }
  }

  delay(2500);

  if (state[0] == 1 && state[1] == 1 && state[2] == 1) {
    lcd.clear();
    lcd.setCursor(0, 1);                    //(COL, ROW)
    lcd.print("All 6 pins are");
    lcd.setCursor(0, 2);                    //(COL, ROW)
    lcd.print("CONNECTED!");
    lcd.setCursor(0, 3);
    lcd.print("Gosh, finally!");
  } else if (state[0] == 0 && state[1] == 1 && state[2] == 1) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Check pin 1 or pin 6");
  } else if (state[0] == 1 && state[1] == 0 && state[2] == 1) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Check pin 2 or pin 4");
  } else if (state[0] == 1 && state[1] == 1 && state[2] == 0) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Check pin 3 or pin 5");
  } else {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Check the entire wire assembly");
  }

  delay(3000);
}

#endif
