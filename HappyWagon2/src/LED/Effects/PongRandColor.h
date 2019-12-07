#ifndef PongRandColor_h
#define PongRandColor_h


#include "IEffect.h"
#include "../LEDController.h"

class PongRandColor : public IEffect {
    private:
    bool destroyed = false;
    bool pongReverse = true;
    int currentLED = 0;
    int tailLength = NUM_LEDS / 5;
    public:
    PongRandColor();
    bool canLoop(unsigned long delta) { return delta >= 50; }
    void loop(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc);
    void destroy(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc);
    bool isDestroyed() { return destroyed; }
};

#endif