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
    // fht[0] = 0-86Hz = sub-bass
    // fht[1] = 86-258Hz = bass
    // fht[2] = 258-431Hz = low-midrange
    // fht[3] = 431-602Hz = low-midrange + midrange
    // ...
    // fht[11] = 1809-1981Hz = midrange
    // fht[12] = 1981-2153Hz = midrange + upper-midrange
    // ...
    // fht[22] = 3704-3876Hz = upper-midrange
    // fht[23] = 3876-4048Hz = upper-midrange + presence
    // ...
    // fht[34] = 5771-5943Hz = presence
    // fht[35] = 5943-6115Hz = presence + brilliance
    // ...
    // fht[115] = 19724-19897Hz = brilliance
    // fht[116] = 19897-20069Hz = brilliance + ???
    // ...
    // fht[128] = 21964-22136Hz = ???

    leds[0].v = ((double) fht[0] / (double) max) * 255.0;
    leds[1].v = ((double) fht[1] / (double) max) * 255.0;
    leds[2].v = ((double) avg(fht, 2, 3) / (double) max) * 255.0;
    leds[3].v = ((double) avg(fht, 4, 12) / (double) max) * 255.0;
    leds[4].v = ((double) avg(fht, 13, 23) / (double) max) * 255.0;
    leds[5].v = ((double) avg(fht, 24, 35) / (double) max) * 255.0;
    leds[6].v = ((double) avg(fht, 36, 116) / (double) max) * 255.0;
    
    /*for (int i = 0; i < NUM_LEDS; i++) {
        double newValue = ((double) fht[i] / (double) max) * 255.0;
        double oldValue = ((double) leds[i].v / (double) max) * 255.0;
        leds[i].v += (newValue - oldValue) * timescale;
    }*/
}

uint8_t TestAudio::avg(uint8_t fht[], uint16_t start, uint16_t end) {
    int retVal = 0;
    for (int i = start; i < end; i++) {
        retVal += fht[i];
    }
    return retVal / (end - start);
}