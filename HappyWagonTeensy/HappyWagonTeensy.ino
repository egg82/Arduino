#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "src/Audio/AudioController.h"
#include <arduinoFFT.h>

arduinoFFT FFT = arduinoFFT();

AudioController *audioController;

unsigned int sampleRate = DEFAULT_SAMPLE_RATE;
unsigned int timerStart = UINT16_MAX - (F_CPU / sampleRate);

#define DO_DEBUG
unsigned long lastDebugPrint = 0;
volatile unsigned int timerEndEven;
volatile unsigned int timerEndOdd;
bool evenCycle = true;

volatile bool ready = false;

double peak;
double vReal[SAMPLES];
double vImag[SAMPLES];

void setup() {
    Serial.begin(115200);

    audioController = new AudioController();
}

void loop() {
    if (audioController->getDoubleBuffer().getBackBuffer().isFull()) {
        audioController->getDoubleBuffer().swapBuffers();
        Serial.println("FFT");
        for (int i = 0; i < SAMPLES; i++) {
            vReal[i] = audioController->getDoubleBuffer().getCurrentBuffer().shift();
        }
        FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
        FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
        FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
        peak = FFT.MajorPeak(vReal, SAMPLES, 22050);
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

/*ISR(TIMER1_OVF_vect) {
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
}*/