#ifndef __PERLIN_H__
#define __PERLIN_H__

#include <vector>
#include <math.h>

double fade(double t);
double lerp(double t, double a, double b);
double grad(int hash, double x, double y, double z);

double perlin_noise(float x, float y, std::vector<int> &p);

std::vector<int> get_permutation_vector();

#endif // __PERLIN_H__
