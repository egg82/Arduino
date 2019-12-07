#ifndef FFT_h
#define FFT_h

#define ARM_MATH_CM4
#define FFT_SIZE 1024
#define SAMPLE_RATE 44100

#include <Arduino.h>
#include <arm_math.h>

class FFT {
    public:
    int16_t input[FFT_SIZE * 2];
    int16_t output[FFT_SIZE];
    FFT();
    void compute(int16_t *result, uint32_t *index);
};

#endif