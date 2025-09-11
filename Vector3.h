#ifndef VECTOR3_H
#define VECTOR3_H
#include "Agent.h"

struct Vector3{
    float x;
    float y;
    float z;

    explicit Vector3(float x = 0.0f, float y= 0.0f, float z= 0.0f)
        : x(x), y(y), z(z)
    {
    }

    Vector3& operator=(const Vector3& a) = default;

    Vector3 operator+(const Vector3& b) const {
        return Vector3(this->x + b.x, this->y + b.y, this->z + b.z);
    }

    Vector3 operator-(const Vector3& b) const {
        return Vector3(this->x - b.x, this->y - b.y, this->z - b.z);
    }

    Vector3 operator*(const float a) const {
        return Vector3(this->x * a, this->y * a, this->z * a);
    }

    Vector3 operator/(const float a) const {
        return Vector3(this->x / a, this->y / a, this->z / a);
    }
};

float vector3_distance(Vector3 a, Vector3 b);
float vector3_sqr_magnitude(Vector3 a);
float vector3_magnitude(Vector3 a);
float vector3_dot(Vector3 a, Vector3 b);

#endif
