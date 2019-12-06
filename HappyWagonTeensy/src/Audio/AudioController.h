#ifndef AudioController_h
#define AudioController_h

#include <AudioHacker.h>
#include "../DoubleBuffer.h"

#define SAMPLES 256

class AudioController {
    private:
    DoubleBuffer<uint16_t, SAMPLES> db;
    public:
    AudioController();
    DoubleBuffer<uint16_t, SAMPLES> &getDoubleBuffer() { return db; }
    void loop(bool evenCycle);
};
#endif