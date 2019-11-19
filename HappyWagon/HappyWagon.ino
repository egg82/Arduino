#include "src/LED/LEDController.h"
#include "src/LED/Effects/IEffect.h"
#include "src/LED/Effects/Blink.h"
#include "src/LED/Effects/Fade.h"
#include "src/LED/Effects/FadeRandColor.h"
#include "src/LED/Effects/PongRandColor.h"
#include "src/LED/Effects/RadiateRandColor.h"

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
    random16_set_seed(analogRead(1));
    randomSeed(analogRead(0));

    ledController = new LEDController();
    ledController->clear(CHSV(random8(), 255, 0));
    currentEffect = static_cast<Effect>(random(0, NONE));
    ledController->setEffect(getEffect(currentEffect));

    lastRandTime = millis();
}

bool isSet = false;

void loop() {
    ledController->loop();

    // Account for time taken during setup when calculating for effect switch
    if (!isSet && ledController->isSetup()) {
        isSet = true;
        lastRandTime = millis();
    }

    // Ensure we don't switch effects too quickly
    int mills = millis() - lastRandTime;
    if (isSet && (mills >= 30000 || (mills >= 15000 && randFloat((float) mills, 30000.0F) >= 0.01F))) {
        // Ensure we get a different random function
        do {
            Effect e = static_cast<Effect>(random(0, NONE));
            if (e != currentEffect) {
                currentEffect = e;
                ledController->setEffect(getEffect(e));
                break;
            }
        } while (true);
        isSet = false;
    }
}

float randFloat(float mills, float maxMills) { return ((float) random(0, RAND_MAX) / (float) RAND_MAX) * (mills / maxMills); }

IEffect *getEffect(Effect effect) {
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] ");
    Serial.print("Attempting to switch to ");
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