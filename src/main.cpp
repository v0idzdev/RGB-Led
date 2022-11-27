#include "util.hpp"
#include <Arduino.h>

#define PIN_RED 15
#define PIN_GREEN 2
#define PIN_BLUE 4
#define PIN_ANALOG_IN 27
#define PWM_FREQUENCY 1000
#define PWM_BIT_PRECISION 12
#define PWM_BIT_PRECISION_RANGE pow(2, PWM_BIT_PRECISION)
#define PWM_CHANNEL_RED 0
#define PWM_CHANNEL_GREEN 1
#define PWM_CHANNEL_BLUE 2
#define RGB_MAX 255
#define HSL_HUE_INITIAL 0
#define HSL_HUE_STEP 1
#define HSL_HUE_MAX 360
#define HSL_SATURATION 1
#define HSL_LIGHTNESS 0.5
#define LED_DELAY_MS 60

// Define LED pin numbers and their corresponding PWM channels. The nth LED pin
// number corresponds to the nth PWM channel
const uint8_t ledPins[] = { PIN_RED, PIN_GREEN, PIN_BLUE };
const uint8_t pwmChannels[] = { PWM_CHANNEL_RED,
                                PWM_CHANNEL_GREEN,
                                PWM_CHANNEL_BLUE };

// Use HSL colour and convert to RGB. Simply increment the hue and % by 360, and
// store the result of the conversion in red, green, and blue
int16_t hue;
uint8_t red = 0, green = 0, blue = 0;

inline float
normalise(float value, float min, float max);

// Set the colour of the RGB LED
void
setColour();

void
setup()
{
  // Initialise PWM channels and attach them to their respective pins
  for (int i = 0; i < 3; i++) {
    ledcSetup(pwmChannels[i], PWM_FREQUENCY, PWM_BIT_PRECISION);
    ledcAttachPin(ledPins[i], pwmChannels[i]);
  }
}

void
loop()
{
  float adc = analogRead(PIN_ANALOG_IN);
  float hue = normalise(adc, 0, PWM_BIT_PRECISION_RANGE) * 360;

  hslToRgb(hue, HSL_SATURATION, HSL_LIGHTNESS, &red, &green, &blue);
  setColour();
  delay(LED_DELAY_MS);
}

inline float
normalise(float value, float min, float max)
{
  return (value - min) / (max - min);
}

void
setColour()
{
  ledcWrite(pwmChannels[0], RGB_MAX - red);
  ledcWrite(pwmChannels[1], RGB_MAX - green);
  ledcWrite(pwmChannels[2], RGB_MAX - blue);
}