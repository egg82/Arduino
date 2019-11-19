#include "LEDController.h"

#define PIN_R 9
#define PIN_G 10
#define PIN_B 11

CHSV hsv = CHSV(random8(), 255, 255);

Pattern pattern = HUE_SHIFT;

LEDController::LEDController() {
    
}

void LEDController::clear(CRGB color) {
    analogWrite(PIN_R, color.r);
    analogWrite(PIN_G, color.g);
    analogWrite(PIN_B, color.b);
}

void LEDController::clear(CHSV hue) {
    clear(CRGB(hue));
}

Pattern LEDController::getPattern() { return pattern; }

void LEDController::setPattern(Pattern p) {
    reset(p);
    pattern = p;
}

void LEDController::reset(Pattern p) {
    /*if (p == TOTAL_SHIFT) {
        int8_t s = random8();
        while (hsv.s > s) {
            hsv.s--;
            clear(hsv);
            delay(50);
        }
        while (hsv.s < s) {
            hsv.s++;
            clear(hsv);
            delay(50);
        }
    } else {*/
        while (hsv.s < 255) {
            hsv.s++;
            clear(hsv);
            delay(50);
        }
    //}
    while (hsv.v < 255) {
        hsv.v++;
        clear(hsv);
        delay(50);
    }
}

bool fadeReverse = false;

void LEDController::loop() {
    if (pattern == HUE_SHIFT) {
        hsv.h++;
        clear(hsv);
        delay(50);
    } else if (pattern == BLINK) {
        hsv.v = (hsv.v == 255) ? 0 : 255;
        clear(hsv);
        delay(500);
    } else if (pattern == FADE) {
        if (hsv.v == 255) {
            fadeReverse = true;
        } else if (hsv.v == 0) {
            fadeReverse = false;
        }
        hsv.v = (fadeReverse) ? hsv.v - 1 : hsv.v + 1;
        clear(hsv);
        delay(10);
    } else if (pattern == FADE_SHIFT) {
        if (hsv.v == 255) {
            fadeReverse = true;
        } else if (hsv.v == 0) {
            fadeReverse = false;
            hsv.h = random8();
        }
        hsv.v = (fadeReverse) ? hsv.v - 1 : hsv.v + 1;
        clear(hsv);
        delay(10);
    }/* else if (pattern == TOTAL_SHIFT) {
        hsv.h++;
        hsv.s++;
        clear(hsv);
        delay(50);
    }*/
}

CRGB LEDController::getRandColor() { return CRGB(random8(), random8(), random8()); }