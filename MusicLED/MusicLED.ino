#include "LEDController.h"
#include "AudioTransformer.h"

#define SAMPLES 128
#define FREQUENCY 10000

AudioTransformer audioTransformer;

CRGB getRandColor() { return CRGB(random8(), random8(), random8()); }

LEDController ledController;
CRGB color = getRandColor();
uint8_t h = 0;
CHSV hue = CHSV(h, 255, 255);

unsigned int samplingPeriod;

void setup() {
    //delay(3000);
    Serial.begin(9600);

    samplingPeriod = round(1000000 * (1.0 / FREQUENCY));
    audioTransformer = AudioTransformer();
    
    ledController = LEDController();
    ledController.clear(CRGB::Black);
}

boolean even = false;

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03

void loop() {
    double input[SAMPLES];
    double output[SAMPLES];
    double peakAmplitude = 0.0;
    for (int i = 0; i < SAMPLES; i++) {
        unsigned long start = micros();
        //input[i] = (double) analogRead(0) / 1023.0;
        input[i] = analogRead(0);
        output[i] = 0;
        peakAmplitude = max(peakAmplitude, analogRead(1));
        while (micros() < start + samplingPeriod) { }
    }

    audioTransformer.transform(input, output, SAMPLES);
    //double peakFreq = audioTransformer.getPeak(input, FREQUENCY, SAMPLES);

    double maxVal = 0.0;
    for (int i = 0; i < SAMPLES; i++) {
        maxVal = max(maxVal, input[i]);
    }

    double bassAvg = 0;
    for (int i = 3; i <= 7; i++) {
        bassAvg += input[i] / maxVal;
    }
    bassAvg /= 5;
    //Serial.print("A: ");
    Serial.println(bassAvg);
    /*if (bassAvg >= 0.2) {
        color = getRandColor();
    }*/
    /*if (peakFreq >= 60 && peakFreq <= 250) {
        color = getRandColor();
    }*/

    peakAmplitude /= 511;
    //printVector(input, SAMPLES >> 1, SCL_FREQUENCY);
    /*Serial.print("A: ");
    Serial.print(peakAmplitude);
    Serial.print(" F: ");
    Serial.println(peakFreq);*/

    /*int lightLEDs = peakAmplitude * NUM_LEDS;

    ledController.clear(CRGB::Black);
    for (int i = NUM_LEDS / 2 - lightLEDs / 2; i < lightLEDs; i++) {
        ledController.setLED(i, color);
    }*/

    for (int i = 0; i < (NUM_LEDS - 1); i++) {
        ledController.setLED(i, i <= peakAmplitude * NUM_LEDS ? color : CRGB::Black);
    }

    ledController.setLED(NUM_LEDS - 1, hue);
    h++;
    hue = CHSV(h, 255, 255);
}

void printVector(double vData[], uint16_t bufferSize, uint8_t scaleType) {
  for (uint16_t i = 0; i < bufferSize; i++) {
    double abscissa;
    switch (scaleType) {
      case SCL_INDEX:
        abscissa = (i * 1.0);
	      break;
      case SCL_TIME:
        abscissa = ((i * 1.0) / FREQUENCY);
        break;
      case SCL_FREQUENCY:
        abscissa = ((i * 1.0 * FREQUENCY) / SAMPLES);
	      break;
    }
    if(scaleType!=SCL_PLOT) {
      Serial.print(abscissa, 6);
      if(scaleType==SCL_FREQUENCY)
        Serial.print("Hz");
      Serial.print(" ");
    }
    Serial.println(vData[i], 4);
  }
  Serial.println();
}