#ifndef FLOAT_HPP
#define FLOAT_HPP

#include <stdlib.h>

static const float EPSILON = 10e-3;

bool equal(float a, float b);
bool less_than(float a, float b);
bool greater_than(float a, float b);
bool less_than_or_equal(float a, float b);
bool greater_than_or_equal(float a, float b);

#endif // FLOAT_HPP
