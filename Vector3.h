#ifndef VECTOR3_H
#define VECTOR3_H

typedef struct {
    float x;
    float y;
    float z;
} Vector3;

Vector3 vector3_add(Vector3 a, Vector3 b);
Vector3 vector3_sub(Vector3 a, Vector3 b);
Vector3 vector3_scale(Vector3 v, float s);
float vector3_distance(Vector3 a, Vector3 b);
float vector3_magnitude(Vector3 v);

#endif
