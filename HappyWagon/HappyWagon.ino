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

unsigned long lastRandTime = 0;

unsigned int sampleRate = DEFAULT_SAMPLE_RATE;
unsigned int timerStart = UINT16_MAX - (F_CPU / sampleRate);

#define DO_DEBUG
unsigned long lastDebugPrint = 0;
volatile unsigned int timerEndEven;
volatile unsigned int timerEndOdd;
volatile double *vReal;
bool evenCycle = true;

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
    unsigned long mills = millis();

    if (ledController->loop(mills, vReal)) {
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

    #ifdef DO_DEBUG
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
    Serial.print("Using effect ");
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
    }
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
    evenCycle = !evenCycle;
    #endif
}