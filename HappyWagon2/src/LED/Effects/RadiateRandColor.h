#ifndef RadiateRandColor_h
#define RadiateRandColor_h

#include "IEffect.h"
#include "../LEDController.h"

class RadiateRandColor : public IEffect {
    private:
    bool destroyed = false;
    int currentLED = 0;
    int middleLED = NUM_LEDS / 2;
    int tailLength = NUM_LEDS / 5;
    public:
    RadiateRandColor();
    bool canLoop(unsigned long delta) { return delta >= 50; }
    void loop(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc);
    void destroy(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc);
    bool isDestroyed() { return destroyed; }
};

#endif