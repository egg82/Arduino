#include "src/Audio/AudioController.h"

#include <Wire.h>

AudioController *audioController;

unsigned int sampleRate = DEFAULT_SAMPLE_RATE;
unsigned int timerStart = UINT16_MAX - (F_CPU / sampleRate);

//#define DO_DEBUG
unsigned long lastDebugPrint = 0;
volatile unsigned int timerEndEven;
volatile unsigned int timerEndOdd;
bool evenCycle = true;

volatile bool ready = false;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    Wire.flush();
    Wire.setTimeout(1000);

    Serial.println("Setting up audio");
    delay(1000);
    audioController = new AudioController();
    delay(1000);
    Serial.println("Set up audio");
}

void loop() {
    if (!audioController->getDoubleBuffer().getBackBuffer().isEmpty()) {
        audioController->getDoubleBuffer().swapBuffers();
        uint16_t numBytes = 0;
        Wire.beginTransmission(4);
        while (!audioController->getDoubleBuffer().getCurrentBuffer().isEmpty()) {
            uint16_t read = audioController->getDoubleBuffer().getCurrentBuffer().shift();
            Wire.write((read >> 8) & 0xFF);
            Wire.write(read & 0xFF);
            numBytes++;
        }
        Wire.endTransmission();

        /*Serial.print("wrote ");
        Serial.print(numBytes * 2);
        Serial.println(" bytes");*/
    }

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
    audioController->loop(evenCycle);

    #ifdef DO_DEBUG
    if (evenCycle) {
        timerEndEven = TCNT1;
    } else {
        timerEndOdd = TCNT1;
    }
    #endif
    evenCycle = !evenCycle;
}