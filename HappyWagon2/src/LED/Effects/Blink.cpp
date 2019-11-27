#include "Blink.h"
#include "../LEDController.h"

Blink::Blink() { }

void Blink::destroy(CHSV leds[], uint8_t fht[], uint8_t max) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].v = 0;
    }
    destroyed = true;
}

void Blink::loop(CHSV leds[], uint8_t fht[], uint8_t max) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].v = (leds[i].v == 255) ? 0 : 255;
    }
}