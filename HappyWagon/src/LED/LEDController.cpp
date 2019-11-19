#include "LEDController.h"

#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define BRIGHTNESS 64

CHSV leds[NUM_LEDS];
CRGB c[NUM_LEDS];
IEffect LEDController::*effect = NULL;
IEffect LEDController::*previousEffect = NULL;

LEDController::LEDController() {
    FastLED.addLeds<LED_TYPE, PIN, COLOR_ORDER>(c, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
}

void LEDController::setEffect(IEffect *effect) {
    this->previousEffect = this->effect;
    this->effect = effect;
}

void LEDController::loop() {
    if (previousEffect != NULL && !previousEffect->isDestroyed()) {
        previousEffect->destroy(leds);
    } else {
        if (!effect->isSetup()) {
            effect->setup(leds);
        } else {
            effect->loop(leds);
        }
    }
    display();
}

void LEDController::clear(CHSV color) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = color;
        c[i] = CRGB(color);
    }
    FastLED.show();
}

void LEDController::display() {
    for (int i = 0; i < NUM_LEDS; i++) {
        c[i] = CRGB(leds[i]);
    }
    FastLED.show();
}