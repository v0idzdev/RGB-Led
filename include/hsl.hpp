#ifndef HSL_HPP
#define HSL_HPP

#include <stdint.h>

typedef struct
{
  uint8_t red, green, blue;

} rgb_t;

typedef struct
{
  int32_t hue;
  float saturation, lightness;

} hsl_t;

#endif