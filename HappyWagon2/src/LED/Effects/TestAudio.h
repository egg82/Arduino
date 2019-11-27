#ifndef TestAudio_h
#define TestAudio_h

#include "IEffect.h"

class TestAudio : public IEffect {
    private:
    bool destroyed = false;
    public:
    TestAudio();
    bool canLoop(unsigned long delta) { return delta >= 10; }
    void loop(CHSV leds[], uint8_t fht[], uint8_t max);
    void destroy(CHSV leds[], uint8_t fht[], uint8_t max);
    bool isDestroyed() { return destroyed; }
};

#endif