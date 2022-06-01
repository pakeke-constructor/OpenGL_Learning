

#ifndef VECMATH
#define VECMATH 1


#include <math.h>

typedef struct vec2 {
	float x,y;
} vec2;

typedef struct vec3 {
	float x,y,z;
} vec3;


vec3* cross(vec3 *a, vec3 *b);

float mag(vec3* v);

void norm(vec3 *v);

float dist(vec2 *a, vec2 *b);

float dot(vec3* a, vec3 *b);

vec3 *mult(vec3 *v, float a);

vec2 *lerp(vec2 *a, vec2 *b, float c);


#endif // VECMATH

