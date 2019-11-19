#include "AudioController.h"

unsigned int playbackBuf = 2048;
unsigned int sampleRate = DEFAULT_SAMPLE_RATE;
unsigned int timerStart = UINT16_MAX - (F_CPU / sampleRate);

AudioController::AudioController() {
    AudioHacker.begin();

    Serial.print("sample rate = ");
    Serial.print(sampleRate);
    Serial.print(" Hz");
    Serial.println();
}

unsigned int AudioController::loop() {
    unsigned int signal;

    AudioHacker.writeDAC(playbackBuf);
    signal = AudioHacker.readADC();
    playbackBuf = signal;

    return timerStart;
}