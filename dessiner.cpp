#include <GL/gl.h>
#include <GL/glu.h>
#include <assert.h>
#define GA(param) assert(param)
#include "dessiner.h"
#include "sdlglutils.h"

void LoadText(void){

    GA(textur[0] = loadTexture("stainedglass05.jpg")); // load txtr
    GA(textur[1] = loadTexture("herbe.png")); // load txtr
    GA(textur[2] = loadTexture("carapacer.png")); // load txtr
    GA(textur[3] = loadTexture("ciel.png"));

}

void DessinerRepere(void){

    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    //glLoadIdentity();
    glBegin(GL_LINES);

    glColor3ub(255,0,0); glVertex3d(0,0,0); glVertex3d(3,0,0);
    glColor3ub(0,0,255); glVertex3d(0,0,0); glVertex3d(0,3,0);
    glColor3ub(0,255,0); glVertex3d(0,0,0); glVertex3d(0,0,3);

    glEnd();
    glColor3ub(255,255,255);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}

void DessinerPlayer(void){
    glPushMatrix();

    glTranslated(player.x,player.y,player.z);
    GLUquadric *player = gluNewQuadric();
    gluQuadricTexture(player,GL_TRUE);

    glColor3ub(255,255,255);

    glBindTexture(GL_TEXTURE_2D,textur[0]);
    gluSphere(player,3,20,20);

    gluDeleteQuadric(player);

    glPopMatrix();
}

void DessinerMario(void){
    glPushMatrix();
    //glLoadIdentity();
    //glRotated(cam.angleZ*28.8,0,0,1); // angleZ varie pour 1 tour entre -3.125 et +3.125 (180/6.25=28.8)
    /*
    glTranslated(player.x,player.y,player.z);
    glRotated(-90,0,0,1);
    glTranslated(3,0,0);
    glRotated(90,1,0,0);*/
    //printf("%.1f\n",cam.angleZ);


    glColor3ub(0,0,0);
    /*
    glTranslated(player.x+3.5,player.y+1,player.z);
    glRotated(90,1,0,0);
    glRotated(test,0,1,0);*/
    glScaled(0.05,0.05,0.05);
    //Mario->draw_model(false,false);
    glPopMatrix();

}

void DessinerCarapaceRouge(void){

    glPushMatrix();
    // ROTATION DU REPERE
    glTranslated(3,0,0);
    //glRotated(angleZ,0,0,1);
    //glRotated(angleX,1,0,0);

    glColor3ub(255,255,255);


    GLUquadric *carapacerouge = gluNewQuadric(), *anneaublanc = gluNewQuadric();
    gluQuadricTexture(carapacerouge,GL_TRUE);
    gluQuadricTexture(anneaublanc,GL_FALSE);

    glBindTexture(GL_TEXTURE_2D,textur[2]);
    gluSphere(carapacerouge,1,20,20);

    gluDisk(anneaublanc,0,1.35,10,1);

    gluDeleteQuadric(carapacerouge);
    gluDeleteQuadric(anneaublanc);


    glPopMatrix();

}

void DessinerCarre(void){

    glPushMatrix();
    // ROTATION DU REPERE
    //glRotated(angleZ,0,0,1);
    //glRotated(angleX,1,0,0);

    // Dessin des 6 face du cube (la premiere texture)
    glBindTexture(GL_TEXTURE_2D, textur[0]);
    glBegin(GL_QUADS);


    glColor3ub(255,255,255);

    glTexCoord2d(0,1); glVertex3d(1,1,1);
    glTexCoord2d(0,0); glVertex3d(1,1,-1);
    glTexCoord2d(1,0); glVertex3d(-1,1,-1);
    glTexCoord2d(1,1); glVertex3d(-1,1,1);

    glEnd();



    glBegin(GL_QUADS);
    glColor3ub(0,255,0); //face verte
    glVertex3d(1,-1,1);
    glVertex3d(1,-1,-1);
    glVertex3d(1,1,-1);
    glVertex3d(1,1,1);

    glColor3ub(0,0,255); //face bleue
    glVertex3d(-1,-1,1);
    glVertex3d(-1,-1,-1);
    glVertex3d(1,-1,-1);
    glVertex3d(1,-1,1);

    glColor3ub(255,255,0); //face jaune
    glVertex3d(-1,1,1);
    glVertex3d(-1,1,-1);
    glVertex3d(-1,-1,-1);
    glVertex3d(-1,-1,1);

    glColor3ub(0,255,255); //face cyan
    glVertex3d(1,1,-1);
    glVertex3d(1,-1,-1);
    glVertex3d(-1,-1,-1);
    glVertex3d(-1,1,-1);

    glColor3ub(255,0,255); //face magenta
    glVertex3d(1,-1,1);
    glVertex3d(1,1,1);
    glVertex3d(-1,1,1);
    glVertex3d(-1,-1,1);

    glEnd();

    // ON ANNULE LA ROTATION
    //glRotated(-angleX,1,0,0);
    //glRotated(-angleZ,0,0,1);
    glPopMatrix();

}

void DessinerSol(void){
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);

    GA(textur[1]);
    glBindTexture(GL_TEXTURE_2D, textur[1]);
    glBegin(GL_QUADS);

    //glColor3ub(255,255,255); //face rouge
    glTexCoord2d(80,80); glVertex3d(100,100,-5);
    glTexCoord2d(80,0); glVertex3d(100,-100,-5);
    glTexCoord2d(0,0); glVertex3d(-100,-100,-5);
    glTexCoord2d(0,80); glVertex3d(-100,100,-5);

    glEnd();

    glPopMatrix();
}

void DessinerCiel(void){
    glPushMatrix();


    GLUquadric *ciel = gluNewQuadric();
    gluQuadricTexture(ciel,GL_TRUE);

    //glColor3ub(255,255,255);
    glBindTexture(GL_TEXTURE_2D,textur[3]);
    gluSphere(ciel,80,20,20);

    gluDeleteQuadric(ciel);


    glPopMatrix();
}

void DrawWorld(void){
    //DessinerCarre();
    //DessinerCarapaceRouge();
    DessinerSol();
    //DessinerCiel();
    DessinerRepere();
    //DessinerMario();
    //DessinerPlayer();
}
