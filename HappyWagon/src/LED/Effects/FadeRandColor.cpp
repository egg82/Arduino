#include "FadeRandColor.h"
#include "../LEDController.h"

FadeRandColor::FadeRandColor() { }

void FadeRandColor::setup(CHSV leds[]) {
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

    delay(10);
}

void FadeRandColor::destroy(CHSV leds[]) {
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

    delay(10);
}

void FadeRandColor::loop(CHSV leds[]) {
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

    delay(10);
}