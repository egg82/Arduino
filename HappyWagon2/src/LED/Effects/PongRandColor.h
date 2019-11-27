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
    void loop(CHSV leds[], uint8_t fht[], uint8_t max);
    void destroy(CHSV leds[], uint8_t fht[], uint8_t max);
    bool isDestroyed() { return destroyed; }
};

#endif