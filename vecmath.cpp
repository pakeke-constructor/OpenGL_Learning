
#include "vecmath.h"

vec3* cross(vec3 *a, vec3 *b) {
    // Yes, this is a memory leak.
    // Too bad! I don't care!
    // (Actually it's only a memory leak if we forget to delete the returned vector.)
    vec3* r = new vec3();
    r->x = (a->y*b->z - a->z*b->y);
    r->y = (a->z*b->x - a->x*b->z);
    r->z = (a->x*b->y - a->y*b->x);
    return r;
}



float mag(vec3* v) {
    return sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
}

float dist(vec2* a, vec2* b) {
    float x = a->x - b->x;
    float y = a->y - b->y;
    return sqrt(x*x+y*y);
}


void norm(vec3 *v) {
    // normalizes in place
    float m = mag(v);
    v->x = v->x/m;
    v->y = v->y/m;
    v->z = v->z/m;
}


vec3 *mult(vec3 *v, float a) {
    return new vec3({
        v->x * a, v->y * a, v->z * a
    });
}


float dot(vec3* a, vec3* b) {
    return a->x * b->x + a->y * b->y;
}



vec2 *lerp(vec2 *a, vec2 *b, float c) {
    float x = a->x + (b->x - a->x) * c;
    float y = a->y + (b->y - a->y) * c;

    return new vec2({x,y});
}

