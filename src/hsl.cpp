#include "hsl.hpp"

float
hslHueToRgb(float v1, float v2, float vH)
{
  if (vH < 0) {
    vH += 1;
  }

  if (vH > 1) {
    vH -= 1;
  }

  if ((6 * vH) < 1) {
    return (v1 + (v2 - v1) * 6 * vH);
  }

  if ((2 * vH) < 1) {
    return v2;
  }

  if ((3 * vH) < 2) {
    return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);
  }

  return v1;
}

rgb_t
hslToRgb(hsl_t hsl)
{
  rgb_t rgb;

  if (hsl.saturation == 0) {
    rgb.red = rgb.blue = rgb.green = (uint8_t)(hsl.lightness * 255);
    return rgb;
  }

  float v1;
  float v2 = (hsl.lightness * (1 + hsl.saturation));
  float hue = (float)hsl.hue / 360;

  if (hsl.lightness > 0.5) {
    v2 = ((hsl.lightness + hsl.saturation) - (hsl.lightness * hsl.saturation));
  }

  v1 = 2 * hsl.lightness - v2;
  rgb.red = (uint8_t)(255 * hslHueToRgb(v1, v2, hue + (1.0f / 3)));
  rgb.green = (uint8_t)(255 * hslHueToRgb(v1, v2, hue));
  rgb.blue = (uint8_t)(255 * hslHueToRgb(v1, v2, hue - (1.0f / 3)));
  return rgb;
}