#include "AudioController.h"

#include <Wire.h>

AudioController::AudioController() { AudioHacker.begin(); }

void AudioController::loop(bool evenCycle) {
    unsigned int read = AudioHacker.readADC();
    AudioHacker.writeDAC(read);

    if (!evenCycle) {
        db.getBackBuffer().push(read >> 4);
    }
}