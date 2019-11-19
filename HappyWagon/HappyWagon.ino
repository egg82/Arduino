#include "src/Audio/AudioController.h"

#include "src/LED/LEDController.h"
#include "src/LED/Effects/IEffect.h"
#include "src/LED/Effects/Blink.h"
#include "src/LED/Effects/Fade.h"
#include "src/LED/Effects/FadeRandColor.h"
#include "src/LED/Effects/PongRandColor.h"
#include "src/LED/Effects/RadiateRandColor.h"

AudioController *audioController;
LEDController *ledController;

unsigned long lastRandTime;

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
    delay(5000);
    setSeeds(getNoise());

    ledController = new LEDController();
    ledController->clear(CHSV(random8(), 255, 0));
    currentEffect = static_cast<Effect>(random(0, NONE));
    ledController->setEffect(getEffect(currentEffect));

    lastRandTime = millis();

    audioController = new AudioController();
}

bool isSet = false;

void loop() {
    if (ledController->loop()) {
        // Account for time taken during setup when calculating for effect switch
        if (!isSet && ledController->isSetup()) {
            isSet = true;
            lastRandTime = millis();
        }

        // Ensure we don't switch effects too quickly
        int mills = millis() - lastRandTime;
        if (isSet && (mills >= 30000 || (mills >= 15000 && randFloat() <= 0.01F))) {
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

float randFloat() { return (float) random(0, RAND_MAX) / (float) RAND_MAX; }

float getNoise() {
    float retVal = 0.0F;
    do {
        retVal += analogRead(1);
        retVal += analogRead(2);
        retVal += analogRead(3);
        retVal += analogRead(4);
        retVal += analogRead(5);
        if (retVal != 0.0F) {
            retVal /= 5.0F;
            while (floor(retVal) != retVal) {
                retVal *= 10.0F;
            }
            return retVal;
        }
    } while (true);
}

void setSeeds(float seed) {
    random16_set_seed(seed);
    randomSeed(seed);
}

IEffect *getEffect(Effect effect) {
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
    }
}

ISR(TIMER1_OVF_vect) { TCNT1 = audioController->loop(); }