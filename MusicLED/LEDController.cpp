#include "LEDController.h"

#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define BRIGHTNESS 64

CRGB leds[NUM_LEDS];

LEDController::LEDController() {
    FastLED.addLeds<LED_TYPE, PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
}

void LEDController::setLED(int led, CRGB color) {
    if (led >= NUM_LEDS || led < 0) {
        return;
    }

    leds[led] = color;
    FastLED.show();
}

void LEDController::setLED(int led, CHSV hue) {
    setLED(led, CRGB(hue));
}

void LEDController::clear(CRGB color) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = color;
    }
    FastLED.show();
}

void LEDController::clear(CHSV hue) {
    clear(CRGB(hue));
}