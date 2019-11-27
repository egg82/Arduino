#include "AudioController.h"

#include <Wire.h>

AudioController::AudioController() { AudioHacker.begin(); }

void AudioController::loop(bool evenCycle) {
    uint16_t read = AudioHacker.readADC();
    AudioHacker.writeDAC(read);

    if (!evenCycle) {
        // Convert 12-bit unsigned to 16-bit unsigned
        // We could shift 4 left for 16, but this formula scales the result properly rather than padding zeroes
        //read = ((read << 4) & (uint16_t) 0xFFF0) | ((read >> 8) & (uint16_t) 0x000F);
        
        db.getBackBuffer().push(read >> 2);
    }
}