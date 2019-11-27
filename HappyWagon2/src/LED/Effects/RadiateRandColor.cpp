#include "RadiateRandColor.h"
#include "../LEDController.h"

RadiateRandColor::RadiateRandColor() { }

void RadiateRandColor::destroy(CHSV leds[], uint8_t fht[], uint8_t max) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].v = 0;
    }
    destroyed = true;
}

void RadiateRandColor::loop(CHSV leds[], uint8_t fht[], uint8_t max) {
    if (currentLED >= middleLED) {
        currentLED = 0;
        uint8_t hue = random8();
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i].h = hue;
        }
    }

    int tail = 0;
    if (NUM_LEDS % 2 == 0) {
        for (int i = middleLED - 1; i >= 0; i--) {
            if (i == currentLED) {
                leds[middleLED + i].v = 255;
                leds[middleLED - i - 1].v = 255;
                tail++;
            } else if (i == currentLED - tail && tail <= tailLength) {
                float val = 255.0F * (1.0F - (float) tail / (float) tailLength);
                leds[middleLED + i].v = val;
                leds[middleLED - i - 1].v = val;
                tail++;
            } else {
                leds[middleLED + i].v = 0;
                leds[middleLED - i - 1].v = 0;
            }
        }
    } else {
        for (int i = middleLED - 1; i >= 0; i--) {
            if (i == currentLED) {
                leds[middleLED + i - 1].v = 255;
                leds[middleLED - i - 1].v = 255;
                tail++;
            } else if (i == currentLED - tail && tail <= tailLength) {
                float val = 255.0F * (1.0F - (float) tail / (float) tailLength);
                leds[middleLED + i - 1].v = val;
                leds[middleLED - i - 1].v = val;
            } else {
                leds[middleLED + i - 1].v = 0;
                leds[middleLED - i - 1].v = 0;
            }
        }
    }
    currentLED++;
}