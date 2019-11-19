#ifndef PongRandColor_h
#define PongRandColor_h


#include "IEffect.h"
#include "../LEDController.h"

class PongRandColor : public IEffect {
    private:
    bool isSet = false;
    bool destroyed = false;
    bool pongReverse = true;
    int currentLED = 0;
    int tailLength = NUM_LEDS / 5;
    public:
    PongRandColor();
    bool isSetup() { return isSet; }
    void setup(CHSV leds[]);
    void loop(CHSV leds[]);
    void destroy(CHSV leds[]);
    bool isDestroyed() { return destroyed; }
};

#endif