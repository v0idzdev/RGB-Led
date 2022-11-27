#include "generator.hpp"
#include <stdlib.h>

// These integers need to have 16 bits
// 8 bit uint = 0 to +255, 16-bit int -36,768 to +32,767
generator_t*
genCreate(int16_t start, int16_t min, int16_t max, int16_t step)
{
  generator_t* gen = (generator_t*)malloc(sizeof *gen);
  gen->min = min;
  gen->max = max;
  gen->current = start;
  gen->step = 1;
  return gen;
}

void
genFree(generator_t* gen)
{
  free(gen);
  gen = NULL;
}

bool
genReachedMax(generator_t* gen)
{
  return gen->current + gen->step > gen->max;
}

bool
genReachedMin(generator_t* gen)
{
  return gen->current + gen->step < gen->min;
}

void
genChangeDirection(generator_t* gen)
{
  gen->step *= -1;
}

void
genUpdateCurrent(generator_t* gen)
{
  gen->current += gen->step;
}

bool
genAdvance(generator_t* gen)
{
  if (genReachedMin(gen) || genReachedMax(gen)) {
    genChangeDirection(gen);
    return false;
  }

  genUpdateCurrent(gen);
  return true;
}