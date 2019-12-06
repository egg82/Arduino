#ifndef TestAudio_h
#define TestAudio_h

#include "IEffect.h"

class TestAudio : public IEffect {
    private:
    bool destroyed = false;
    double timescale = 0.1;
    uint8_t avg(int16_t fft[], uint16_t start, uint16_t end);
    uint8_t scale(double oldVal, double newVal) { return (newVal - oldVal) * timescale; }
    public:
    TestAudio();
    bool canLoop(unsigned long delta) { return delta >= 10; }
    void loop(CHSV leds[], int16_t fft[], int16_t peak);
    void destroy(CHSV leds[], int16_t fft[], int16_t peak);
    bool isDestroyed() { return destroyed; }
};

#endif