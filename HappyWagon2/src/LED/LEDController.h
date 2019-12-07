#ifndef LEDController_h
#define LEDController_h

#include <FastLED.h>
#include "Effects/IEffect.h"

#define NUM_LEDS 30
#define PIN 3

class LEDController {
    private:
    bool isSet = false;
    IEffect *effect = NULL;
    IEffect *previousEffect = NULL;
    void display();
    public:
    LEDController();
    void setEffect(IEffect *effect);
    IEffect *getEffect() { return effect; };
    bool loop(unsigned long mills, int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc);
    bool isSetup() { return isSet; }
    bool isDestroyed() { return this->effect->isDestroyed(); }

    void clear(CHSV color);
};
#endif