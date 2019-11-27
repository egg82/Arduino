#include "TestAudio.h"
#include "../LEDController.h"

TestAudio::TestAudio() { }

void TestAudio::destroy(CHSV leds[], uint8_t fht[], uint8_t max) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].v = 0;
    }
    destroyed = true;
}

void TestAudio::loop(CHSV leds[], uint8_t fht[], uint8_t max) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].v = ((double) fht[i + 2] / (double) max) * 255.0;
    }
}