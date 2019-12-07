#include "LEDController.h"

#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define BRIGHTNESS 64

CHSV leds[NUM_LEDS];
CRGB c[NUM_LEDS];
unsigned long lastMills;

LEDController::LEDController() {
    FastLED.addLeds<LED_TYPE, PIN, COLOR_ORDER>(c, NUM_LEDS);
    FastLED.setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    lastMills = millis();

    /*//FastLED.setDither(false);
    FastLED.setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 1500);
    set_max_power_indicator_LED(13);
    lastMills = millis();*/
}

void LEDController::setEffect(IEffect *effect) {
    if (previousEffect != NULL) {
        delete previousEffect;
    }
    previousEffect = this->effect;
    this->effect = effect;
    isSet = false;
}

bool LEDController::loop(unsigned long mills, int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc) {
    if (previousEffect != NULL && !previousEffect->isDestroyed()) {
        if (previousEffect->canLoop(mills - lastMills)) {
            previousEffect->destroy(leds, fft, peak, peakBin, recalc);
            lastMills = mills;
            display();
            return true;
        }
    } else {
        isSet = true;
        if (effect->canLoop(mills - lastMills)) {
            effect->loop(leds, fft, peak, peakBin, recalc);
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