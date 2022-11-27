#ifndef UTIL_HPP
#define UTIL_HPP

#include <stdlib.h>

void
hslToRgb(const int16_t h,
         const float s,
         const float l,
         uint8_t* r,
         uint8_t* g,
         uint8_t* b);

#endif