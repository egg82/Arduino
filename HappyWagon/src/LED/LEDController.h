#ifndef LEDController_h
#define LEDController_h

#include <FastLED.h>
#include "Effects/IEffect.h"

#define NUM_LEDS 30
#define PIN 3

class LEDController {
    private:
    IEffect *effect = NULL;
    IEffect *previousEffect = NULL;
    void display();
    public:
    LEDController();
    void setEffect(IEffect *effect);
    IEffect *getEffect() { return effect; };
    bool loop(unsigned long mills, volatile double vReal[]);
    bool isSetup() { return this->effect->isSetup(); }
    bool isDestroyed() { return this->effect->isDestroyed(); }

    void clear(CHSV color);
};
#endif