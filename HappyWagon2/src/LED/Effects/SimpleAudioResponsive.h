#ifndef SimpleAudioResponsive_h
#define SimpleAudioResponsive_h

#include "IEffect.h"

class SimpleAudioResponsive : public IEffect {
    private:
    uint16_t destroyedLEDs = 0;
    bool destroyed = false;
    uint16_t avg(int16_t fft[], uint16_t start, uint16_t end);
    uint16_t bins[7];
    public:
    SimpleAudioResponsive();
    bool canLoop(unsigned long delta) { return delta >= 50; }
    void loop(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc);
    void destroy(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc);
    bool isDestroyed() { return destroyed; }
};

#endif