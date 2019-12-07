#ifndef TestAudio_h
#define TestAudio_h

#include "IEffect.h"

class TestAudio : public IEffect {
    private:
    bool destroyed = false;
    double timescale = 0.1;
    uint16_t avg(int16_t fft[], uint16_t start, uint16_t end);
    uint16_t scale(double oldVal, double newVal) { return (newVal - oldVal) * timescale; }
    public:
    TestAudio();
    bool canLoop(unsigned long delta) { return delta >= 10; }
    void loop(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc);
    void destroy(CHSV leds[], int16_t fft[], int16_t peak, uint32_t peakBin, bool recalc);
    bool isDestroyed() { return destroyed; }
};

#endif