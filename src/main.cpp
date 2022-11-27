#include "generator.hpp"
#include <Arduino.h>

#define DEBUG

#define PWM_FREQUENCY 1000
#define PWM_BIT_PRECISION 8
#define RGB_MAX 255
#define RGB_STEP_PER_UPDATE 1
#define LED_DELAY_MS 5

// Define LED pin numbers and their corresponding PWM channels. The nth LED pin
// number corresponds to the nth PWM channel
const uint8_t ledPins[] = { 15, 2, 4 };
const uint8_t pwmChannels[] = { 0, 1, 2 };

// Contains the current red, green, and blue values from 0-255. The structure
// each value is contained in cycles through 0-255 indefinitely
generator_t* rgbValues[3];

// Set the colour using rgbValues
void
setColour();

void
setup()
{
  for (int i = 0; i < 3; i++) {
    ledcSetup(pwmChannels[i], PWM_FREQUENCY, PWM_BIT_PRECISION);
    ledcAttachPin(ledPins[i], pwmChannels[i]);

    rgbValues[i] = genCreate(0, 0, RGB_MAX, RGB_STEP_PER_UPDATE);
  }

#ifdef DEBUG
  Serial.begin(115200);
#endif
}

void
loop()
{
  for (int i = 0; i < 3; i++) {
    if (genAdvance(rgbValues[i])) {
      break;
    }
  }

#ifdef DEBUG
  Serial.printf("(%d, %d, %d)\n",
                rgbValues[0]->current,
                rgbValues[1]->current,
                rgbValues[2]->current);
#endif

  setColour();
  delay(LED_DELAY_MS);
}

void
setColour()
{
  for (int i = 0; i < 3; i++) {
    ledcWrite(pwmChannels[i], RGB_MAX - rgbValues[i]->current);
  }
}