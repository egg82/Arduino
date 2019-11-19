#include "Blink.h"
#include "../LEDController.h"

Blink::Blink() { }

void Blink::setup(CHSV leds[]) {
    bool maxBrightness = true;
    for (int i = 0; i < NUM_LEDS; i++) {
        if (leds[i].s != 255) {
            leds[i].s++;
            maxBrightness = false;
        }
        if (leds[i].v != 0) {
            leds[i].v--;
            maxBrightness = false;
        }
    }

    if (maxBrightness) {
        isSet = true;
    }
}

void Blink::destroy(CHSV leds[]) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].v = 0;
    }
    destroyed = true;
}

void Blink::loop(CHSV leds[]) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].v = (leds[i].v == 255) ? 0 : 255;
    }
}