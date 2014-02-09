#ifndef DESSINER_H
#define DESSINER_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

void DrawWorld(void);
void LoadText();

typedef struct {
  double x,y,z;
} point;

typedef struct {
  point eye;
  point at;
  point up;
  double angleZ, angleY;
  double offset;
  double distance;
  double hold;
  double motionSensivity;
  double scrollSensivity;
} camera;


static point reference;
static point player;

static camera cam;

static GLuint textur[16];

#endif // DESSINER_H
