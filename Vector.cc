#include <array>
#include <cmath>

#include "Vector.h"


Vec3f crossProduct(Vec3f u, Vec3f v) {
    Vec3f output;
    output[0] = u[1] * v[2] - u[2] * v[1];
    output[1] = u[2] * v[0] - u[0] * v[2];
    output[2] = u[0] * v[1] - u[1] * v[0];
    return output;
}


Vec3f add(Vec3f u, Vec3f v) {
    Vec3f output;
    output[0] = u[0] + v[0];
    output[1] = u[1] + v[1];
    output[2] = u[2] + v[2];
    return output;
}


Vec3f add(Vec3f v, float k) {
    Vec3f output;
    output[0] = v[0] + k;
    output[1] = v[1] + k;
    output[2] = v[2] + k;
    return output;
}


Vec3f subtract(Vec3f u, Vec3f v) {
    Vec3f output;
    output[0] = u[0] - v[0];
    output[1] = u[1] - v[1];
    output[2] = u[2] - v[2];
    return output;
}


Vec3f subtract(Vec3f v, float k) {
    Vec3f output;
    output[0] = v[0] - k;
    output[1] = v[1] - k;
    output[2] = v[2] - k;
    return output;
}


float norm(Vec3f v) {
    return sqrt(dot(v, v));
}


Vec3f normalize(Vec3f v) {
    return divide(v, norm(v));
}


Vec3f multiply(Vec3f v, float multiple) {
    Vec3f output;
    output[0] = v[0] * multiple;
    output[1] = v[1] * multiple;
    output[2] = v[2] * multiple;
    return output;
}


Vec3f divide(Vec3f v, float denominator) {
    Vec3f output;
    output[0] = v[0] / denominator;
    output[1] = v[1] / denominator;
    output[2] = v[2] / denominator;
    return output;
}


float dot(Vec3f u, Vec3f v) {
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}


Vec3f truncate(Vec3f v, float maximum) {
    Vec3f output;
    output[0] = fmin(v[0], maximum);
    output[1] = fmin(v[1], maximum);
    output[2] = fmin(v[2], maximum);
    return output;
}
