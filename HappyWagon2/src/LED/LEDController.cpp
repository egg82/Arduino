#include "LEDController.h"

#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define BRIGHTNESS 64

CHSV leds[NUM_LEDS];
CRGB c[NUM_LEDS];
unsigned long lastMills;

LEDController::LEDController() {
    FastLED.addLeds<LED_TYPE, PIN, COLOR_ORDER>(c, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    lastMills = millis();
}

void LEDController::setEffect(IEffect *effect) {
    if (previousEffect != NULL) {
        delete previousEffect;
    }
    previousEffect = this->effect;
    this->effect = effect;
}

bool LEDController::loop(unsigned long mills, uint8_t fht[]) {
    if (previousEffect != NULL && !previousEffect->isDestroyed()) {
        if (previousEffect->canLoop(mills - lastMills)) {
            previousEffect->destroy(leds);
            lastMills = mills;
            display();
            return true;
        }
    } else {
        if (effect->canLoop(mills - lastMills)) {
            if (!effect->isSetup()) {
                effect->setup(leds);
            } else {
                effect->loop(leds);
            }
            lastMills = mills;
            display();
            return true;
        }
    }
    return false;
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