#ifndef AudioController_h
#define AudioController_h

#include <AudioHacker.h>
#include "../DoubleBuffer.h"

#define AUDIO_BUFFER_SIZE 512

class AudioController {
    private:
    DoubleBuffer<uint8_t, AUDIO_BUFFER_SIZE> db;
    public:
    AudioController();
    DoubleBuffer<uint8_t, AUDIO_BUFFER_SIZE> &getDoubleBuffer() { return db; }
    void loop(bool evenCycle);
};
#endif