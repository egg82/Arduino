#include <Arduino.h>

#include <FastLED.h>

void setup() {
    pinMode(0, OUTPUT);
}

bool isHigh = true;

void loop() {
    digitalWrite(0, isHigh ? HIGH : LOW);
    isHigh = !isHigh;
    delay(100);
}