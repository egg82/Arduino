#ifndef IEffect_h
#define IEffect_h

#include <FastLED.h>

class IEffect {
    public:
    virtual ~IEffect(){};
    virtual bool canLoop(unsigned long delta) { return true; }
    virtual void loop(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc) = 0;
    virtual void destroy(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc) = 0;
    virtual bool isDestroyed() { return true; }
};

#endif