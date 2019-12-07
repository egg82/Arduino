#include "src/Audio/AudioController.h"

#include <Wire.h>

#define AUDIO_BUFFER_SIZE 256

AudioController *audioController;

unsigned int sampleRate = DEFAULT_SAMPLE_RATE;
unsigned int timerStart = UINT16_MAX - (F_CPU / sampleRate);

//#define DO_DEBUG
unsigned long lastDebugPrint = 0;
volatile unsigned int timerEndEven;
volatile unsigned int timerEndOdd;
bool evenCycle = true;

uint16_t currentPos = 0;
uint16_t buffer[AUDIO_BUFFER_SIZE];
volatile bool ready = false;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    Wire.setTimeout(100);
    Wire.setClock(380000L);
    //Wire.setClock(400000);
    //Wire.setClock(1000000L);

    audioController = new AudioController();
}

void loop() {
    if (ready) {
        uint16_t current = 0;
        while (current < AUDIO_BUFFER_SIZE - 1) {
            uint8_t min = min(AUDIO_BUFFER_SIZE - 1 - current, 16);
            Wire.beginTransmission(0x20);
            for (int i = 0; i < min; i++) {
                uint16_t read = buffer[current + i];
                // Split uint16_t into two uint8_t little-endian
                Wire.write((read >> 8) & 0xFF); // low byte
                Wire.write(read & 0xFF); // high byte
            }
            Wire.endTransmission();
            current += min;
        }
        ready = false;
    }

    /*if (!audioController->getDoubleBuffer().getBackBuffer().isEmpty()) {
        audioController->getDoubleBuffer().swapBuffers();
        //uint16_t numBytes = 0;
        Wire.beginTransmission(0x20);
        while (!audioController->getDoubleBuffer().getCurrentBuffer().isEmpty()) {
            int read = audioController->getDoubleBuffer().getCurrentBuffer().shift();
            // Split uint16_t into two uint8_t little-endian
            Wire.write((read >> 8) & 0xFF); // low byte
            Wire.write(read & 0xFF); // high byte
            //numBytes++;
        }
        Wire.endTransmission();

        Serial.print("wrote ");
        Serial.print(numBytes * 2);
        Serial.println(" bytes");
    }*/

    #ifdef DO_DEBUG
    unsigned long mills = millis();
    if ((mills - lastDebugPrint) >= 1000) {
        lastDebugPrint = mills;

        // Print the number of instruction cycles remaining at the end of the ISR.
        // The more work you try to do in the ISR, the lower this number will become.
        // If the number of cycles remaining reaches 0, then the ISR will take up
        // all the CPU time and the code in loop() will not run.

        Serial.print("even cycles remaining = ");
        Serial.print(UINT16_MAX - timerEndEven);
        Serial.print("   odd cycles remaining = ");
        Serial.print(UINT16_MAX - timerEndOdd);
        Serial.println();
        if (((UINT16_MAX - timerEndEven) < 20) || (((UINT16_MAX - timerEndOdd) < 20))) {
            Serial.println("WARNING: ISR execution time is too long. Reduce sample rate or reduce the amount of code in the ISR.");
        }
    }
    #endif

    //timerStart = UINT16_MAX - (F_CPU / sampleRate);
}

ISR(TIMER1_OVF_vect) {
    TCNT1 = timerStart;
    uint16_t retVal = audioController->loop(evenCycle);
    if (!ready) {
        buffer[currentPos] = retVal;
        if (currentPos >= AUDIO_BUFFER_SIZE - 1) {
            currentPos = 0;
            ready = true;
        } else {
            currentPos++;
        }
    }

    #ifdef DO_DEBUG
    if (evenCycle) {
        timerEndEven = TCNT1;
    } else {
        timerEndOdd = TCNT1;
    }
    #endif
    evenCycle = !evenCycle;
}