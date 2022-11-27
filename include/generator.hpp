#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <stdlib.h>

typedef struct
{
  int16_t current, min, max, step;
} generator_t;

generator_t*
genCreate(int16_t start, int16_t min, int16_t max, int16_t step);

void
genFree(generator_t* gen);

bool
genReachedMax(generator_t* gen);

bool
genReachedMin(generator_t* gen);

void
genChangeDirection(generator_t* gen);

void
genUpdateCurrent(generator_t* gen);

bool
genAdvance(generator_t* gen);

#endif