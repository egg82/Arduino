#ifndef TestLights_h
#define TestLights_h

#include "IEffect.h"

class TestLights : public IEffect {
    private:
    bool destroyed = false;
    CHSV color = CHSV(0, 255, 0);
    public:
    TestLights();
    bool canLoop(unsigned long delta) { return delta >= 500; }
    void loop(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc);
    void destroy(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc);
    bool isDestroyed() { return destroyed; }
};

#endif