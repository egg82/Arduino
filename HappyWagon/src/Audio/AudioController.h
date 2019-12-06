#ifndef AudioController_h
#define AudioController_h

#include <AudioHacker.h>
//#include "../DoubleBuffer.h"

#define AUDIO_BUFFER_SIZE 256

class AudioController {
    private:
    //DoubleBuffer<uint16_t, AUDIO_BUFFER_SIZE> db;
    public:
    AudioController();
    //DoubleBuffer<uint16_t, AUDIO_BUFFER_SIZE> &getDoubleBuffer() { return db; }
    uint16_t loop(bool evenCycle);
};
#endif