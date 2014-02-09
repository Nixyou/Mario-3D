#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <math.h>
#include <assert.h>

#include "dessiner.h"
#include "sdlglutils.h"

#define TAILLE_FENETRE_L 800
#define TAILLE_FENETRE_H 600
#define FPS_GAME 50
#define DELAY_TIME 1000/FPS_GAME
#define VITESSE 0.02
#define GA(param) assert(param) // Gardien Angel <3
#define INFO(param) if(0) printf(param)

 //en variable globale

//MeshObj *mario; //=new MeshObj("obj/Mario2.obj");


void update_cam(void);
void idle(Uint32 last_time, Uint32 current_time, Uint32 ellapsed_time, Uint32 start_time);
void init(void);


void update_cam(void) {
  // On met à jour la position de la caméra, elle décrit un cercle autour de ce qu'elle regarde
  cam.eye.x = cam.at.x + cos(cam.angleZ) * cam.distance;
  cam.eye.z = cam.at.z + reference.z + sin(cam.angleY) * cam.distance;
  cam.eye.y = cam.at.y + sin(cam.angleZ) * cam.distance;

  // Si on veut voir un peu plus loin, on ne centre pas la caméra sur le joueur mais sur un point qui se trouve devant le joueur (on l'appel l'offset, le cône bleu)
  cam.at.x = player.x - cos(cam.angleZ) * cam.offset;
  cam.at.z = player.z;
  cam.at.y = player.y - sin(cam.angleZ) * cam.offset;

  glRotated(cam.angleY,1,0,0);
}

void Dessiner(void){
    // ** Initialisation **
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable(GL_TEXTURE_2D);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

    update_cam();

    gluLookAt(cam.eye.x,cam.eye.y,cam.eye.z,
                cam.at.x,cam.at.y,cam.at.z,
                cam.up.x,cam.up.y,cam.up.z);

    DrawWorld();

    // Message de fin
    glFlush();
    SDL_GL_SwapBuffers();
}

void idle(Uint32 last_time, Uint32 current_time, Uint32 ellapsed_time, Uint32 start_time){
    current_time = SDL_GetTicks(); // on prend le temps actuel 110ms
    ellapsed_time = current_time - last_time; // le temps passe est donc 110-100=10ms
    last_time = current_time; // last time devient 110ms

    Dessiner();

    ellapsed_time = SDL_GetTicks() - start_time; // temps passe deviens 150-100=50ms
    if (ellapsed_time < DELAY_TIME) // admettons elapsed time
    {
        SDL_Delay(DELAY_TIME - ellapsed_time);// du coup on freeze pour avoir 1 image toutes les 10ms
    }
}

void init(void){

    //mario=new MeshObj("obj/Mario.obj"); //OBJ

    player.x=0;
    player.y=0;
    player.z=-5;

    // init cam
    reference.x = 0;
    reference.y = 0;
    reference.z = 10;

    cam.up.x = 0;
    cam.up.y = 0;
    cam.up.z = 1;

    cam.distance = 20;
    cam.offset = 5;
    cam.motionSensivity = 0.01;
    cam.scrollSensivity = 1;
}

int main(int argc, char *argv[]){
    SDL_Event event;
    Uint32 start_time, current_time, ellapsed_time, last_time = SDL_GetTicks();

    SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);

    SDL_WM_SetCaption("Mario 1.0 by FICHERA Benjamin", NULL);
    SDL_SetVideoMode(800, 600, 32, SDL_OPENGL); // 640*480
    //initFullScreen(&width,&height);
    SDL_EnableKeyRepeat(10, 10);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(70,(double)800/600,1,1000); //70 base, 90 half life recule, 50 zoom

    glEnable(GL_DEPTH_TEST); // pour que ce qui est devant reste devant
    //glEnable(GL_TEXTURE_2D);

    LoadText();

    init();

    last_time = SDL_GetTicks();
    for (;;)
    {
        start_time = SDL_GetTicks(); // il est  100ms

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                exit(0);
                break;
                case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        exit(0);
                        break;
                    case SDLK_z: // devant
                    player.x += (cam.at.x-cam.eye.x)*VITESSE;
                    player.y += (cam.at.y-cam.eye.y)*VITESSE;
                    break;
                    case SDLK_s: // derriere
                    player.x -= (cam.at.x-cam.eye.x)*VITESSE;
                    player.y -= (cam.at.y-cam.eye.y)*VITESSE;
                    break;
                    case SDLK_q: // gauche
                    player.y += (cam.at.x-cam.eye.x)*VITESSE;
                    player.x -= (cam.at.y-cam.eye.y)*VITESSE;
                    break;
                    case SDLK_d: // droite
                    player.y -= (cam.at.x-cam.eye.x)*VITESSE;
                    player.x += (cam.at.y-cam.eye.y)*VITESSE;
                    break;
                    case SDLK_a: // gauche
                    cam.angleZ += 0.03;
                    break;
                    case SDLK_e: // droite
                    cam.angleZ -= 0.03;
                    break;
                    default:
                    break;
                }
                break;
                case SDL_MOUSEMOTION: // trackball
                    if (cam.hold)
                    {
                        cam.angleZ -= event.motion.xrel*cam.motionSensivity;
                        cam.angleY += event.motion.yrel*cam.motionSensivity;
                        printf("%.1f\n",cam.angleY);
                        if(cam.angleY>1) cam.angleY=1;
                        if(cam.angleY<-0.3) cam.angleY=-0.3;
                        if(cam.angleZ>3.125) cam.angleZ=3.125;
                        if(cam.angleZ<-3.125) cam.angleZ=-3.125;
                    }
                break;
                case SDL_MOUSEBUTTONUP:
                if(cam.hold)
                {
                    cam.hold = false;
                    SDL_ShowCursor(SDL_ENABLE);
                }
                break;
                case SDL_MOUSEBUTTONDOWN:
                if(!cam.hold){
                    cam.hold = true;
                    SDL_ShowCursor(SDL_DISABLE);
                }
                if(event.button.button == SDL_BUTTON_WHEELUP){
                    cam.distance -= cam.scrollSensivity;
                    if(cam.distance < 14) cam.distance = 14;
                }
                if(event.button.button == SDL_BUTTON_WHEELDOWN){
                    cam.distance += cam.scrollSensivity;
                    if(cam.distance > 29) cam.distance = 29;
                }

            }
        }
        idle(last_time, current_time, ellapsed_time, start_time);
    }

    getchar();
    return 0;
}
