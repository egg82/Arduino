#ifndef FFT_h
#define FFT_h

#define ARM_MATH_CM4
#define FFT_SIZE 4096
#define SAMPLE_RATE 44100

#include <arm_math.h>

class FFT {
    public:
    int16_t input[FFT_SIZE * 2];
    int16_t output[FFT_SIZE];
    FFT();
    void compute();
};

#endif