#include "PongRandColor.h"
#include "../LEDController.h"

PongRandColor::PongRandColor() { }

void PongRandColor::setup(CHSV leds[]) {
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

void PongRandColor::destroy(CHSV leds[]) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].v = 0;
    }
    destroyed = true;
}

void PongRandColor::loop(CHSV leds[]) {
    leds[currentLED].v = 0;
    if (pongReverse) {
        currentLED--;
    } else {
        currentLED++;
    }
    leds[currentLED].v = 255;
    if (currentLED <= 0) {
        pongReverse = false;
        uint8_t hue = random8();
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i].h = hue;
        }
    } else if (currentLED >= NUM_LEDS) {
        pongReverse = true;
        uint8_t hue = random8();
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i].h = hue;
        }
    }

    delay(50);
}