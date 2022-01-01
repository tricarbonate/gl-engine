#include "../include/float.hpp"

bool equal(float a, float b) {
    return abs(a - b) < EPSILON;
}

bool less_than(float a, float b) {
    return (a - b < 0) && (b - a > EPSILON);
}

bool greater_than(float a, float b) {
    return (b - a < 0) && (a - b > EPSILON);
}

bool less_than_or_equal(float a, float b) {
    return (a - b < 0) || (abs(b - a) < EPSILON);
}

bool greater_than_or_equal(float a, float b) {
    return (b - a < 0) || (abs(b - a) < EPSILON);
}


