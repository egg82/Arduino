#ifndef LEDController_h
#define LEDController_h

#include <FastLED.h>
#include "Effects/IEffect.h"

#define NUM_LEDS 16
#define PIN 3

class LEDController {
    private:
    IEffect *effect;
    IEffect *previousEffect;
    void display();
    public:
    LEDController();
    void setEffect(IEffect *effect);
    IEffect *getEffect() { return effect; };
    void loop();
    bool isSetup() { return this->effect->isSetup(); }
    bool isDestroyed() { return this->effect->isDestroyed(); }

    void clear(CHSV color);
};
#endif