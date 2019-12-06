#include "TestLights.h"
#include "../LEDController.h"

TestLights::TestLights() { }

void TestLights::destroy(CHSV leds[], int16_t fft[], int16_t peak) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].h = color.h;
        leds[i].s = color.s;
        leds[i].v = color.v;
    }
    destroyed = true;
}

void TestLights::loop(CHSV leds[], int16_t fft[], int16_t peak) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].v = (leds[i].v == 255) ? 0 : 255;
    }
}