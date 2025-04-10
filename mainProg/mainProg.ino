
/***********************************************
Title: Wire connectivity and Pinning Test Kit  
Author: Franco Nepomuceno                      
Date: 12/11/2024                               
Rev: Draft                                     
***********************************************/
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Wire.h>
#include "KeyPadControl.h"
#include "MIC_Connector.h"
#include "wireSelection.h"
char* wireSelectInput;
int WSint = 0;
int WSint_2 = 0;

LiquidCrystal_I2C lcd(0x27, 20, 4);   // Set the LCD address to 0x3F for 20 chars

/*********************
Pin1: D2
Pin2: D3 (Green)
Pin3: D4
********
Pin4: D5
Pin5: D6 (Red)
Pin6: D7 (Black)
********
//Combination
D2(Pin1) -> D7(Pin6)
D5(Pin4) -> D3(Pin2) 
D4(Pin3) -> D6(Pin5) 
**********************/

const int txPins[] = {2, 4, 5};     // TX pins (connected to active connector pins)
const int rxPins[] = {7, 6, 3};     // RX pins (expected loopback pins)
const int ledPins[] = {8, 9, 10};   // Indicator pins to set HIGH on connection acquired
int ledState[3] = {}; 

void setup() {

  lcd.init();                                           // Initialize the LCD
  lcd.backlight();                                      // Turn on the backlight

  // Start Serial and set-up --> Welcome Screen
  Serial.begin(9600);
  lcd.clear();
  lcd.setCursor(3, 1);                                  //LCD --> (COLUMN, ROW)
  lcd.print("Welcome to the");
  lcd.setCursor(3, 2);
  lcd.print("Wire Test Kit");
  lcd.setCursor(8, 3);
  lcd.print("Rev A");                                   //Change if revised
  delay(6000);
  lcd.clear();
  
  // Set RX pins as INPUT
  for (int i = 0; i < 3; i++) {
      pinMode(rxPins[i], INPUT);
  }

  // Set TX pins as OUTPUT
  for (int i = 0; i < 3; i++) {
      pinMode(txPins[i], OUTPUT);
      pinMode(ledPins[i], OUTPUT);
      digitalWrite(txPins[i], LOW);  // Start with LEDs OFF
      digitalWrite(ledPins[i], LOW);
  }
  
  selection_1(); // Show user directions
  delay(500);
  selection_2(); // Show choices to user
  wireSelectInput = processKeypad(); // Process user input
  WSint = atoi(wireSelectInput); // Converts string from keypad into integer

  if (WSint == 2) // look at the wireSelection header file for types of 4 wire
  {
    RGB4WireSelect();
    wireSelectInput = processKeypad(); // Process user input
    WSint_2 = atoi(wireSelectInput); // Converts string from keypad into integer
  }
}

void loop() 
{
    for (int i = 0; i < 3; i++){
      digitalWrite(ledPins[i], LOW); //Reset - all LEDs OFF
      digitalWrite(rxPins[i], LOW); //Reset - all RX pins LOW
      digitalWrite(txPins[i], LOW); //Reset - all TX pins LOW
     }
     delay(75);

    // //Testing TX PINS -- Manually
    // digitalWrite(txPins[1], HIGH);

    //Make TX PINs HIGH 
    for (int i = 0; i < 3; i++) {
      digitalWrite(txPins[i], HIGH); //Turn all TX Pins to HIGH - Pin 2, 4, 5
    }
    delay(50);  // Small delay to reduce CPU usage

    // // Testing -- LEDs right to left 8, 9 10 visually -- Look at the LEDs 
    // for (int i = 0; i < 3; i++) {
    // digitalWrite(ledPins[i], HIGH);
    // delay(500);
    // digitalWrite(ledPins[i], LOW);
    // delay(500);
    // }

    // //Testing RX Pins -- Manually
    // for (int i = 0; i < 3; i++){
    // digitalWrite(rxPins[i], HIGH);
    // }
  
  //Read if RX PINs are HIGH - Turn the LEDs ON
    for (int i = 0; i < 3; i++)
    {
      if (digitalRead(rxPins[i]) == HIGH) // Pins 7, 6, 3 
      {
        digitalWrite(ledPins[i], HIGH); // Pins 8, 9, 10 
        delay(1000);
      }
      else
      {
      digitalWrite(ledPins[i], LOW); // Pins 8, 9, 10
      delay(500);
      }
    }
    delay(50);

    memset(ledState, 0, sizeof(ledState)); // Zero out all elements

    /* Array of LED state -- 0: OFF | 1: ON  */
    /* ledState = {#, #, #}                  */
    /* ledPins = {D8, D9, D10}               */
    /* rxPins = {D7(Pin6), D6(Pin5), D3(Pin2)}  */
    /* txPins = {D2(Pin1), D4(Pin3), D5(Pin4)}  */

    for (int i = 0; i < 3; i++){
      if (digitalRead(ledPins[i]) == HIGH)
      {
        ledState[i] = 1;
        delay(50);
      }
      else
      {
        ledState[i] = 0;
        delay(50);
      }
    }

    switch(WSint){
      case 1: 
        RGBW_5wire(ledState);
        break;

      case 2:
        if (WSint_2 == 1)
        {
          RGB_4Std();
        }
        else
        {
          //Future Update
          RGB_4Kiosk(ledState);
        }
      break;

      case 3: 
        TW_3Wire(ledState);
        break;

      default:
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Wrong button!!");
        lcd.setCursor(0, 2);
        lcd.print("OMG! Restarting...");
        delay(1500);
        asm volatile("jmp 0"); //Soft restart
    }

    
}


