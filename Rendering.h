

#ifndef RENDERING
#define RENDERING


#include "vecmath.h"

#include <vector>

typedef std::vector<vec2> Track;


void floor(); // renders the floor


Track* generate_track_direction(float); // generates track direction.

void tracks(Track* t) ;  // renders the tracks


void engine();

void wagon(unsigned int i);

void initializeTextures();

void station();

void bouncy();

void trainBar(float a);

#endif

