#include <Wire.h>
//#include <arduinoFFT.h>

#include "src/FFT.h"
//#include "src/DoubleBuffer.h"
#include "src/LED/LEDController.h"
#include "src/LED/Effects/IEffect.h"
#include "src/LED/Effects/Blink.h"
#include "src/LED/Effects/Fade.h"
#include "src/LED/Effects/FadeRandColor.h"
#include "src/LED/Effects/PongRandColor.h"
#include "src/LED/Effects/RadiateRandColor.h"
#include "src/LED/Effects/TestLights.h"
#include "src/LED/Effects/TestAudio.h"

//#define SAMPLES 256
//#define SAMPLING_FREQUENCY 22050

//volatile bool ready = false;
//arduinoFFT FFT = arduinoFFT();
FFT *fft;

LEDController *ledController;

unsigned long lastRandTime = 0;
bool isSet = false;

uint16_t currentPos = 0;
/*double peak;
double input[SAMPLES];
double vReal[SAMPLES];
double vImag[SAMPLES];
unsigned long size = sizeof(input[0]) * SAMPLES;*/

unsigned long inputSize;
unsigned long outputSize;

enum Effect {
    BLINK,
    FADE,
    FADE_RAND_COLOR,
    PONG_RAND_COLOR,
    RADIATE_RAND_COLOR,
    NONE
};

Effect currentEffect;

void setup() {
    Serial.begin(115200);
    Wire.begin(0x20);
    TWBR = 12;
    Wire.onReceive(receive);

    setSeeds(getNoise());

    fft = new FFT();
    inputSize = sizeof(fft->input[0]) * FFT_SIZE * 2;
    outputSize = sizeof(fft->input[0]) * FFT_SIZE;

    ledController = new LEDController();
    ledController->clear(CHSV(random8(), 255, 0));
    currentEffect = static_cast<Effect>(random(0, NONE));
    ledController->setEffect(getEffect(currentEffect));

    lastRandTime = millis();
}

void loop() {
    /*if (ready) {
        //max = 0;
        Serial.println("FFT start");
        Serial.flush();
        fft->compute();
        Serial.println("FFT end");
        Serial.flush();*/
        /*memcpy(vReal, input, size);
        memset(vImag, 0, size);
        FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
        FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
        FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
        peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);*/
        /*for(int i = 0; i < (FFT_SIZE / 2); i++) {
          Serial.println(fft->output[i], 1);
        }*/
        /*for (int i = 0; i < FHT_N / 2; i++) {
            char buffer[64];
            sprintf(buffer, "%03d", vReal[i]);
            Serial.print(buffer);
            Serial.print(",");
            //Serial.print(vReal[i], 2);
            //Serial.print(",");
        }
        Serial.println();*/
        //ready = false;
    //}

    unsigned long mills = millis();
    if (ledController->loop(mills, fft->output, 255)) {
        // Account for time taken during setup when calculating for effect switch
        if (!isSet && ledController->isSetup()) {
            isSet = true;
            lastRandTime = mills;
        }

        // Ensure we don't switch effects too quickly
        unsigned long m = mills - lastRandTime;
        if (isSet && (m >= 30000 || (m >= 15000 && randFloat() <= 0.01F))) {
            // Ensure we get a different random function
            do {
                Effect e = static_cast<Effect>(random(0, NONE));
                if (e != currentEffect) {
                    currentEffect = e;
                    ledController->setEffect(getEffect(e));
                    setSeeds(getNoise());
                    break;
                }
            } while (true);
            isSet = false;
        }
    }
}

void setSeeds(float seed) {
    random16_set_seed(seed);
    randomSeed(seed);
}

float randFloat() { return (float) random(0, RAND_MAX) / (float) RAND_MAX; }

float getNoise() {
    float retVal = 0.0F;
    do {
        retVal += analogRead(0);
        retVal += analogRead(1);
        retVal += analogRead(2);
        retVal += analogRead(3);
        if (retVal != 0.0F) {
            retVal /= 5.0F;
            while (floor(retVal) != retVal) {
                retVal *= 10.0F;
            }
            return retVal;
        }
    } while (true);
}

IEffect *getEffect(Effect effect) {
    /*Serial.print("Using effect ");
    Serial.println(effect);
    switch (effect) {
        case BLINK:
        return new Blink();
        case FADE:
        return new Fade();
        case FADE_RAND_COLOR:
        return new FadeRandColor();
        case PONG_RAND_COLOR:
        return new PongRandColor();
        case RADIATE_RAND_COLOR:
        return new RadiateRandColor();
    }*/
    //return new TestLights();
    return new TestAudio();
}

void receive(int bytes) {
    while (Wire.available() >= 2) {
        byte m = Wire.read(); // low byte
        byte j = Wire.read(); // high byte

        //if (!ready) {
            // From the example
            // ADC is unsigned 10-bit (0-1023) big-endian
            // byte m = ADCL; // ADC low byte (uint8_t)
            // byte j = ADCH; // ADC high byte (uint8_t)
            // int k = (j << 8) | m; // combine high + low into uint16_t little-endian
            // k -= 0x0200; // subtract 512 (-512-511)
            // k <<= 6; // left-shift to convert 10-bit into 16-bit
            // input[i] = k; // finally, add 16-bit signed int

            // Combine two uint8_t into one uint16_t little-endian
            //int k = (m << 8) | j;
            //input[currentPos] = (j << 8) | m;
            fft->input[currentPos] = (j << 8) | m;
            fft->input[currentPos + 1] = 0;
            if (currentPos >= FFT_SIZE * 2 - 2) {
            //if (currentPos >= SAMPLES - 1) {
                currentPos = 0;
                //ready = true;
                //memset(fft->output, 0, outputSize);
                Serial.println("FFT start");
                Serial.flush();
                fft->compute();
                Serial.println("FFT end");
                Serial.flush();
                //memset(fft->input, 0, inputSize);
            } else {
                //currentPos += 1;
                currentPos += 2;
            }
            // Convert signed to unsigned
            //fht_input[currentPos] = (k - 0x0200) << 6; // Subtract 512
            //db.getBackBuffer().push(k - 32768);
        //}
    }
}
