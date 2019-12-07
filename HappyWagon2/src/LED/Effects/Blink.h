#ifndef Blink_h
#define Blink_h

#include "IEffect.h"

class Blink : public IEffect {
    private:
    bool destroyed = false;
    public:
    Blink();
    bool canLoop(unsigned long delta) { return delta >= 500; }
    void loop(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc);
    void destroy(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc);
    bool isDestroyed() { return destroyed; }
};

#endif