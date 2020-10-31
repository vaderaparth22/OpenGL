#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Utils.h"
#include "utils/sdlglutils.h"

SDL_Window* win;
SDL_GLContext context;

bool isRunning = true;
float dxCamera = 0;
float dyCamera = 0;
float angleRotationCamera = 0;

const int CITY_W = 4;
const int CITY_H = 4;


static const int citymap[CITY_W][CITY_H] = {
        { 1, 0, 3, 4 },
        { 2, 0, 4, 5 },
        { 1, 0, 2, 1 },
        { 2, 3, 4, 7 }
};

void drawCube(); // forward declaration
void drawPyramid();

void drawMap() {

    glPushMatrix();
    glScaled(2, 2, 1);
    for (int i = 0; i < CITY_W; i++) {
        for (int j = 0; j < CITY_H; j++) {
            int value = citymap[i][j];
            if (value != 0) {
                glPushMatrix();
                glTranslated(i, j, 1);
                glScaled(0.4, 0.4, value);
                drawCube();
                glPopMatrix();
            }
        }
    }
    glPopMatrix();
}


void drawCube() {
    glBegin(GL_QUADS);

    glColor3ub(255, 0, 0); //face rouge
    glVertex3d(1, 1, 1);
    glVertex3d(1, 1, -1);
    glVertex3d(-1, 1, -1);
    glVertex3d(-1, 1, 1);

    glColor3ub(0, 255, 0); //face verte
    glVertex3d(1, -1, 1);
    glVertex3d(1, -1, -1);
    glVertex3d(1, 1, -1);
    glVertex3d(1, 1, 1);

    glColor3ub(0, 0, 255); //face bleue
    glVertex3d(-1, -1, 1);
    glVertex3d(-1, -1, -1);
    glVertex3d(1, -1, -1);
    glVertex3d(1, -1, 1);

    glColor3ub(255, 255, 0); //face jaune
    glVertex3d(-1, 1, 1);
    glVertex3d(-1, 1, -1);
    glVertex3d(-1, -1, -1);
    glVertex3d(-1, -1, 1);

    glColor3ub(0, 255, 255); //face cyan
    glVertex3d(1, 1, -1);
    glVertex3d(1, -1, -1);
    glVertex3d(-1, -1, -1);
    glVertex3d(-1, 1, -1);

    glColor3ub(255, 0, 255); //face magenta
    glVertex3d(1, -1, 1);
    glVertex3d(1, 1, 1);
    glVertex3d(-1, 1, 1);
    glVertex3d(-1, -1, 1);

    glEnd();
}

void drawPyramid() {
    glBegin(GL_TRIANGLES);
    //Triangle 1
    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);   //V0(red)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f(-1.0f,-1.0f, 1.0f);   //V1(green)
    glColor3f(0.0f,0.0f,1.0f); glVertex3f( 1.0f,-1.0f, 1.0f);   //V2(blue)
    //Triangle 2
    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);   //V0(red)
    glColor3f(0.0f,0.0f,1.0f); glVertex3f( 1.0f,-1.0f, 1.0f);   //V2(blue)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f( 1.0f,-1.0f,-1.0f);   //V3(green)
    //Triangle 3
    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);   //V0(red)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f( 1.0f,-1.0f,-1.0f);   //V3(green)
    glColor3f(0.0f,0.0f,1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);   //V4(blue)
    //Triangle 4
    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);   //V0(red)
    glColor3f(0.0f,0.0f,1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);   //V4(blue)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f(-1.0f,-1.0f, 1.0f);   //V1(green)
    glEnd();
}

void drawCylinder() {
    static GLUquadricObj* cylinder = gluNewQuadric();
    glColor3f(1.0, 1.0, 1.0);
    gluCylinder(cylinder, 1.0, 1, 3, 30, 30);
    gluQuadricDrawStyle(cylinder, GLU_FILL);
}

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    win = SDL_CreateWindow("OpenGl Test", SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    SDL_GLContext context = SDL_GL_CreateContext(win);
//    SDL_GL_SetSwapInterval(1);
    //charger la matrice de transformation
    dxCamera = 0;
    dyCamera = 0;

    GLuint idTextureSol = loadTexture("assets/img/herbe.jpg");
    GLuint idTextureSkyBox = loadTexture("assets/img/skybox.jpg");


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, (double) 800 / 600, 1, 1000);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    SDL_Event event;
    const Uint8* states = nullptr;
    while (isRunning) {
        //effacer le tampon d’affichage
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();


       //glPushMatrix();


        glRotated(angleRotationCamera, 0,0,1);
        gluLookAt(dxCamera+4, dyCamera+4,4, dxCamera, dyCamera, 4, 0, 0, 1);


      // glPopMatrix();

        //gestion evenement
        SDL_PollEvent(&event);
        states = SDL_GetKeyboardState(NULL);
        if (event.type == SDL_QUIT)
            isRunning = false;

        if (states[SDL_SCANCODE_LEFT])
            dxCamera += .5;
        if (states[SDL_SCANCODE_RIGHT])
            dxCamera -= .5;
        if (states[SDL_SCANCODE_UP])
            dyCamera -= .5;
        if (states[SDL_SCANCODE_DOWN])
            dyCamera += .5;




        //dessin

        //sol
//        //binder la texture
//        glBindTexture(GL_TEXTURE_2D, idTextureSol);
//        glBegin(GL_QUADS);
//        glColor3ub(255, 255, 255);
//        glTexCoord2d(0,0); glVertex3d(75, -75, -2);
//        glTexCoord2d(10,0); glVertex3d(75, 75, -2);
//        glTexCoord2d(10,10); glVertex3d(-75, 75,-2);
//        glTexCoord2d(0,10); glVertex3d(-75, -75, -2);
//        glEnd();

        //drawMap();
        drawPyramid();

        glPushMatrix();
        glTranslatef(dxCamera, dyCamera, 0);

        glBegin(GL_QUADS);

        glColor3ub(255, 0, 0); //face rouge
        glVertex3d(1, 1, 1);
        glVertex3d(1, 1, -1);
        glVertex3d(-1, 1, -1);
        glVertex3d(-1, 1, 1);

        glColor3ub(0, 255, 0); //face verte
        glVertex3d(1, -1, 1);
        glVertex3d(1, -1, -1);
        glVertex3d(1, 1, -1);
        glVertex3d(1, 1, 1);

        glColor3ub(0, 0, 255); //face bleue
        glVertex3d(-1, -1, 1);
        glVertex3d(-1, -1, -1);
        glVertex3d(1, -1, -1);
        glVertex3d(1, -1, 1);

        glColor3ub(255, 255, 0); //face jaune
        glVertex3d(-1, 1, 1);
        glVertex3d(-1, 1, -1);
        glVertex3d(-1, -1, -1);
        glVertex3d(-1, -1, 1);

        glColor3ub(0, 255, 255); //face cyan
        glVertex3d(1, 1, -1);
        glVertex3d(1, -1, -1);
        glVertex3d(-1, -1, -1);
        glVertex3d(-1, 1, -1);

        glColor3ub(255, 0, 255); //face magenta
        glVertex3d(1, -1, 1);
        glVertex3d(1, 1, 1);
        glVertex3d(-1, 1, 1);
        glVertex3d(-1, -1, 1);

        glEnd();

        glPushMatrix();
        drawCylinder();
        glPopMatrix();

        glPopMatrix();

//
//        Utils::dessinerRepere(.5);



//Dessin SkyBox

        glBindTexture(GL_TEXTURE_2D, idTextureSkyBox);
        glBegin(GL_QUADS);

        glColor3ub(255, 255, 255);
        glTexCoord2d(.75,.66); glVertex3d(75, 75, 75);
        glTexCoord2d(.75,.33); glVertex3d(75, 75, -75);
        glTexCoord2d(1, .33); glVertex3d(-75, 75, -75);
        glTexCoord2d(1,.66); glVertex3d(-75, 75, 75);


        glTexCoord2d(0,.66);glVertex3d(75, -75, 75);
        glTexCoord2d(0,.33);glVertex3d(75, -75, -75);
        glTexCoord2d(.25,.33);glVertex3d(75, 75, -75);
        glTexCoord2d(.25,.66);glVertex3d(75, 75, 75);

//        glColor3ub(0, 0, 255); //face bleue
        glTexCoord2d(0.25,.66);glVertex3d(-75, -75, 75);
        glTexCoord2d(0.25,.33);glVertex3d(-75, -75, -75);
        glTexCoord2d(0.5,.33);glVertex3d(75, -75, -75);
        glTexCoord2d(0.5,.66);glVertex3d(75, -75, 75);

//        glColor3ub(255, 255, 0); //face jaune
        glTexCoord2d(0.5,.66);glVertex3d(-75, 75, 75);
        glTexCoord2d(0.5,.33);glVertex3d(-75, 75, -75);
        glTexCoord2d(0.75,.33);glVertex3d(-75, -75, -75);
        glTexCoord2d(0.75,.66);glVertex3d(-75, -75, 75);

//        glColor3ub(0, 255, 255); //face cyan
        glTexCoord2d(0.25,.33);glVertex3d(75, 75, -75);
        glTexCoord2d(0.25,0);glVertex3d(75, -75, -75);
        glTexCoord2d(0.5,0);glVertex3d(-75, -75, -75);
        glTexCoord2d(0.5,.33);glVertex3d(-75, 75, -75);

//        glColor3ub(255, 0, 255); //face magenta
        glTexCoord2d(0.25,1);glVertex3d(75, -75, 75);
        glTexCoord2d(0.25,.66);glVertex3d(75, 75, 75);
        glTexCoord2d(0.5,.66);glVertex3d(-75, 75, 75);
        glTexCoord2d(0.5,1);glVertex3d(-75, -75, 75);

        glEnd();

        //pause
        SDL_Delay(3);
        //mise a jour de l'ecran
        glFlush();
        SDL_GL_SwapWindow(win);
    }
    //vider la memoire

    glDeleteTextures(1, &idTextureSol);
    glDeleteTextures(1, &idTextureSkyBox);

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
    return 0;
}