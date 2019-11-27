#include "Fade.h"
#include "../LEDController.h"

Fade::Fade() { }

void Fade::destroy(CHSV leds[], uint8_t fht[], uint8_t max) {
    bool maxBrightness = true;
    for (int i = 0; i < NUM_LEDS; i++) {
        if (leds[i].v != 0) {
            leds[i].v--;
            maxBrightness = false;
        }
    }

    if (maxBrightness) {
        destroyed = true;
    }
}

void Fade::loop(CHSV leds[], uint8_t fht[], uint8_t max) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].v = (fadeReverse) ? leds[i].v - 1 : leds[i].v + 1;
    }
    if (leds[0].v == 255) {
        fadeReverse = true;
    } else if (leds[0].v == 0) {
        fadeReverse = false;
    }
}