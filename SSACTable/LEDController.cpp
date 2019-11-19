#include "LEDController.h"

#define NUM_LEDS 16
#define PIN 3
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define BRIGHTNESS 64

Pattern pattern = BLINK;
CHSV leds[NUM_LEDS];
CRGB c[NUM_LEDS];

LEDController::LEDController() {
    FastLED.addLeds<LED_TYPE, PIN, COLOR_ORDER>(c, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
}

void LEDController::clear(CHSV hue) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = hue;
        c[i] = CRGB(hue);
    }
    FastLED.show();
}

Pattern LEDController::getPattern() { return pattern; }

void LEDController::setPattern(Pattern p) {
    reset(p);
    pattern = p;
}

void LEDController::reset(Pattern p) {
    while (leds[0].s < 255) {
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i].s++;
        }
        delay(50);
        display();
    }
    while (leds[0].v < 255) {
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i].v++;
        }
        delay(50);
        display();
    }
}

bool fadeReverse = false;

void LEDController::loop() {
    if (pattern == HUE_SHIFT) {
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i].h++;
        }
        delay(10);
    } else if (pattern == BLINK) {
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i].v = (leds[i].v == 255) ? 0 : 255;
        }
        delay(500);
    } else if (pattern == FADE) {
        if (leds[0].v == 255) {
            fadeReverse = true;
        } else if (leds[0].v == 0) {
            fadeReverse = false;
        }
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i].v = (fadeReverse) ? leds[i].v - 1 : leds[i].v + 1;
        }
        delay(10);
    } else if (pattern == FADE_SHIFT) {
        if (leds[0].v == 255) {
            fadeReverse = true;
        } else if (leds[0].v == 0) {
            fadeReverse = false;
            for (int i = 0; i < NUM_LEDS; i++) {
                leds[i].h = random8();
            }
        }
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i].v = (fadeReverse) ? leds[i].v - 1 : leds[i].v + 1;
        }
        delay(10);
    }

    display();
}

void LEDController::display() {
    for (int i = 0; i < NUM_LEDS; i++) {
        c[i] = CRGB(leds[i]);
    }
    FastLED.show();
}

CRGB LEDController::getRandColor() { return CRGB(random8(), random8(), random8()); }