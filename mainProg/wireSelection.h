/*Add wire type in the future*/

#include <wire.h>
#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd; //Use existing LCD object from mainProg

void selection_1()
{
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

void selection_2()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1: 6 connected");
  lcd.setCursor(0, 1);
  lcd.print("2: 5 connected");
  lcd.setCursor(0, 2);
  lcd.print("3: 4 connected");
  lcd.setCursor(0, 3);
  lcd.print("Select [1-3]");
}

