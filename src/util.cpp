#include "util.hpp"

static float
hueToRgb(float p, float q, float t)
{
  if (t < 0) {
    t += 1;
  }
  if (t > 1) {
    t -= 1;
  }
  if (t < 1. / 6) {
    return p + (q - p) * 6 * t;
  }
  if (t < 1. / 2) {
    return q;
  }
  if (t < 2. / 3) {
    return p + (q - p) * (2. / 3 - t) * 6;
  }

  return p;
}

void
hslToRgb(const int16_t _h,
         const float s,
         const float l,
         uint8_t* r,
         uint8_t* g,
         uint8_t* b)
{
  if (0 == s) {
    *r = *g = *b = l; // Achromatic
  } else {
    float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
    float p = 2 * l - q;
    float h = (float)_h / 360;
    *r = hueToRgb(p, q, h + 1. / 3) * 255;
    *g = hueToRgb(p, q, h) * 255;
    *b = hueToRgb(p, q, h - 1. / 3) * 255;
  }
}