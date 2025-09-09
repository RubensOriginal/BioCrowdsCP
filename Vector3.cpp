#include "Vector3.h"
#include <cmath>

Vector3 vector3_add(Vector3 a, Vector3 b) {
    Vector3 res = {a.x + b.x, a.y + b.y, a.z + b.z};
    return res;
}

Vector3 vector3_sub(Vector3 a, Vector3 b) {
    Vector3 res = {a.x - b.x, a.y - b.y, a.z - b.z};
    return res;
}

Vector3 vector3_scale(Vector3 v, float s) {
    Vector3 res = {v.x * s, v.y * s, v.z * s};
    return res;
}

float vector3_distance(Vector3 a, Vector3 b) {
    Vector3 diff = vector3_sub(a, b);
    return std::sqrt(diff.x*diff.x + diff.y*diff.y + diff.z*diff.z);
}

float vector3_magnitude(Vector3 a) {
    return a.x*a.x + a.y*a.y + a.z*a.z;
}
