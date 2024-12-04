#include <FastLED.h>
#include "turnLedON.h"

//Define the pins where the relay modules are connected
const int relayPins[] = {2, 3, 4, 5, 6,}; //Green - White - Blue - Red - Black
const int numRelays = sizeof(relayPins) / sizeof(relayPins[0]); //Calculate the number of relays

//Define LED Parameters
#define numLeds 2
#define DATA_PIN_1 7
#define DATA_PIN_2 8
#define DATA_PIN_3 9
#define DATA_PIN_4 10
#define DATA_PIN_5 11

CRGB leds1[numLeds];
CRGB leds2[numLeds];
CRGB leds3[numLeds];
CRGB leds4[numLeds];
CRGB leds5[numLeds];


void setup() {
  for (int i = 0; i < numRelays; i++){
    pinMode(relayPins[i], OUTPUT); //Initialize each relay pin as output
    digitalWrite(relayPins[i], LOW); //All relays are turned off
  }
    //FastLED.addLeds<WS2811, DATA_PIN_1, RGB>(leds1, numLeds);
    FastLED.addLeds<WS2811, DATA_PIN_2, RGB>(leds2, numLeds);
    FastLED.addLeds<WS2811, DATA_PIN_3, RGB>(leds3, numLeds);
    FastLED.addLeds<WS2811, DATA_PIN_4, RGB>(leds4, numLeds);
    FastLED.addLeds<WS2811, DATA_PIN_5, RGB>(leds5, numLeds);
   
}
  

void loop() {
  for (int i = 0; i < numRelays; i++){
    digitalWrite(relayPins[i], HIGH); //Activate relay
    //Pin 2 of UUT
    for (int i = 0; i < numLeds; i++) {
      leds1[i] = CRGB::Green;
    }
    FastLED.show(); 
    delay(500);
    //Pin 3 of UUT
    for (int i = 0; i < numLeds; i++) {
    leds2[i] = CRGB::White;
    }
    FastLED.show(); 
    delay(500);
    //Pin 3 of UUT
    for (int i = 0; i < numLeds; i++) {
    leds3[i] = CRGB::Blue;
    }
    FastLED.show(); 
    delay(500);
    //Pin 4 of UUT
    for (int i = 0; i < numLeds; i++) {
    leds4[i] = CRGB::Red;
    }
    FastLED.show(); 
    delay(500);
    //Pin 5 of UUT
    for (int i = 0; i < numLeds; i++){
      leds5[0] = CRGB::Green;
      leds5[i] = CRGB::Gray;
    }
    FastLED.show(); 
    delay(500);

  }
}
