#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>

#include <math.h>
#include <assert.h>

#define TAILLE_FENETRE_L 800
#define TAILLE_FENETRE_H 600
#define FPS_GAME 50
#define DELAY_TIME 1000/FPS_GAME
#define VITESSE 0.02
#define GA(param) assert(param) // Gardien Angel <3
#define INFO(param) if(0) printf(param)

#include "sdlglutils.h"

typedef struct {
  double x,y,z;
} point;

struct camera {
  point eye;
  point at;
  point up;
  double angleZ, angleY;
  double offset;
  double distance;
  double hold;
  double motionSensivity;
  double scrollSensivity;
} my_camera;

point reference;
point player;

camera cam;

GLuint textur[16];
 //en variable globale
//MeshObj *mario; //=new MeshObj("obj/Mario2.obj");
