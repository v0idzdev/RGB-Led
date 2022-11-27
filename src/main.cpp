#include "util.hpp"
#include <Arduino.h>

#define PWM_FREQUENCY 1000
#define PWM_BIT_PRECISION 8
#define RGB_MAX 255
#define HSL_HUE_INITIAL 0
#define HSL_HUE_STEP 1
#define HSL_HUE_MAX 360
#define HSL_SATURATION 1
#define HSL_LIGHTNESS 0.5
#define LED_DELAY_MS 60

// Define LED pin numbers and their corresponding PWM channels. The nth LED pin
// number corresponds to the nth PWM channel
const uint8_t ledPins[] = { 15, 2, 4 };
const uint8_t pwmChannels[] = { 0, 1, 2 };

// Use HSL colour and convert to RGB. Simply increment the hue and % by 360, and
// store the result of the conversion in red, green, and blue
int16_t hue = HSL_HUE_INITIAL;
uint8_t red = 0, green = 0, blue = 0;

// Increment hue by HSL_HUE_STEP and % by HSL_HUE_MAX
void
updateHue();

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
  hslToRgb(hue, HSL_SATURATION, HSL_LIGHTNESS, &red, &green, &blue);
  updateHue();
  setColour();
  delay(LED_DELAY_MS);
}

void
updateHue()
{
  hue += HSL_HUE_STEP;
  hue %= HSL_HUE_MAX;
}

void
setColour()
{
  ledcWrite(pwmChannels[0], RGB_MAX - red);
  ledcWrite(pwmChannels[1], RGB_MAX - green);
  ledcWrite(pwmChannels[2], RGB_MAX - blue);
}