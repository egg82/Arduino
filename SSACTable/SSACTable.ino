#include "LEDController.h"

LEDController *ledController;
unsigned long lastRandTime;

void setup() {
    ledController = new LEDController();
    ledController->clear(CHSV(0, 0, 0));

    lastRandTime = millis();
}

void loop() {
    ledController->loop();

    if (millis() - lastRandTime >= 15000) {
        do {
            Pattern p = static_cast<Pattern>(rand() % NONE);
            if (p != ledController->getPattern()) {
                ledController->setPattern(p);
                break;
            }
        } while (true);
        lastRandTime = millis(); // Account for time taken by phase change reset
    }
}