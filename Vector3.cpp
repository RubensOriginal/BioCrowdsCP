#include "Vector3.h"
#include <cmath>

Vector3 vector3_normalize(Vector3 a) {
    float magnitude = vector3_magnitude(a);
    return Vector3{a.x/magnitude, a.y/magnitude, a.z/magnitude};
}

float vector3_distance(Vector3 a, Vector3 b) {
    Vector3 diff = a - b;
    return std::sqrt(diff.x*diff.x + diff.y*diff.y + diff.z*diff.z);
}

float vector3_sqr_magnitude(Vector3 a) {
    return a.x*a.x + a.y*a.y + a.z*a.z;
}

float vector3_magnitude(Vector3 a) {
    return std::sqrt(vector3_sqr_magnitude(a));
}

float vector3_dot(Vector3 a, Vector3 b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
