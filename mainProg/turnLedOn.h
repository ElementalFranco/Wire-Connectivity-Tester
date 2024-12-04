#include <FastLED.h>

void TurnLedOn(CRGB* leds, int CP){
  for (int i = 0; i < CP; i++){
    leds[i] = CRGB::Red;
  }
  FastLED.show();
  delay(1000);

  for (int i = 0; i < CP; i++){
    leds[i] = CRGB::Blue;
  }
  FastLED.show();
  delay(1000);
}