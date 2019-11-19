#ifndef LEDController_h
#define LEDController_h

#include <FastLED.h>

enum Pattern {
    HUE_SHIFT, // Shift between rainbow colors
    BLINK, // Blink a specific color
    FADE, // Fade in/out a specific color
    FADE_SHIFT, // Fade in/out between random colors
    NONE
};

class LEDController {
    private:
    CRGB getRandColor();
    void reset(Pattern p);
    void display();
    public:
    LEDController();
    void clear(CHSV hue);
    Pattern getPattern();
    void setPattern(Pattern p);
    void loop();
};
#endif