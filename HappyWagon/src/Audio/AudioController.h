#ifndef AudioController_h
#define AudioController_h

#include <AudioHacker.h>
//#include <FHT.h>

#define SAMPLES 32

class AudioController {
    private:
    unsigned int buf;
    public:
    AudioController();
    void loop(bool evenCycle);
};
#endif