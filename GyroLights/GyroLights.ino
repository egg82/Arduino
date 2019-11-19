#include "LEDController.h"
#include "Gyro.h"

LEDController ledController;
Gyro gyro;

CRGB getRandColor() { return CRGB(random8(), random8(), random8()); }

void setup() {
    Serial.begin(9600);

    ledController = LEDController();
    ledController.clear(CRGB::Black);

    gyro = Gyro();
    //gyro = Gyro(252.0, 457.0, 230.0, 473.0, 242.0, 455.0);
}

void loop() {
    /*float x = gyro.readX();
    float y = gyro.readY();
    float z = gyro.readZ();
    Serial.print("X: ");
    Serial.print(x);
    Serial.print(", Y: ");
    Serial.print(y);
    Serial.print(", Z: ");
    Serial.println(z);
    delay(1);*/
    
    /*for (int i = 0; i < NUM_LEDS; i++) {
        ledController.setLED(i, getRandColor());
        delay(50);
    }*/

    /*float x = gyro.readX();
    Serial.print("X: ");
    Serial.print(x);
    float y = gyro.readY();
    Serial.print(", Y: ");
    Serial.print(y);
    float z = gyro.readZ();
    Serial.print(", Z: ");
    Serial.println(z);
    delay(50);*/

    /*delay(15000);
    Serial.println("Min");
    float min = 3.40282347e+38F;
    for (int i = 0; i < 128; i++) {
        float num;
        for (int j = 0; j < 16; j++) {
            num += gyro.readX();
            delay(10);
        }
        num /= 16;
        min = min(min, num);
    }

    Serial.println("Max");
    delay(5000);
    float max = -3.4028235e+38F;
    for (int i = 0; i < 128; i++) {
        float num;
        for (int j = 0; j < 16; j++) {
            num += gyro.readX();
            delay(10);
        }
        num /= 16;
        max = max(max, num);   
    }

    Serial.print("X Min: ");
    Serial.println(min);
    Serial.print("X Max: ");
    Serial.println(max);
    delay(300000);*/

    float min, max;

    delay(15000);
    Serial.println("X Min");
    delay(5000);
    Serial.println("Start");
    min = 3.40282347e+38F;
    for (int i = 0; i < 20480; i++) {
        min = min(min, gyro.readRawX());
        delay(1);
    }
    Serial.println("X Max");
    delay(5000);
    Serial.println("Start");
    max = -3.4028235e+38F;
    for (int i = 0; i < 20480; i++) {
        max = max(max, gyro.readRawX());
        delay(1);
    }
    Serial.print("X: ");
    Serial.print(min);
    Serial.print(", ");
    Serial.println(max);

    Serial.println("Y Min");
    delay(5000);
    Serial.println("Start");
    min = 3.40282347e+38F;
    for (int i = 0; i < 20480; i++) {
        min = min(min, gyro.readRawY());
        delay(1);
    }
    Serial.println("Y Max");
    delay(5000);
    Serial.println("Start");
    max = -3.4028235e+38F;
    for (int i = 0; i < 20480; i++) {
        max = max(max, gyro.readRawY());
        delay(1);
    }
    Serial.print("Y: ");
    Serial.print(min);
    Serial.print(", ");
    Serial.println(max);

    Serial.println("Z Min");
    delay(5000);
    Serial.println("Start");
    min = 3.40282347e+38F;
    for (int i = 0; i < 20480; i++) {
        min = min(min, gyro.readRawZ());
        delay(1);
    }
    Serial.println("Z Max");
    delay(5000);
    Serial.println("Start");
    max = -3.4028235e+38F;
    for (int i = 0; i < 20480; i++) {
        max = max(max, gyro.readRawZ());
        delay(1);
    }
    Serial.print("Z: ");
    Serial.print(min);
    Serial.print(", ");
    Serial.println(max);

    delay(300000);
}