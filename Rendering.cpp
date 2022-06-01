
/*

Used for generating the tracks.

*/


#include <cmath>
#include <GL/freeglut.h>
#include <vector>
#include "Rendering.h"
#include "vecmath.h"
#include "loadBMP.h"


void floor()
{
	float white[4] = {1., 1., 1., 1.};
	float black[4] = {0};
	glColor4f(0.2, 1., 0.1, 1.0);  
	glNormal3f(0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	for(int i = -400; i < 400; i++)
	{
		for(int j = -200;  j < 200; j++)
		{
			glVertex3f(i, 0, j);
			glVertex3f(i, 0, j+1);
			glVertex3f(i+1, 0, j+1);
			glVertex3f(i+1, 0, j);
		}
	}
	glEnd();

}


void loadTexture(GLuint *texRef, std::string texPath)				
{
	glBindTexture(GL_TEXTURE_2D, *texRef);		//Use this texture
    loadBMP(texPath);	
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}




static float give_x(float a, float t) {
	float sint = sin(t);
	return a*cos(t) / (1+sint*sint);
}


static float give_y(float a, float t) {
	float sint = sin(t);
	return a*sint*cos(t) / (1+sint*sint);
}



#define PI 3.141592

static int TRACK_ITER;

#define MAX_ITER (2*PI)



#define TRACKPOINT_SEP 3.0 // Track points should be separated by X



Track* generate_track_direction(float a) {
	/*
	generates a singular line that indicates the directoin of the track.
	Currently, it's an infinity symbol.

	(`a` is the focal length of the inf symbol.)
	*/
	Track* ret = new Track();
	
	// CODE THAT GENERATES INFINITY
	vec2 last = {100000., 1000000.};
	for (float t=0; t<=MAX_ITER; t+=0.0001) {
		vec2 c = {give_x(a,t), give_y(a,t)};
		if (dist(&last, &c) > TRACKPOINT_SEP) {
			ret->push_back(c);
			last = c;
		}
	}

	TRACK_ITER = ret->size();

	return ret;
}


#define DIST_APART 5.0
// the distance that the tracks are apart.

#define THICC 1.0  
// Thickness of rails

#define ELEVATION 1.0f
// elevation of track

#define SLEEPER_WIDTH 10.0f

#define SLEEPER_THICC 2.0f


static void do_quad(vec2 *a, vec2 *b, vec2 *c, vec2 *d) {
	glBegin(GL_QUADS);
	glColor3f(1.0,1.0,0.);
	glNormal3f(0., 1., 0.); // top facing
	glVertex3f(a->x, ELEVATION, a->y);
	glVertex3f(b->x, ELEVATION, b->y);
	glVertex3f(c->x, ELEVATION, c->y);
	glVertex3f(d->x, ELEVATION, d->y);

	glNormal3f(a->x-d->x, 0., a->y-d->y); // side quad 1
	glVertex3f(a->x, 0., a->y);
	glVertex3f(a->x, ELEVATION, a->y);
	glVertex3f(b->x, ELEVATION, b->y);
	glVertex3f(b->x, 0., b->y);

	glNormal3f(d->x-a->x, 0., d->y-a->y);
	glVertex3f(d->x, 0., d->y);
	glVertex3f(d->x, ELEVATION, d->y);
	glVertex3f(c->x, ELEVATION, c->y);
	glVertex3f(c->x, 0., c->y);
	glEnd();
}


#define TUNNEL_RADIUS 32.0

#define TUNNEL_OUTER_RADIUS 40.0

#define TUNNEL_THICC 10.0

#define RAD_TO_DEGREES(x) ((x*180)/(PI))


static void do_tunnel_seg(vec2 *pos, vec2 *dir) {
	glColor3f(0.2,0.2,.95);
	glNormal3f(0.,1.,0.);	

	vec3 up = {0.,1.,0.};
	glBegin(GL_QUADS);

	// to get axis of rotation, we cross product the up vector with the
	// direction vector.
	vec3 dir_copy = {dir->x, 0., dir->y};
	norm(&dir_copy);
	vec3* axis = cross(&up, &dir_copy);

	for (float u=0; u<(PI*2); u+=0.1) {
		float s = sin(u);
		float c = cos(u);
		float s1 = sin(u+0.2);
		float c1 = cos(u+0.2);
		
		float x,y,z;
		float x1,y1,z1;

		x = pos->x + TUNNEL_RADIUS*s*up.x + TUNNEL_RADIUS*c*axis->y;
		y = TUNNEL_RADIUS*s*up.y + TUNNEL_RADIUS*c*axis->y;
		z = pos->y + TUNNEL_RADIUS*s*up.z + TUNNEL_RADIUS*c*axis->z;

		x1 = pos->x + TUNNEL_RADIUS*s1*up.x + TUNNEL_RADIUS*c1*axis->y;
		y1 = TUNNEL_RADIUS*s1*up.y + TUNNEL_RADIUS*c1*axis->y;
		z1 = pos->y + TUNNEL_RADIUS*s1*up.z + TUNNEL_RADIUS*c1*axis->z;

		float sep = TRACKPOINT_SEP + 3.0;

		glNormal3f(x-pos->x, y, z-pos->y);
		glVertex3f(x,y,z);
		glVertex3f(x1,y1,z1);
		glVertex3f(x1+dir_copy.x*sep, y1, z1+dir_copy.z*sep);
		glVertex3f(x+dir_copy.x*sep, y, z+dir_copy.z*sep);

		float ox, oy, oz, ox1, oy1, oz1;
		ox = pos->x + TUNNEL_OUTER_RADIUS*s*up.x + TUNNEL_OUTER_RADIUS*c*axis->y;
		oy = TUNNEL_OUTER_RADIUS*s*up.y + TUNNEL_OUTER_RADIUS*c*axis->y;
		oz = pos->y + TUNNEL_OUTER_RADIUS*s*up.z + TUNNEL_OUTER_RADIUS*c*axis->z;

		ox1 = pos->x + TUNNEL_OUTER_RADIUS*s1*up.x + TUNNEL_OUTER_RADIUS*c1*axis->y;
		oy1 = TUNNEL_OUTER_RADIUS*s1*up.y + TUNNEL_OUTER_RADIUS*c1*axis->y;
		oz1 = pos->y + TUNNEL_OUTER_RADIUS*s1*up.z + TUNNEL_OUTER_RADIUS*c1*axis->z;

		glNormal3f(ox-pos->x, oy, oz-pos->y);
		glVertex3f(ox,oy,oz);
		glVertex3f(ox1,oy1,oz1);
		glVertex3f(ox1+dir_copy.x*sep, oy1, oz1+dir_copy.z*sep);
		glVertex3f(ox+dir_copy.x*sep, oy, oz+dir_copy.z*sep);

		glNormal3f(dir->x, 0., dir->y);
		glVertex3f(ox,oy,oz);
		glVertex3f(ox1,oy1,oz1);
		glVertex3f(x,y,z);
		glVertex3f(x1,y1,z1);

		glVertex3f(x1+dir_copy.x*sep, y1, z1+dir_copy.z*sep);
		glVertex3f(x+dir_copy.x*sep, y, z+dir_copy.z*sep);
		glVertex3f(ox1+dir_copy.x*sep, oy1, oz1+dir_copy.z*sep);
		glVertex3f(ox+dir_copy.x*sep, oy, oz+dir_copy.z*sep);
	};

	delete axis;

	glEnd();
}


static void do_sleeper(vec2 *a, vec2 *b, vec2 *c, vec2 *d) {
	glBegin(GL_QUADS);
	glColor3f(0.8,0.3,0.);
	glNormal3f(0.,1.,0.);
	glVertex3f(a->x, 0.1, a->y);
	glVertex3f(b->x, 0.1, b->y);
	glVertex3f(d->x, 0.1, d->y);
	glVertex3f(c->x, 0.1, c->y);
	glEnd();
}


static void do_seg(vec2 *v1, vec2 *v2, vec2 *v3, vec3 *up) {
	vec3 v3d1 = {
		v2->x-v1->x, 0., v2->y-v1->y // y is z here.
	};

	vec3 v3d2 = {
		v3->x-v2->x, 0., v3->y-v2->y // y is z here.
	};
	
	vec3 *c1 = cross(&v3d1, up);
	vec3 *c2 = cross(&v3d2, up);
	norm(c1);
	norm(c2);

	// x,y represent the unit vector that is perpendicular to the main track line.
	float x = c1->x;
	float y = c1->z;

	norm(&v3d1);

	float nx, nz;
	// nx,ny represent the unit vector that is parellel to the man track line.
	nx = v3d1.x;
	nz = v3d1.z;
	
	// quads for the railway sleepers
	vec2 sa,sb,sc,sd;
	sa = {v1->x + x*SLEEPER_WIDTH, v1->y + y*SLEEPER_WIDTH};
	sb = {v1->x + x*SLEEPER_WIDTH + nx*SLEEPER_THICC, v1->y + y*SLEEPER_WIDTH + nz*SLEEPER_THICC};
	sc = {v1->x - x*SLEEPER_WIDTH, v1->y - y*SLEEPER_WIDTH};
	sd = {v1->x - x*SLEEPER_WIDTH + nx*SLEEPER_THICC, v1->y - y*SLEEPER_WIDTH + nz*SLEEPER_THICC};
	do_sleeper(&sa, &sb, &sc, &sd);

	vec2 a = {v1->x + x * DIST_APART, v1->y + y * DIST_APART};
	vec2 b = {v2->x + x * DIST_APART, v2->y + y * DIST_APART};
	vec2 c = {v2->x + x*DIST_APART + x*THICC, v2->y + y*DIST_APART + y*THICC};
	vec2 d = {v1->x + x*DIST_APART + x*THICC, v1->y + y*DIST_APART + y*THICC};

	do_quad(&a, &b, &c, &d);

	// Change perp vector:
	x = c2->x;
	y = c2->z;

	vec2 e = {v2->x + x * DIST_APART, v2->y + y * DIST_APART};
	vec2 f = {v2->x + x*DIST_APART + x*THICC, v2->y + y*DIST_APART + y*THICC};

	do_quad(&b, &e, &f, &c);



	delete c1, c2;
};


void tracks(Track *track)  
{
	glColor4f(0.0, 0.0, 0.3, 1.0);

	glColor4f(0.0, 0.0, 0.3, 1.0);
    glBegin(GL_QUADS);

	vec3 up = {0.,1.,0.};
	vec3 down = {0.,-1.,0.};

	int sz = track->size();

	for (int i=0; i<sz; i++) {
		vec2 v1 = track->at(i % sz);
		vec2 v2 = track->at((i+1) % sz);
		vec2 v3 = track->at((i+2) % sz);
		
		vec2 dir = {v2.x-v1.x, v2.y-v1.y};

		if (i > sz*6/10 && i < sz*7/10) {
			do_tunnel_seg(&v1, &dir);
		}

		do_seg(&v1, &v2, &v3, &up);
		do_seg(&v1, &v2, &v3, &down);
	}
	
	glEnd();
}



#define NUM_TEXTURES 10

GLuint textures[NUM_TEXTURES];

GLuint *ironTex;
GLuint *roofTex;


void initializeTextures() {
	glGenTextures(NUM_TEXTURES, textures); // Create a Texture object
	loadTexture(textures, "iron.bmp");
	loadTexture(textures + 1, "roof.bmp");
	ironTex = textures;
	roofTex = textures + 1;
}


void base()
{
	glColor3f(0.5,0.5,0.5);
    glPushMatrix();
      glTranslatef(0.0, 4.0, 0.0);
      glScalef(20.0, 2.0, 10.0);     //Size 20x10 units, thickness 2 units.
      glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();					//Connector between wagons
      glTranslatef(11.0, 4.0, 0.0);
      glutSolidCube(2.0);
    glPopMatrix();

    //4 Wheels (radius = 2 units)
	//x, z positions of wheels:
	float wx[4] = {  -8,   8,   -8,    8 }; 
	float wz[4] = { 5.1, 5.1, -5.1, -5.1 };
    glColor4f(0.5, 0., 0., 1.0);    //Wheel color
	GLUquadric *q = gluNewQuadric();   //Disc

	for (int i = 0; i < 4; i++)
	{
		glPushMatrix();
		glTranslatef(wx[i], 2.0, wz[i]);
		gluDisk(q, 0.0, 2.0, 20, 2);
		glPopMatrix();
	}
}



void engine()
{
    base();

    //Cab
    glColor4f(0.0, 0.6, 0.6, 1.0);
    glPushMatrix();
      glTranslatef(7.0, 8.5, 0.0);
      glScalef(6.0, 7.0, 10.0);
      glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(6.0, 14.0, 0.0);
      glScalef(4.0, 4.0, 8.0);
      glutSolidCube(1.0);
    glPopMatrix();

    //Boiler
	GLUquadric *q = gluNewQuadric();   //Cylinder
    glPushMatrix();
      glColor4f(0., 0.3, 0.3, 1.0);
      glTranslatef(4.0, 10.0, 0.0);
      glRotatef(-90.0, 0., 1., 0.);
      gluCylinder(q, 5.0, 5.0, 14.0, 20, 5);
      glTranslatef(0.0, 0.0, 14.0);
      gluDisk(q, 0.0, 5.0, 20, 3);
      glColor4f(1.0, 1.0, 0.0, 1.0);
      glTranslatef(0.0, 4.0, 0.2);
      gluDisk(q, 0.0, 1.0, 20,2);  //headlight!
    glPopMatrix();

	// Chimney

}




void station_base() {
	glPushMatrix();
	glScalef(3.,1.,10.);
	glutSolidCube(2.);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.65, 0., 0.);
	glScalef(.3, 4.8, 10.);
	glutSolidCube(2.);
	glPopMatrix();
}

void station_pillars() {
	for (int u=-2; u<3; u++) {
		glPushMatrix();
		glColor3f(0.,0.5,1.0);
		glTranslatef(0., 5., 3.7*(float)u);
		glScalef(3.,1.,3.);
		glRotatef(90, 1.0,0.,0.);
		glutSolidCylinder(0.2, 5., 30, 100);
		glPopMatrix();
	}
}



#define ROOF_HEIGHT 12.0

void do_roof() {
	glEnable(GL_NORMALIZE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, *roofTex);
	glColor3f(1.,1.,1.);

	glBegin(GL_QUADS);

	// top1
	glNormal3f(1., ROOF_HEIGHT + 1.0, 0.);
	float xmax = 6.0;
	float ymax = 2.0;
	glTexCoord2f(0., 0.); glVertex3f(-1., -1., -1.);
	glTexCoord2f(xmax, 0.); glVertex3f(-1.,-1.,1.);
	glTexCoord2f(xmax, ymax); glVertex3f(0., ROOF_HEIGHT, 1.);
	glTexCoord2f(0., ymax); glVertex3f(0., ROOF_HEIGHT, -1.);

	// top 2
	glNormal3f(-1., ROOF_HEIGHT + 1.0, 0.);
	glTexCoord2f(0., 0.); glVertex3f(1., -1., -1.);
	glTexCoord2f(xmax, 0.); glVertex3f(1., -1., 1.);
	glTexCoord2f(xmax, ymax); glVertex3f(0., ROOF_HEIGHT, 1.);
	glTexCoord2f(0., ymax); glVertex3f(0., ROOF_HEIGHT, -1.);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);

	// base
	glColor3f(0.2,0.2,0.2);

	glNormal3f(0.,-1.,0.);
	glVertex3f(-1.,-1.,-1.);
	glVertex3f(-1.,-1.,1.);
	glVertex3f(1.,-1.,1.);
	glVertex3f(1.,-1.,-1.);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glBegin(GL_TRIANGLES);
	glNormal3f(0., 0., 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(0., ROOF_HEIGHT, 1.0);

	glNormal3f(0., 0., -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(0., ROOF_HEIGHT, -1.0);

	glDisable(GL_NORMALIZE);
	glEnd();
}

void station_roof() {
	glPushMatrix();
	glScalef(3.,0.2,10.);
	glTranslatef(0.,25.,0.);

	do_roof();

	glPopMatrix();
}

void station() {
	glColor3f(0.3,0.3,0.3);
	glPushMatrix();
	glScalef(10.,10.,10.);
	glTranslatef(30.,0.,0.);
	station_base();
	station_pillars();
	station_roof();
	glPopMatrix();
}



#define BOUNCE_HEIGHT 80.0

void bouncy() {
	float t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	glPushMatrix();
	glColor3f(1.0, 0.1, 0.8);
	float ypos = BOUNCE_HEIGHT * std::abs(sin(t*2));
	glTranslatef(-150., 20. + ypos, 0.);
	glutSolidSphere(20., 100, 100);
	glPopMatrix();
}


void trainBar(float a) {
	// `a` is a value from 0 to 1 denoting how far up the bar is.
	// a=1, the bar is up. 0=down.
	glPushMatrix();

	glTranslatef(236., 0.5, 15.);
	glColor3f(1.,1.,0);
	glutSolidCube(2.);
	
	glTranslatef(0., 2., 0.);
	glColor3f(0.,0.,0);
	glutSolidCube(2.);
	
	glTranslatef(0., 2., 0.);
	glColor3f(1.,1.,0);
	glutSolidCube(2.);
	
	glTranslatef(0., 2., 0.);
	glColor3f(0.,0.,0);
	glutSolidCube(2.);

	glTranslatef(0., 2., 0.);
	glColor3f(1.,1.,0);
	glutSolidCube(2.);

	glTranslatef(0., 2., 0.);
	glColor3f(0.,0.,0);
	glutSolidCube(2.);

	glRotatef(90 * a, 0., 0., 1.);
	glTranslatef(10.0, 0., 0.);

	glScalef(10.0, 1.0, 1.0);
	glutSolidCube(2.0);

	glPopMatrix();
}



#define NUM_WAGON_COLS 7

vec3 cols[7] = {
	{0.55, 0.55, 0.55},
	{1.0,0.1, 0.1},
	{0.9, 0.1, 0.9},
	{0.9,0.9,0.9},
	{0.5,1.0,0.5},
	{0.5,0.34,1.0},
	{0.2,0.5,0.9}
};


void wagon(unsigned int i)
{
    base();

	vec3 col = cols[i % NUM_WAGON_COLS];
    glColor4f(col.x, col.y, col.z, 1.0);

    glPushMatrix();
		glTranslatef(0.0, 10.0, 0.0);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, *ironTex);
		
		glBegin(GL_QUADS);
			// top
			float max = 1.0;
            glNormal3f(0.,1.,0.);
			glTexCoord2f(0.,0.); glVertex3f(-9.,10.,-5.);
			glTexCoord2f(0.,max); glVertex3f(-9.,10.,5.);
			glTexCoord2f(max,max); glVertex3f(9.,10.,5.);
			glTexCoord2f(max,0.); glVertex3f(9.,10.,-5.);

			// back
			glNormal3f(1.,0.,0.);
			glTexCoord2f(0.,0.); glVertex3f(9.,-5.,-5.);
			glTexCoord2f(0.,max); glVertex3f(9.,-5.,5.);
			glTexCoord2f(max,max); glVertex3f(9.,10.,5.);
			glTexCoord2f(max,0.); glVertex3f(9.,10.,-5.);

			// front
			glNormal3f(-1.,0.,0.);
			glTexCoord2f(0.,0.); glVertex3f(-9.,-5.,-5.);
			glTexCoord2f(0.,max); glVertex3f(-9.,-5.,5.);
			glTexCoord2f(max,max); glVertex3f(-9.,10.,5.);
			glTexCoord2f(max,0.); glVertex3f(-9.,10.,-5.);

			// back
			glNormal3f(0.,0.,1.);
			glTexCoord2f(0.,0.); glVertex3f(-9.,10.,5.);
			glTexCoord2f(0.,max); glVertex3f(-9.,-5.,5.);
			glTexCoord2f(max,max); glVertex3f(9.,-5.,5.);
			glTexCoord2f(max,0.); glVertex3f(9.,10.,5.);

			// front
			glNormal3f(0.,0.,-1.);
			glTexCoord2f(0.,0.); glVertex3f(-9.,10.,-5.);
			glTexCoord2f(0.,max); glVertex3f(-9.,-5.,-5.);
			glTexCoord2f(max,max); glVertex3f(9.,-5.,-5.);
			glTexCoord2f(max,0.); glVertex3f(9.,10.,-5.);

		glEnd();

		glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}


