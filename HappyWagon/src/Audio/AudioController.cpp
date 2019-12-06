#include "AudioController.h"

#include <Wire.h>

AudioController::AudioController() { AudioHacker.begin(); }

uint16_t AudioController::loop(bool evenCycle) {
    uint16_t read = AudioHacker.readADC();
    AudioHacker.writeDAC(read);

    // Convert 12-bit unsigned to 16-bit unsigned
    // We could shift 4 left for 16, but this formula scales the result properly rather than padding zeroes
    //read = ((read << 4) & (uint16_t) 0xFFF0) | ((read >> 8) & (uint16_t) 0x000F);
    //db.getBackBuffer().push(read);
    
    // Convert 12-bit unsigned to 10-bit unsigned
    //db.getBackBuffer().push(read >> 2);
    return read >> 2;

    /*if (!evenCycle) {
        // Convert 12-bit unsigned to 16-bit unsigned
        // We could shift 4 left for 16, but this formula scales the result properly rather than padding zeroes
        //read = ((read << 4) & (uint16_t) 0xFFF0) | ((read >> 8) & (uint16_t) 0x000F);
        //db.getBackBuffer().push(read);
        
        // Convert 12-bit unsigned to 10-bit unsigned
        //db.getBackBuffer().push(read >> 2);

        buffer[currentPos] = read >> 2;
        if (currentPos >= AUDIO_BUFFER_SIZE - 1) {
            currentPos = 0;
        } else {
            currentPos++;
        }
    }*/
}