#ifndef Gyro_h
#define Gyro_h

#include <Arduino.h>

#define PIN_X 0
#define PIN_Y 1
#define PIN_Z 2

class Gyro {
    public:
    Gyro();
    Gyro(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
    int readRawX();
    float readX();
    int readRawY();
    float readY();
    int readRawZ();
    float readZ();
    private:
    float minX;
    float minY;
    float minZ;
    float calcX(float x);
    float calcY(float y);
    float calcZ(float z);
    void recalcX();
    void recalcY();
    void recalcZ();
};
#endif