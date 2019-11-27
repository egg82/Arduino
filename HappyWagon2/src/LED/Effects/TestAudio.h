#ifndef TestAudio_h
#define TestAudio_h

#include "IEffect.h"

class TestAudio : public IEffect {
    private:
    bool destroyed = false;
    double timescale = 0.05;
    uint8_t avg(uint8_t fht[], uint16_t start, uint16_t end);
    public:
    TestAudio();
    bool canLoop(unsigned long delta) { return delta >= 10; }
    void loop(CHSV leds[], uint8_t fht[], uint8_t max);
    void destroy(CHSV leds[], uint8_t fht[], uint8_t max);
    bool isDestroyed() { return destroyed; }
};

#endif