#include "Gyro.h"

float minX = 3.40282347e+38F; // Pins facing you and chip down, roll on its edge (90 degrees) to the right
float minY = 3.40282347e+38F; // Pins facing you and chip down, roll on its edge (90 degrees) toward you
float minZ = 3.40282347e+38F; // Flat on its back (chip down), facing up

float maxX = -3.4028235e+38F; // Pins facing you and chip down, roll on its edge (90 degrees) to the left
float maxY = -3.4028235e+38F; // Pins facing you and chip down, roll on its edge (90 degrees) away from you
float maxZ = -3.4028235e+38F; // same as minZ, but facing down instead of up

int maxSamples = 8;
int sampleX = 0;
float avgX = 0.0;
int sampleY = 0;
float avgY = 0.0;
int sampleZ = 0;
float avgZ = 0.0;

float zeroX = 331.5; // (maxX + minX) / 2
float zeroY = 329.5; // (maxY + minY) / 2
float zeroZ = 340.0; // (maxZ + minZ) / 2

float scaleX = 65.0; // (maxX / 3.3v) * 330mv/g
float scaleY = 68.5; // (maxY / 3.3v) * 330mv/g
float scaleZ = 68.0; // (maxZ / 3.3v) * 330mv/g

Gyro::Gyro(float minX, float maxX, float minY, float maxY, float minZ, float maxZ) {
    this->minX = minX;
    this->minY = minY;
    this->minZ = minZ;

    recalcX();
    recalcY();
    recalcZ();
}

Gyro::Gyro() { }

float Gyro::readX() {
    /*float x = analogRead(PIN_X);
    avgX += x;
    sampleX++;
    if (sampleX >= maxSamples) {
        avgX /= sampleX;
        sampleX = 0;
        float temp = min(minX, avgX);
        if (temp < minX) {
            minX = temp;
            recalcX();
        }
        temp = max(maxX, avgX);
        if (temp > maxX) {
            maxX = temp;
            recalcX();
        }
    }
    return calcX(x);*/
    return calcX(analogRead(PIN_X));
}

int Gyro::readRawX() { return analogRead(PIN_X); }

float Gyro::readY() {
    /*float y = analogRead(PIN_Y);
    avgY += y;
    sampleY++;
    if (sampleY >= maxSamples) {
        avgY /= sampleY;
        sampleY = 0;
        float temp = min(minY, avgY);
        if (temp < minY) {
            minY = temp;
            recalcY();
        }
        temp = max(maxY, avgY);
        if (temp > maxY) {
            maxY = temp;
            recalcY();
        }
    }
    return calcY(y);*/
    return calcY(analogRead(PIN_Y));
}

int Gyro::readRawY() { return analogRead(PIN_Y); }

float Gyro::readZ() {
    /*float z = analogRead(PIN_Z);
    avgZ += z;
    sampleZ++;
    if (sampleZ >= maxSamples) {
        avgZ /= sampleZ;
        sampleZ = 0;
        float temp = min(minZ, avgZ);
        if (temp < minZ) {
            minZ = temp;
            recalcZ();
        }
        temp = max(maxZ, avgZ);
        if (temp > maxZ) {
            maxZ = temp;
            recalcZ();
        }
    }
    return calcZ(z);*/
    return calcZ(analogRead(PIN_Z));
}

int Gyro::readRawZ() { return analogRead(PIN_Z); }

float Gyro::calcX(float x) { return (x - zeroX) / scaleX; }

float Gyro::calcY(float y) { return (y - zeroY) / scaleY; }

float Gyro::calcZ(float z) { return (z - zeroZ) / scaleZ; }

void Gyro::recalcX() {
    zeroX = (maxX + minX) / 2.0;
    scaleX = (maxX / 3300) * 330;
}

void Gyro::recalcY() {
    zeroY = (maxY + minY) / 2.0;
    scaleY = (maxY / 3300) * 330;
}

void Gyro::recalcZ() {
    zeroZ = (maxZ + minZ) / 2.0;
    scaleZ = (maxZ / 3300) * 330;
}