#include "AudioController.h"

AudioController::AudioController() { AudioHacker.begin(); }

void AudioController::loop(bool evenCycle) {
    unsigned int signal = AudioHacker.readADC();
    AudioHacker.writeDAC(signal);

    if (evenCycle) {
        buf = signal;
    } else {
        
    }
}