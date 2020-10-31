#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <time.h>
#include "Utils.h"
#include <vector>
#include <fstream>
#include <iostream>

class Cube
{
private:
    bool isEnemy;
    float positionX;
    float positionY;
    float positionZ;
    float r;
    float g;
    float b;
public:
    void setPositionX(float pos)
    {
        this->positionX = pos;
    }

    void setPositionY(float pos)
    {
        this->positionY = pos;
    }

    void setPositionZ(float pos)
    {
        this->positionZ = pos;
    }

    float getPositionX()
    {
        return this->positionX;
    }

    float getPositionY()
    {
        return this->positionY;
    }

    float getPositionZ()
    {
        return this->positionZ;
    }

    void setIsEnemy(bool isEnemy)
    {
        this->isEnemy = isEnemy;
    }

    bool getIsEnemy()
    {
        return isEnemy;
    }

    void setRGB(float r,float g,float b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    void Draw()
    {
        glPushMatrix();
        glTranslatef(this->getPositionX(),this->getPositionY(),this->getPositionZ());
        glScalef(1.0f,0.3f,1.0f);

        glBegin(GL_QUADS);

        glColor3ub(r, g, b);
        glVertex3d(1, 1, 1);
        glVertex3d(1, 1, -1);
        glVertex3d(-1, 1, -1);
        glVertex3d(-1, 1, 1);

        glColor3ub(0, 255, 0);
        glVertex3d(1, -1, 1);
        glVertex3d(1, -1, -1);
        glVertex3d(1, 1, -1);
        glVertex3d(1, 1, 1);

        glColor3ub(0, 0, 255);
        glVertex3d(-1, -1, 1);
        glVertex3d(-1, -1, -1);
        glVertex3d(1, -1, -1);
        glVertex3d(1, -1, 1);

        glColor3ub(255, 255, 0);
        glVertex3d(-1, 1, 1);
        glVertex3d(-1, 1, -1);
        glVertex3d(-1, -1, -1);
        glVertex3d(-1, -1, 1);

        glColor3ub(0, 255, 150);
        glVertex3d(1, 1, -1);
        glVertex3d(1, -1, -1);
        glVertex3d(-1, -1, -1);
        glVertex3d(-1, 1, -1);

        glColor3ub(255, 0, 255);
        glVertex3d(1, -1, 1);
        glVertex3d(1, 1, 1);
        glVertex3d(-1, 1, 1);
        glVertex3d(-1, -1, 1);

        glEnd();
        glPopMatrix();
    }
};

class Player
{
private:
    float positionX;
    float positionY;
    float positionZ;
public:
    void setPositionX(float pos)
    {
        this->positionX = pos;
    }

    void setPositionY(float pos)
    {
        this->positionY = pos;
    }

    void setPositionZ(float pos)
    {
        this->positionZ = pos;
    }

    float getPositionX()
    {
        return this->positionX;
    }

    float getPositionY()
    {
        return this->positionY;
    }

    float getPositionZ()
    {
        return this->positionZ;
    }

    void Draw()
    {
        glPushMatrix();
        glTranslatef(this->getPositionX(),this->getPositionY(),this->getPositionZ());
        glScalef(1.0f,3.0f,1.0f);

        glBegin(GL_QUADS);

        glColor3ub(50, 50, 50);
        glVertex3d(1, 1, 1);
        glVertex3d(1, 1, -1);
        glVertex3d(-1, 1, -1);
        glVertex3d(-1, 1, 1);

        glColor3ub(0, 255, 0);
        glVertex3d(1, -1, 1);
        glVertex3d(1, -1, -1);
        glVertex3d(1, 1, -1);
        glVertex3d(1, 1, 1);

        glColor3ub(0, 0, 255);
        glVertex3d(-1, -1, 1);
        glVertex3d(-1, -1, -1);
        glVertex3d(1, -1, -1);
        glVertex3d(1, -1, 1);

        glColor3ub(255, 255, 0);
        glVertex3d(-1, 1, 1);
        glVertex3d(-1, 1, -1);
        glVertex3d(-1, -1, -1);
        glVertex3d(-1, -1, 1);

        glColor3ub(200, 200, 150);
        glVertex3d(1, 1, -1);
        glVertex3d(1, -1, -1);
        glVertex3d(-1, -1, -1);
        glVertex3d(-1, 1, -1);

        glColor3ub(255, 0, 255);
        glVertex3d(1, -1, 1);
        glVertex3d(1, 1, 1);
        glVertex3d(-1, 1, 1);
        glVertex3d(-1, -1, 1);

        glEnd();
        glPopMatrix();
    }
};

SDL_Window* win;
SDL_GLContext context;

bool isRunning = true;
float inputX = 0;
float inputZ = 0;
int randomBetween;
std::vector<Cube> cubes;

Player player;

void drawFloor();
void setAllCubePositionsAtStart();


int main(int argc, char** argv) {

    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    win = SDL_CreateWindow("OpenGl Test", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    SDL_GLContext context = SDL_GL_CreateContext(win);

    inputX = 0;
    inputZ = 0;

    player.setPositionX(-2.0f);

    srand(time(NULL));

    setAllCubePositionsAtStart();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, (double) 1280 / 720, 1, 1000);
    glEnable(GL_DEPTH_TEST);

    SDL_Event event;
    const Uint8* states = nullptr;

    while (isRunning) {

        glClearColor(0.f, 0.5f, 1.0f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        //glRotatef(inputX * 5.0f,0.0f,1.0f,0.0f);
        //glTranslatef(0, 0, inputZ);
        gluLookAt(0, 30, -30, 0, 0, 0, 0, 1, 0);

        SDL_PollEvent(&event);
        states = SDL_GetKeyboardState(NULL);
        if (event.type == SDL_QUIT)
            isRunning = false;

        if (states[SDL_SCANCODE_LEFT])
            inputX += .2;
        if (states[SDL_SCANCODE_RIGHT])
            inputX -= .2;
        if (states[SDL_SCANCODE_UP])
            inputZ += .2;
        if (states[SDL_SCANCODE_DOWN])
            inputZ -= .2;


        drawFloor();

        player.setPositionX(inputX);
        player.setPositionY(2.0f);
        player.setPositionZ(inputZ);
        player.Draw();

        if(!cubes.empty())
        {
            for (int i = 0; i < cubes.size(); ++i)
            {
                cubes[i].Draw();
            }
        }

        //Utils::dessinerRepere(.5);

        SDL_Delay(3);
        glFlush();
        SDL_GL_SwapWindow(win);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}

void drawFloor()
{
    //FLOOR
    glPushMatrix();
    glTranslatef(0.0f,-1.0f,0.0f);
    glScalef(20.0f,0.0f,20.0f);

    glBegin(GL_QUADS);

    glColor3ub(0, 100, 150); //face green
    glVertex3d(1, -2, -1);
    glVertex3d(1, -2, 1);
    glVertex3d(-1, -2,1);
    glVertex3d(-1, -2, -1);

    glEnd();

    glPopMatrix();
}

void setAllCubePositionsAtStart()
{
    //MAKE CUBES AND ADD IN VECTOR

    float xPos = 24.0f;
    float yPos = -1.0f;
    float zPos = -18.0f;

    for (int i = 0; i < 7; ++i)
    {
        Cube cubeForX;
        xPos -= 6.0f;
        cubeForX.setPositionX(xPos);
        cubeForX.setPositionY(yPos);
        cubeForX.setPositionZ(zPos);

        randomBetween = rand() % (2-1 + 1) + 1;

        if(randomBetween == 1)
        {
            cubeForX.setIsEnemy(true);
            cubeForX.setRGB(255,0,0);
        }
        else
        {
            cubeForX.setRGB(50,100,0);
        }

        cubes.push_back(cubeForX);

        for (int j = 0; j < 6; ++j)
        {
            Cube cubeForZ;

            zPos += 6.0f;
            cubeForZ.setPositionX(cubeForX.getPositionX());
            cubeForZ.setPositionY(yPos);
            cubeForZ.setPositionZ(zPos);

            randomBetween = rand() % (2-1 + 1) + 1;

            if(randomBetween == 1)
            {
                cubeForZ.setIsEnemy(true);
                cubeForZ.setRGB(255,0,0);
            }
            else
            {
                cubeForZ.setRGB(50,100,0);
            }

            cubes.push_back(cubeForZ);
        }

        zPos = -18.0f;
    }
}