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
    // We're sampling at half 44100Hz, so 22050Hz
    // 22050Hz / 128 bins = 172.265625Hz peak at each bin
    // 172.265625Hz / 2 = +-86.1328125Hz for each bin
    // bin 0 starts at 0Hz

    // https://www.teachmeaudio.com/mixing/techniques/audio-spectrum/
    // sub-bass = 20-60Hz
    // bass = 60-250Hz
    // low-midrange = 250-500Hz
    // midrange = 500-2000Hz
    // upper-midrage = 2000-4000Hz
    // presence = 4000-6000Hz
    // brilliance = 6000-20000Hz

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

    leds[0].v += scale(((double) leds[0].v / (double) max) * 255.0, ((double) fht[0] / (double) max) * 255.0);
    leds[1].v += scale(((double) leds[1].v / (double) max) * 255.0, ((double) fht[1] / (double) max) * 255.0);
    leds[2].v += scale(((double) leds[2].v / (double) max) * 255.0, ((double) avg(fht, 2, 3) / (double) max) * 255.0);
    leds[3].v += scale(((double) leds[3].v / (double) max) * 255.0, ((double) avg(fht, 4, 12) / (double) max) * 255.0);
    leds[4].v += scale(((double) leds[4].v / (double) max) * 255.0, ((double) avg(fht, 13, 23) / (double) max) * 255.0);
    leds[5].v += scale(((double) leds[5].v / (double) max) * 255.0, ((double) avg(fht, 24, 35) / (double) max) * 255.0);
    leds[6].v += scale(((double) leds[6].v / (double) max) * 255.0, ((double) avg(fht, 36, 116) / (double) max) * 255.0);
    
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