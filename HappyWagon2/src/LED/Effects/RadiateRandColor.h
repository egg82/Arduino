#ifndef RadiateRandColor_h
#define RadiateRandColor_h

#include "IEffect.h"
#include "../LEDController.h"

class RadiateRandColor : public IEffect {
    private:
    bool destroyed = false;
    int currentLED = 0;
    int middleLED = 0;
    int tailLength = NUM_LEDS / 5;
    public:
    RadiateRandColor();
    bool canLoop(unsigned long delta) { return delta >= 50; }
    void loop(CHSV leds[], uint8_t fht[], uint8_t max);
    void destroy(CHSV leds[], uint8_t fht[], uint8_t max);
    bool isDestroyed() { return destroyed; }
};

#endif