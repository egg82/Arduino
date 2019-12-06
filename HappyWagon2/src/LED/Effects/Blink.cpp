#include "Blink.h"
#include "../LEDController.h"

Blink::Blink() { }

void Blink::destroy(CHSV leds[], int16_t fft[], int16_t peak) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].v = 0;
    }
    destroyed = true;
}

void Blink::loop(CHSV leds[], int16_t fft[], int16_t peak) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].v = (leds[i].v == 255) ? 0 : 255;
    }
}