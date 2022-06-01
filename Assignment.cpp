

#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>
#include "Rendering.h"

#define PI 3.141592f

void initialize(void) 
{
    float grey[4] = {0.2, 0.2, 0.2, 1.0};
    float white[4]  = {1.0, 1.0, 1.0, 1.0};

//	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

//	Define light's ambient, diffuse, specular properties
    glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

    glEnable(GL_MULTISAMPLE);  

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glClearColor (0.5, 0.5, 1.0, 0.0);  //Background colour

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60., 1.0, 10.0, 1000.0);   //Perspective projection
}


// Camera position and direction
float x = 10.;
float y = 10.;
float z = 10.;

float lx = 0.;
float lz = -1.;

float a = 0.;


Track *trackDir;


float get_dt() {
    static int last_time = glutGet(GLUT_ELAPSED_TIME);
    int current_time = glutGet(GLUT_ELAPSED_TIME);
    int dt_ms = current_time - last_time;
    float dt = (dt_ms / 1000.);
    last_time = current_time;
    return dt;
}


#define WAIT_TIME 5.0 // X seconds of waiting at station

#define STATION_INDEX 1


float time_spent_waiting = 0;
bool is_waiting = false;
float current_time = 100.0;
float time_since_wait = 10.0;

#define TRAIN_SPEED 25.0


void updateWait() {
    float dt = get_dt();

    time_since_wait += dt;

    if (is_waiting) {
        time_spent_waiting += dt;
        time_since_wait = 0.;
        if (time_spent_waiting > WAIT_TIME) {
            is_waiting = false;
        }
        return;
    };

    current_time += dt;
    float time = current_time;
    int sz = trackDir->size();
    float index = fmod(time * TRAIN_SPEED, sz);
    unsigned int lower = ((unsigned int)(index)) % sz;
    unsigned int upper = ((unsigned int)(index) + 1) % sz;

    if ((lower == STATION_INDEX || upper == STATION_INDEX) && time_since_wait > 5.0) {
        is_waiting = true;
        time_spent_waiting = 0;
        return;
    }
}




float bar_value = 1.;

void set_bar_value() {
    bar_value = std::abs(sin((2*PI) * time_spent_waiting / (WAIT_TIME*2)) - 1.);
}


void update(void) {
    updateWait();
    glutPostRedisplay();
    set_bar_value();
}







#define RAD_TO_DEG(x) ((x / (PI)) * 180)


float train_cam_x;
float train_cam_z;

float train_cam_lx;
float train_cam_lz;


void pushTranslateTrain(float time_offset, bool is_first_carrige) {
    glPushMatrix();

    float time = current_time - time_offset;

    int sz = trackDir->size();
    float index = fmod(time * TRAIN_SPEED, sz);

    unsigned int lower = ((unsigned int)(index)) % sz;
    unsigned int upper = ((unsigned int)(index) + 1) % sz;
    float dif = fmod(index, 1);

    vec2 p1 = trackDir->at(lower);
    vec2 p2 = trackDir->at(upper);
    vec2 *lerped = lerp(&p1, &p2, dif);

    glTranslatef(lerped->x, 0., lerped->y);

    float dx, dz;
    dx = p2.x - p1.x;
    dz = p2.y - p1.y;

    float ang = RAD_TO_DEG(atan2(dx, dz));

    if (is_first_carrige) {
        train_cam_x = lerped->x;
        train_cam_z = lerped->y;
        train_cam_lx = lerped->x + dx;
        train_cam_lz = lerped->y + dz;
    }

    delete lerped;

    glRotatef(ang + 90., 0.,1.,0.);
}




void drawEngine() {
    pushTranslateTrain(0., true);

    engine();

    glPopMatrix();
}



#define NUM_WAGONS 25

void drawWagons() {
    for (unsigned int i=1; i<NUM_WAGONS; i++) {
        float u = i;
        pushTranslateTrain(u / 3, false);
        wagon(i);
        glPopMatrix();
    }
}


enum LOOKING {
    MAIN = 0,
    STATION = 1,
    TRAIN = 2
};

enum LOOKING looking = MAIN;

void lookAt() {
    switch (looking) {
        case MAIN:
            gluLookAt (x,y,z, x+lx,y,z+lz, 0.,1.,0.);
            break;
        case TRAIN:
            gluLookAt(train_cam_x, 20.0, train_cam_z, train_cam_lx, 20., train_cam_lz, 0.,1.,0.);
            break;
        case STATION:
            gluLookAt(300., 20., 0., 0., 18., 0., 0.,1.,0.);
            break;
    };
}



void display(void)
{
    float lgt_pos[] = {0.0f, 50.0f, 0.0f, 1.0f};  //light0 position (directly above the origin)

    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    lookAt();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);   //light position

    floor();

    tracks(trackDir);

    drawEngine();		 //locomotive
    drawWagons();  // imagine wagons!

    station();

    bouncy();

    trainBar(bar_value);

    glutSwapBuffers();   //Useful for animation
}


void move(float u, float da) {
    a += da;

    x += lx*u;
    z += lz*u;

    lx = sin(a);
    lz = -cos(a);
}


#define SPD (8.0)

#define AS (0.06)

void special(int key, int _x, int _y) {
    switch (key) {
        case GLUT_KEY_UP:
            move(SPD,0.); break;
        
        case GLUT_KEY_DOWN:
            move(-SPD,0.); break;
            
        case GLUT_KEY_LEFT:
            move(0., -AS);  break;
            
        case GLUT_KEY_RIGHT:
            move(0., AS); break;

        case GLUT_KEY_PAGE_UP:
            y+=SPD; break;

        case GLUT_KEY_PAGE_DOWN:
            y-=SPD; break;
    }
    glutPostRedisplay();
}


void keypressed(unsigned char k, int x, int y) {
    if (k == 'c') {
        looking = (enum LOOKING) ((looking + 1) % 3);
    }
}

//---------------------------------------------------------------------
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize (600, 600); 
    glutInitWindowPosition (50, 50);
    glutCreateWindow ("Toy Train");
    initialize ();
    initializeTextures();

    trackDir = generate_track_direction(250.);

    glutDisplayFunc(display); 
    glutSpecialFunc(special);
    glutKeyboardFunc(keypressed);
    glutIdleFunc(update);
    glutMainLoop();
    return 0;
}

