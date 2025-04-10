#ifndef WIRE_SELECTION_H
#define WIRE_SELECTION_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;//mainProg 

void selection_1() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("How many pins");
  lcd.setCursor(0, 1);
  lcd.print("are connected");
  lcd.setCursor(0, 2);
  lcd.print("Choices next page");
  lcd.setCursor(0, 3);
  lcd.print("Wait...");
  delay(1500);
}

void selection_2() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1: 5-Wire RGBW");
  lcd.setCursor(0, 1);
  lcd.print("2: 4-Wire -->");
  lcd.setCursor(0, 2);
  lcd.print("3: 3-Wire TW");
  lcd.setCursor(0, 3);
  lcd.print("Slct [1-3] & '#'");
}

void RGB4WireSelect() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1: Standard");
  lcd.setCursor(0, 1);
  lcd.print("2: KIOSK(FutureRev)");
  lcd.setCursor(0, 2);
  lcd.print("Slct [1-2] & '#'");
}

#endif
