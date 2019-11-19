#include "AudioTransformer.h"

#include <arduinoFFT.h>

arduinoFFT fft = arduinoFFT();

AudioTransformer::AudioTransformer() { }

void AudioTransformer::transform(double input[], double output[], int samples) {
    fft.Windowing(input, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    fft.Compute(input, output, samples, FFT_FORWARD);
    fft.ComplexToMagnitude(input, output, samples);
}

double AudioTransformer::getPeak(double input[], int frequency, int samples) { return fft.MajorPeak(input, samples, frequency); }