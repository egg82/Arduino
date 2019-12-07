#include "SimpleAudioResponsive.h"
#include "../LEDController.h"

SimpleAudioResponsive::SimpleAudioResponsive() { }

void SimpleAudioResponsive::destroy(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc) {
    for (int i = NUM_LEDS - 1; i > 0; i--) {
        leds[i].h = leds[i - 1].h;
        leds[i].s = leds[i - 1].s;
        leds[i].v = leds[i - 1].v;
    }
    leds[0].s = 255;
    leds[0].v = 0;

    destroyedLEDs++;
    if (destroyedLEDs >= NUM_LEDS) {
        uint8_t hue = random8();
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i].h = hue;
        }
        destroyed = true;
    }
}

void SimpleAudioResponsive::loop(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc) {
    // 44100Hz / 1024 bins = 43.06640625Hz peak at each bin
    // 86.1328125Hz / 2 = +-21.533203125Hz for each bin
    // only 512 bins are available, so max frequency is 22050Hz
    // bin 0 starts at 0Hz

    // https://www.teachmeaudio.com/mixing/techniques/audio-spectrum/
    // sub-bass = 20-60Hz
    // bass = 60-250Hz
    // low-midrange = 250-500Hz
    // midrange = 500-2000Hz
    // upper-midrage = 2000-4000Hz
    // presence = 4000-6000Hz
    // brilliance = 6000-20000Hz

    // fht[0] = 0-22Hz = ??? + sub-bass
    // fht[1] = 22-65Hz = sub-bass + bass
    // fht[2] = 65-108Hz = bass
    // ...
    // fht[5] = 194-237Hz = bass
    // fht[6] = 237-280Hz = bass + low-midrage
    // fht[7] = 280-323Hz = low-midrage
    // ...
    // fht[11] = 452-495Hz = low-midrange
    // fht[12] = 495-538Hz = low-midrange + midrange
    // fht[13] = 538-581Hz = midrange
    // ...
    // fht[45] = 1916-1960Hz = midrange
    // fht[46] = 1960-2002Hz = midrange + upper-midrange
    // fht[47] = 2002-2046Hz = upper-midrange
    // ...
    // fht[92] = 3941-3984Hz = upper-midrange
    // fht[93] = 3984-4026Hz = upper-midrange + presence
    // fht[94] = 4026-4069Hz = presence
    // ...
    // fht[138] = 5921-5965Hz = presence
    // fht[139] = 5965-6008Hz = presence + brilliance
    // fht[140] = 6008-6051Hz = brilliance
    // ...
    // fht[463] = 19918-19961Hz = brilliance
    // fht[464] = 19961-20004Hz = brilliance + ???
    // fht[465] = 20004-20047Hz = ???
    // ...
    // fht[512] = 22028-22050Hz = ???

    /*leds[0].v += scale(((double) leds[0].v / peak) * 255.0, ((double) fft[0] / peak) * 255.0);
    leds[1].v += scale(((double) leds[1].v / peak) * 255.0, ((double) fft[1] / peak) * 255.0);
    leds[2].v += scale(((double) leds[2].v / peak) * 255.0, ((double) avg(fft, 2, 3) / peak) * 255.0);
    leds[3].v += scale(((double) leds[3].v / peak) * 255.0, ((double) avg(fft, 4, 12) / peak) * 255.0);
    leds[4].v += scale(((double) leds[4].v / peak) * 255.0, ((double) avg(fft, 13, 23) / peak) * 255.0);
    leds[5].v += scale(((double) leds[5].v / peak) * 255.0, ((double) avg(fft, 24, 35) / peak) * 255.0);
    leds[6].v += scale(((double) leds[6].v / peak) * 255.0, ((double) avg(fft, 36, 116) / peak) * 255.0);*/

    /*Serial.print((double) fft[1] / (double) peak);
    Serial.print("\t");
    Serial.print((double) avg(fft, 2, 5) / (double) peak);
    Serial.print("\t");
    Serial.print((double) avg(fft, 6, 11) / (double) peak);
    Serial.print("\t");
    Serial.print((double) avg(fft, 12, 46) / (double) peak);
    Serial.print("\t");
    Serial.print((double) avg(fft, 47, 93) / (double) peak);
    Serial.print("\t");
    Serial.print((double) avg(fft, 94, 139) / (double) peak);
    Serial.print("\t");
    Serial.println((double) avg(fft, 140, 464) / (double) peak);
    Serial.flush();*/

    for (int i = NUM_LEDS - 1; i > 0; i--) {
        leds[i].h = leds[i - 1].h;
        leds[i].s = leds[i - 1].s;
        leds[i].v = leds[i - 1].v;
    }
    /*leds[0].h = peakBin <= 1 ? 160 : ((double) peakBin / 1024.0) * 224.0;
    leds[0].s = peakBin <= 1 ? 0 : 255;
    leds[0].v = 255;*/

    if (recalc) {
        bins[0] = min(((double) (fft[1] * 0.95) / 511.0) * 255.0, 255);
        bins[1] = min(((double) (avg(fft, 2, 5) * 1.05) / 511.0) * 255.0, 255);
        bins[2] = min(((double) (avg(fft, 6, 11) * 1.5) / 511.0) * 255.0, 255);
        bins[3] = min(((double) (avg(fft, 12, 46) * 1.5) / 511.0) * 255.0, 255);
        bins[4] = min(((double) (avg(fft, 47, 93) * 1.5) / 511.0) * 255.0, 255);
        bins[5] = min(((double) (avg(fft, 94, 139) * 1.25) / 511.0) * 255.0, 255);
        bins[6] = min(((double) (avg(fft, 140, 464)* 1.0) / 511.0) * 255.0, 255);

        /*for (int i = 0; i < 7; i++) {
            Serial.print(bins[i]);
            Serial.print("\t");
        }
        Serial.println();
        Serial.flush();*/
    }

    uint8_t max = 0;
    uint8_t maxBin = 0;
    for (int i = 0; i < 7; i++) {
        if (bins[i] > max) {
            max = bins[i];
            maxBin = i;
        }
    }
    leds[0].h = ((double) maxBin / 7.0) * 224.0;
    leds[0].s = peakBin == 0 ? 0 : 255;
    leds[0].v = peakBin == 0 ? 190 : 255; // White LEDs are very bright

    /*leds[0].v = ((double) fft[1] / 511.0) * 255.0; // sub-bass
    leds[1].v = ((double) avg(fft, 2, 5) / 511.0) * 255.0; // bass
    leds[2].v = ((double) avg(fft, 6, 11) / 511.0) * 255.0; // low-midrange
    leds[3].v = ((double) avg(fft, 12, 46) / 511.0) * 255.0; // midrange
    leds[4].v = ((double) avg(fft, 47, 93) / 511.0) * 255.0; // upper-midrange
    leds[5].v = ((double) avg(fft, 94, 139) / 511.0) * 255.0; // presence
    leds[6].v = ((double) avg(fft, 140, 464) / 511.0) * 255.0; // brilliance*/
    
    /*for (int i = 0; i < NUM_LEDS; i++) {
        double newValue = ((double) fft[i] / peak) * 255.0;
        double oldValue = ((double) leds[i].v / peak) * 255.0;
        leds[i].v += (newValue - oldValue) * timescale;
    }*/
}

uint16_t SimpleAudioResponsive::avg(int16_t fft[], uint16_t start, uint16_t end) {
    double retVal = 0.0;
    for (int i = start; i < end; i++) {
        retVal += fft[i];
    }
    return retVal / (double) (end - start);
}