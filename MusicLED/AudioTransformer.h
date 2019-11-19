#ifndef AudioTransformer_h
#define AudioTransformer_h

class AudioTransformer {
    public:
    AudioTransformer();
    void transform(double input[], double output[], int samples);
    double getPeak(double input[], int frequency, int samples);
};
#endif