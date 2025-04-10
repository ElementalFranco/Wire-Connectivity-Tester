#ifndef MIC_CONNECTOR_H
#define MIC_CONNECTOR_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Wire.h>
#include "KeyPadControl.h"
char* userResponse;
int userResponseInt = 0;

extern LiquidCrystal_I2C lcd; //mainProg 

void RGBW_5wire(int state[]) {
  
  lcd.clear();
  lcd.setCursor(1, 1);                //(COL, ROW)
  lcd.print("Is Pin6 connected");
  lcd.setCursor(0, 2);
  lcd.print("w/ black wire color?");
  lcd.setCursor(3, 3);
  lcd.print("1: Yes | 2: No");
  userResponse = processKeypad(); // Process user input
  userResponseInt = atoi(userResponse); // Converts string from keypad into integer
  if(userResponseInt == 1)
  {
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print("Ok! Next..");
    delay(500);
    lcd.setCursor(3, 2);
    lcd.print("Is pin1 empty?");
    lcd.setCursor(4, 3);
    lcd.print("1-Yes | 2-No");
    userResponse = processKeypad(); // Process user input
    userResponseInt = atoi(userResponse); // Converts string from keypad into integer
    if (userResponseInt == 1)
    {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("oh Yeah! Wait...");
      lcd.setCursor(0, 2);
      lcd.print("Im checking..");
      delay(1500);
    }
    else if (userResponseInt == 2)
    {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Ayy! Recheck Pin5");
      lcd.setCursor(0, 2);
      lcd.print("Fix your cable!");
      delay(5000);
      lcd.clear();
      lcd.setCursor(3, 2);
      lcd.print("Is pin1 empty?");
      lcd.setCursor(4, 3);
      lcd.print("1-Yes | 2-No");
      userResponse = processKeypad(); // Process user input
      userResponseInt = atoi(userResponse); // Converts string from keypad into integer
      switch (userResponseInt){
        case 1: 
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Great! Verifying..");
        delay(1500);
        break;

        case 2:
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Again? Grrr");
        lcd.setCursor(0, 2);
        lcd.print("Restarting...");
        delay(1500);
        asm volatile("jmp 0"); //Soft restart

        case 3: 
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Pressed the ");
        lcd.setCursor(0, 2);
        lcd.print("wrong button!!");
        lcd.setCursor(0, 3);
        lcd.print("Restarting..");
        delay(1500);
        asm volatile("jmp 0"); //Soft restart
      }
    }
  else if (userResponse == 2)
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Fix it then!");
    delay(5000);
    lcd.setCursor(3, 2);
    lcd.print("Is pin1 empty?");
    lcd.setCursor(4, 3);
    lcd.print("1-Yes | 2-No");
    userResponse = processKeypad(); // Process user input
    userResponseInt = atoi(userResponse); // Converts string from keypad into integer
        switch (userResponseInt){
        case 1: 
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Great! Verifying..");
        delay(1500);
        break;

        case 2:
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Call Franco! JK");
        lcd.setCursor(0, 2);
        lcd.print("Restarting...");
        delay(1500);
        asm volatile("jmp 0"); //Soft restart

        case 3: 
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("No bueno");
        lcd.setCursor(0, 2);
        lcd.print("my friend!");
        lcd.setCursor(0, 3);
        lcd.print("Restarting..");
        delay(1500);
        asm volatile("jmp 0"); //Soft restart
        }
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Wrong button");
      lcd.setCursor(0, 2);
      lcd.print("my friend!");
      lcd.setCursor(0, 3);
      lcd.print("Restarting..");
      delay(1500);
      asm volatile("jmp 0"); //Soft restart
    }
  delay(2500);

    /* Array of LED state -- 0: OFF | 1: ON  */
    /* ledState = {#, #, #}                  */
    /* ledPins = {D8, D9, D10}               */
    /* rxPins = {D7(Pin6), D6(Pin5), D3(Pin2)}  */
    /* txPins = {D2(Pin1), D4(Pin3), D5(Pin4)}  */
  if (state[0] == 0 && state[1] == 1 && state[2] == 1) {
    lcd.clear();
    lcd.setCursor(0, 1);                    //(COL, ROW)
    lcd.print("All 5 pins are");
    lcd.setCursor(0, 2);                    //(COL, ROW)
    lcd.print("CONNECTED!");
    lcd.setCursor(0, 3);
    lcd.print("Gosh, finally!");
    delay(4000);
  } else if (state[0] == 1 && state[1] == 1 && state[2] == 1) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Check pin 1 or pin 6");
  } else if (state[0] == 0 && state[1] == 0 && state[2] == 1) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Check pin 5 or pin 3");
  } else if (state[0] == 0 && state[1] == 1 && state[2] == 0) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Check pin 2 or pin 4");
  } else {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Check all wires");
  }
  delay(3000);
}
}

void RGB_4Std() 
{
  //Rearranging I/O ports because the pairs are not compatible with default/original values
    /* Array of LED state -- 0: OFF | 1: ON  */
    /* ledState = {#, #, #}                  */
    /* ledPins = {D8, D9, D10}               */
    /* rxPins = {D7(Pin6), D6(Pin5), D4(Pin3)}  */
    /* txPins = {D3(Pin2), D5(Pin4), D2(Pin1)}  */

  const int led_Pins[] = {8, 9};   // Indicator pins to set HIGH on connection acquired
  const int rx_Pins[] = {7, 6};     // RX pins (expected loopback pins)
  const int tx_Pins[] = {3, 5};     // TX pins (connected to active connector pins)
  const int extraLed_Pins[] = {10};  // 3rd LED 
  const int emptyPins[] = {2, 4};   //Testing Empty Pins
  int led_State[3] = {}; 


      // Set TX/ledPins pins as OUTPUT
  for (int i = 0; i < 3; i++) {
    pinMode(tx_Pins[i], OUTPUT);
    digitalWrite(tx_Pins[i], LOW);  // Start with LEDs OFF
    pinMode(led_Pins[i], OUTPUT);
    digitalWrite(led_Pins[i], LOW);  // Start with LEDs OFF
    pinMode(emptyPins[i], OUTPUT);
    digitalWrite(emptyPins[i], LOW);
  }
  delay(50);

      // Set RX pins as INPUT
  for (int i = 0; i < 3; i++) {
    pinMode(rx_Pins[i], INPUT);
    digitalWrite(rx_Pins[i], LOW);
  }
  delay(50);

  /* Array of LED state -- 0: OFF | 1: ON  */
  /* ledState = {#, #, #}                  */
  /* ledPins = {D8, D9, D10}               */
    /* rxPins = {D4(Pin3), D6(Pin5), D3(Pin2)}  */
    /* txPins = {D2(Pin1), D7(Pin6), D5(Pin4)}  */

  lcd.clear();
  lcd.setCursor(0, 1);                //(COL, ROW)
  lcd.print("Is Pin 1 and");
  lcd.setCursor(0, 2);
  lcd.print("Pin 3 empty?");
  lcd.setCursor(3, 3);
  lcd.print("1: Yes | 2: No");
  userResponse = processKeypad(); // Process user input
  userResponseInt = atoi(userResponse); // Converts string from keypad into integer

  if(userResponseInt == 1)
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Great! Will see!!");
    delay(1000);

    //Testing LEDs
    // digitalWrite(led_Pins[1], HIGH); //0 D8 || 1 D9 || 2 D10
    // delay(5000);

    //Make TX PINs HIGH 
    for (int i = 0; i < 3; i++) {
      digitalWrite(tx_Pins[i], HIGH); //Turn all TX Pins to HIGH - Pin 2, 7, 5
    }
    delay(50);  // Small delay to reduce CPU Usage

    //Read if RX PINs are HIGH - Turn the LEDs ON
    for (int i = 0; i < 3; i++)
    {
      if (digitalRead(rx_Pins[i]) == HIGH) // Pins 4, 6, 3 
      {
        digitalWrite(led_Pins[i], HIGH); // Pins 8, 9, 10 
        delay(500);
      }
      else
      {
      digitalWrite(led_Pins[i], LOW); // Pins 8, 9, 10
      delay(500);
      }
    }

    //Test Empty Pins
    if (digitalRead(emptyPins[0]) == HIGH)
    {
      digitalWrite(extraLed_Pins[0], HIGH);
    }
    else
    {
      digitalWrite(extraLed_Pins[0], LOW);
    }

  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Ayy! Recheck Pin");
    delay(500);
    lcd.setCursor(0, 2);
    lcd.print("Restarting again");
    delay(5000);
    asm volatile("jmp 0"); //Soft restart
  }
  delay(2500);

  for (int i = 0; i < 3; i++){
    if (digitalRead(led_Pins[i]) == HIGH)
    {
      led_State[i] = 1;
      delay(50);
    }
    else
    {
      led_State[i] = 0;
      delay(50);
    }
  }

    /* Array of LED state -- 0: OFF | 1: ON  */
    /* ledState = {#, #, #}                  */
    /* ledPins = {D8, D9, D10}               */
    /* rxPins = {D4(Pin3), D6(Pin5), D3(Pin2)}  */
    /* txPins = {D2(Pin1), D7(Pin6), D5(Pin4)}  */
    if (led_State[0] == 1 && led_State[1] == 1 && led_State[2] == 0) {
    lcd.clear();
    lcd.setCursor(0, 1);                    //(COL, ROW)
    lcd.print("All 4 pins are");
    lcd.setCursor(0, 2);                    //(COL, ROW)
    lcd.print("CONNECTED!");
    lcd.setCursor(0, 3);
    lcd.print("Gosh, finally!");
    delay(1500);
  } else if (led_State[0] == 0 && led_State[0] == 1 && led_State[2] == 1) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Chk pin 1&3 or 4&2");
    delay(1500);
  } else {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Check the entire");
    lcd.setCursor(0, 2);
    lcd.print("wire assembly!");
    delay(3000);
  }
}

void RGB_4Kiosk(int state[]) 
{
  lcd.clear();
  lcd.setCursor(1, 1);
  lcd.print("Nothing yet!");
  lcd.setCursor(1, 2);
  lcd.print("Restarting... bye!");
  delay(2000);
  asm volatile("jmp 0"); //Soft restart
}

void TW_3Wire(int state[]) 
{
  lcd.clear();
  lcd.setCursor(1, 1);                //(COL, ROW)
  lcd.print("Is Pin5 connected");
  lcd.setCursor(0, 2);
  lcd.print("w/ YW/RD wire color?");
  lcd.setCursor(3, 3);
  lcd.print("1: Yes | 2: No");
  userResponse = processKeypad(); // Process user input
  userResponseInt = atoi(userResponse); // Converts string from keypad into integer
  if(userResponseInt == 1)
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Pin5 Connected");
    delay(1500);
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Ayy! Recheck Pin5");
    delay(1500);
    lcd.setCursor(0, 2);
    lcd.print("Restarting again");
    delay(1500);
    asm volatile("jmp 0"); //Soft restart
  }
  
  delay(2500);

    /* Array of LED state -- 0: OFF | 1: ON     */
    /* ledState = {#, #, #}                     */
    /* ledPins = {D8, D9, D10}                  */
    /* rxPins = {D7(Pin6), D6(Pin5), D3(Pin2)}  */
    /* txPins = {D5(Pin4), NC, NC)}             */
    if (state[0] == 1 && state[1] == 0 && state[2] == 0) {
    lcd.clear();
    lcd.setCursor(0, 1);                    //(COL, ROW)
    lcd.print("All 3 pins are");
    lcd.setCursor(0, 2);                    //(COL, ROW)
    lcd.print("CONNECTED!");
    lcd.setCursor(0, 3);
    lcd.print("Gosh, finally!");
    delay(4000);
  } else if (state[0] == 1 && state[1] == 1 && state[2] == 0) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Check pin 5");
  } else if (state[0] == 0 && state[1] == 0 && state[2] == 0) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Check pin 4 or pin 6");
  } else {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Check the entire wire assembly");
  }
}

#endif
