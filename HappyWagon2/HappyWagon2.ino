#define FHT_N 256
//#define LIN_OUT8 1
#define LOG_OUT 1

#include <FHT.h>
#include <Wire.h>

#include "src/LED/LEDController.h"
#include "src/LED/Effects/IEffect.h"
#include "src/LED/Effects/Blink.h"
#include "src/LED/Effects/Fade.h"
#include "src/LED/Effects/FadeRandColor.h"
#include "src/LED/Effects/PongRandColor.h"
#include "src/LED/Effects/RadiateRandColor.h"
#include "src/LED/Effects/TestAudio.h"

uint16_t currentPos = 0;
LEDController *ledController;

unsigned long lastRandTime = 0;
bool isSet = false;

volatile bool ready = false;
uint8_t max = 0;

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
    Wire.begin(4);
    Wire.onReceive(receive);
    Wire.setTimeout(1000);

    setSeeds(getNoise());

    ledController = new LEDController();
    ledController->clear(CHSV(random8(), 255, 0));
    currentEffect = static_cast<Effect>(random(0, NONE));
    ledController->setEffect(getEffect(currentEffect));

    lastRandTime = millis();
}

void loop() {
    if (ready) {
        max = 0;
        //Serial.println("FHT");
        fht_window();
        fht_reorder();
        fht_run();
        //fht_mag_lin8();
        fht_mag_log();
        for (int i = 0; i < FHT_N /2; i++) {
            max = max(max, fht_log_out[i]);
        }
        for (int i = 0; i < FHT_N / 2; i++) {
            char buffer[64];
            sprintf(buffer, "%03d", fht_log_out[i]);
            Serial.print(buffer);
            Serial.print(",");
            //Serial.print(fht_log_out[i], 2);
            //Serial.print(",");
        }
        Serial.println();
        ready = false;
    }

    unsigned long mills = millis();
    if (ledController->loop(mills, fht_log_out, max)) {
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
    return new TestAudio();
}

void receive(int bytes) {
    while (Wire.available() >= 2) {
        byte m = Wire.read();
        byte j = Wire.read();
        int k = (j << 8) | m;
        fht_input[currentPos] = (k - 0x0200) << 6;
        if (currentPos >= FHT_N - 1) {
            currentPos = 0;
            ready = true;
        } else {
            currentPos += 1;
        }
    }
}