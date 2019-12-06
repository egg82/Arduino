#include "TestAudio.h"
#include "../LEDController.h"

TestAudio::TestAudio() { }

void TestAudio::destroy(CHSV leds[], int16_t fft[], int16_t peak) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].v = 0;
    }
    destroyed = true;
}

void TestAudio::loop(CHSV leds[], int16_t fft[], int16_t peak) {
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

    /*leds[0].v += scale(((double) leds[0].v / peak) * 255.0, ((double) fft[0] / peak) * 255.0);
    leds[1].v += scale(((double) leds[1].v / peak) * 255.0, ((double) fft[1] / peak) * 255.0);
    leds[2].v += scale(((double) leds[2].v / peak) * 255.0, ((double) avg(fft, 2, 3) / peak) * 255.0);
    leds[3].v += scale(((double) leds[3].v / peak) * 255.0, ((double) avg(fft, 4, 12) / peak) * 255.0);
    leds[4].v += scale(((double) leds[4].v / peak) * 255.0, ((double) avg(fft, 13, 23) / peak) * 255.0);
    leds[5].v += scale(((double) leds[5].v / peak) * 255.0, ((double) avg(fft, 24, 35) / peak) * 255.0);
    leds[6].v += scale(((double) leds[6].v / peak) * 255.0, ((double) avg(fft, 36, 116) / peak) * 255.0);*/

    /*leds[0].v = ((double) fft[0] / 1023.0) * 255.0;
    leds[1].v = ((double) fft[1] / 1023.0) * 255.0;
    leds[2].v = ((double) avg(fft, 2, 3) / 1023.0) * 255.0;
    leds[3].v = ((double) avg(fft, 4, 12) / 1023.0) * 255.0;
    leds[4].v = ((double) avg(fft, 13, 23) / 1023.0) * 255.0;
    leds[5].v = ((double) avg(fft, 24, 35) / 1023.0) * 255.0;
    leds[6].v = ((double) avg(fft, 36, 116) / 1023.0) * 255.0;*/

    leds[0].v = scale(((double) leds[0].v / peak) * 255.0, ((double) fft[0] / 1023.0) * 255.0);
    leds[1].v = scale(((double) leds[0].v / peak) * 255.0, ((double) fft[1] / 1023.0) * 255.0);
    leds[2].v = scale(((double) leds[0].v / peak) * 255.0, ((double) avg(fft, 2, 3) / 1023.0) * 255.0);
    leds[3].v = scale(((double) leds[0].v / peak) * 255.0, ((double) avg(fft, 4, 12) / 1023.0) * 255.0);
    leds[4].v = scale(((double) leds[0].v / peak) * 255.0, ((double) avg(fft, 13, 23) / 1023.0) * 255.0);
    leds[5].v = scale(((double) leds[0].v / peak) * 255.0, ((double) avg(fft, 24, 35) / 1023.0) * 255.0);
    leds[6].v = scale(((double) leds[0].v / peak) * 255.0, ((double) avg(fft, 36, 116) / 1023.0) * 255.0);
    
    /*for (int i = 0; i < NUM_LEDS; i++) {
        double newValue = ((double) fft[i] / peak) * 255.0;
        double oldValue = ((double) leds[i].v / peak) * 255.0;
        leds[i].v += (newValue - oldValue) * timescale;
    }*/
}

uint8_t TestAudio::avg(int16_t fft[], uint16_t start, uint16_t end) {
    double retVal = 0.0;
    for (int i = start; i < end; i++) {
        retVal += fft[i];
    }
    return retVal / (end - start);
}