#include "FadeRandColor.h"
#include "../LEDController.h"

FadeRandColor::FadeRandColor() { }

void FadeRandColor::destroy(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc) {
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

void FadeRandColor::loop(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].v = (fadeReverse) ? leds[i].v - 1 : leds[i].v + 1;
    }
    if (leds[0].v == 255) {
        fadeReverse = true;
    } else if (leds[0].v == 0) {
        fadeReverse = false;
        uint8_t hue = random8();
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i].h = hue;
        }
    }
}