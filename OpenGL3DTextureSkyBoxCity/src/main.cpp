#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Utils.h"
#include "utils/sdlglutils.h"
#include <vector>
#include <time.h>
#include <iostream>

class Player
{
private:
    float posX;
    float posY;
    float posZ;

public:
    void draw()
    {
        glPushMatrix();
        glTranslatef(this->getPosX(),this->getPosY(),this->getPosZ());
        glScaled(1,2,1);

        glBegin(GL_QUADS);
        glColor3ub(255, 0, 255); //face rouge
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

        glColor3ub(120, 120, 120); //face jaune
        glVertex3d(-1, 1, 1);
        glVertex3d(-1, 1, -1);
        glVertex3d(-1, -1, -1);
        glVertex3d(-1, -1, 1);

        glColor3ub(120, 255, 120); //face cyan
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
        glPopMatrix();
    }

    float getPosX() const {
        return posX;
    }

    void setPosX(float posX) {
        Player::posX = posX;
    }

    float getPosY() const {
        return posY;
    }

    void setPosY(float posY) {
        Player::posY = posY;
    }

    float getPosZ() const {
        return posZ;
    }

    void setPosZ(float posZ) {
        Player::posZ = posZ;
    }
};

class Ground
{
private:
    float posX;
    float posY;
    float posZ;

public:
    void draw(GLuint textureId)
    {
        //FLOOR
        glPushMatrix();
        glTranslatef(0.0f,-5.0f,0.0f);
        glScalef(20.0f,0.0f,20.0f);

        setPosX(0.0f);
        setPosY(-5.0f);
        setPosZ(0.0f);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureId);

        glBegin(GL_QUADS);

        glColor3ub(255, 255, 255);
        glTexCoord2f(0.0, 0.0);
        glVertex3d(1, -2, -1);
        glTexCoord2f(1.0, 0);
        glVertex3d(1, -2, 1);
        glTexCoord2f(1.0, 1.0);
        glVertex3d(-1, -2,1);
        glTexCoord2f(0.0, 1.0);
        glVertex3d(-1, -2, -1);

        glEnd();

        glDisable(GL_TEXTURE_2D);

        glPopMatrix();
    }

    float getPosX() const {
        return posX;
    }

    void setPosX(float posX) {
        Ground::posX = posX;
    }

    float getPosY() const {
        return posY;
    }

    void setPosY(float posY) {
        Ground::posY = posY;
    }

    float getPosZ() const {
        return posZ;
    }

    void setPosZ(float posZ) {
        Ground::posZ = posZ;
    }
};

class Box
{
private:
    float posX;
    float posY;
    float posZ;
    float gravityValue;

public:
    float getPosX() const {
        return posX;
    }

    void setPosX(float posX) {
        Box::posX = posX;
    }

    float getPosY() const {
        return posY;
    }

    void setPosY(float posY) {
        Box::posY = posY;
    }

    float getPosZ() const {
        return posZ;
    }

    void setPosZ(float posZ) {
        Box::posZ = posZ;
    }

    float getGravityValue() const {
        return gravityValue;
    }

    void setGravityValue(float gravityValue) {
        Box::gravityValue = gravityValue;
    }

    void setRandomXZ()
    {
        float randomX = rand() % 19 + -19;
        float randomZ = rand() % 19 + -19;
        setPosX(randomX);
        setPosZ(randomZ);
    }

    void draw()
    {
        glPushMatrix();
        glTranslatef(this->getPosX(),this->getPosY(),this->getPosZ());

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
        glPopMatrix();
    }

    void setGravity()
    {
        setPosY(getPosY() - getGravityValue());
    }

    bool isColliding(Player player, Ground ground)
    {
        SDL_Rect  myRect;
        myRect.x = getPosX();
        myRect.y = getPosY();
        myRect.w = 1;
        myRect.h = 1;

        SDL_Rect playerRect;
        playerRect.x = player.getPosX();
        playerRect.y = player.getPosY();
        playerRect.w = 2;
        playerRect.h = 5;

        SDL_Rect groundRect;
        groundRect.w = 20;
        groundRect.h = 2;
        groundRect.x = ground.getPosZ() + groundRect.w;
        groundRect.y = ground.getPosY() + groundRect.h;

        if(SDL_HasIntersection(&myRect, &playerRect) || SDL_HasIntersection(&myRect, &groundRect))
        {
            return true;
        }

        return false;
    }
};



SDL_Window* win;
SDL_GLContext context;

bool isRunning = true;
float inputX = 0;
float inputY = 0;
int count = 0;
bool isGameOver = false;
std::vector<Box> boxes;
static const Uint32 MS_PER_SECOND = 1000;
static const int MAX_BOX_COLLISION_COUNT = 5;

void drawSkybox()
{
    //Dessin SkyBox

//        glBindTexture(GL_TEXTURE_2D, idTextureSkyBox);
//        glBegin(GL_QUADS);
//
//        glColor3ub(255, 255, 255);
//        glTexCoord2d(.75,.66); glVertex3d(75, 75, 75);
//        glTexCoord2d(.75,.33); glVertex3d(75, 75, -75);
//        glTexCoord2d(1, .33); glVertex3d(-75, 75, -75);
//        glTexCoord2d(1,.66); glVertex3d(-75, 75, 75);
//
//
//        glTexCoord2d(0,.66);glVertex3d(75, -75, 75);
//        glTexCoord2d(0,.33);glVertex3d(75, -75, -75);
//        glTexCoord2d(.25,.33);glVertex3d(75, 75, -75);
//        glTexCoord2d(.25,.66);glVertex3d(75, 75, 75);
//
////        glColor3ub(0, 0, 255); //face bleue
//        glTexCoord2d(0.25,.66);glVertex3d(-75, -75, 75);
//        glTexCoord2d(0.25,.33);glVertex3d(-75, -75, -75);
//        glTexCoord2d(0.5,.33);glVertex3d(75, -75, -75);
//        glTexCoord2d(0.5,.66);glVertex3d(75, -75, 75);
//
////        glColor3ub(255, 255, 0); //face jaune
//        glTexCoord2d(0.5,.66);glVertex3d(-75, 75, 75);
//        glTexCoord2d(0.5,.33);glVertex3d(-75, 75, -75);
//        glTexCoord2d(0.75,.33);glVertex3d(-75, -75, -75);
//        glTexCoord2d(0.75,.66);glVertex3d(-75, -75, 75);
//
////        glColor3ub(0, 255, 255); //face cyan
//        glTexCoord2d(0.25,.33);glVertex3d(75, 75, -75);
//        glTexCoord2d(0.25,0);glVertex3d(75, -75, -75);
//        glTexCoord2d(0.5,0);glVertex3d(-75, -75, -75);
//        glTexCoord2d(0.5,.33);glVertex3d(-75, 75, -75);
//
////        glColor3ub(255, 0, 255); //face magenta
//        glTexCoord2d(0.25,1);glVertex3d(75, -75, 75);
//        glTexCoord2d(0.25,.66);glVertex3d(75, 75, 75);
//        glTexCoord2d(0.5,.66);glVertex3d(-75, 75, 75);
//        glTexCoord2d(0.5,1);glVertex3d(-75, -75, 75);
//
//        glEnd();
}

void drawUpperFloor(GLuint textureId)
{
    //FLOOR
    glPushMatrix();
    glTranslatef(0.0f,20.0f,0.0f);
    glScalef(20.0f,0.0f,20.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glBegin(GL_QUADS);

    glColor3ub(255, 255, 255);
    glTexCoord2f(0.0, 0.0);
    glVertex3d(1, -2, -1);
    glTexCoord2f(1.0, 0);
    glVertex3d(1, -2, 1);
    glTexCoord2f(1.0, 1.0);
    glVertex3d(-1, -2,1);
    glTexCoord2f(0.0, 1.0);
    glVertex3d(-1, -2, -1);

    glEnd();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void spawnBox()
{
    Box box;
    box.setPosY(15.0f);
    box.setRandomXZ();

    float g = (rand()) / ( static_cast <float> (RAND_MAX/(0.5 - 0.2)));
    box.setGravityValue(g);
    boxes.push_back(box);
}

void drawBoxes(Player player, Ground ground)
{
    if(!boxes.empty())
    {
        for (int i = 0; i < boxes.size(); ++i) {
            boxes[i].setGravity();
            boxes[i].draw();

            if(boxes[i].isColliding(player, ground))
            {
                count++;
                std::cout << "Boxes hit : " << count << std::endl;
                boxes.erase(boxes.begin() + i);
            }
        }
    }
}



int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    win = SDL_CreateWindow("OpenGl Test", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    SDL_GLContext context = SDL_GL_CreateContext(win);

    srand(time(NULL));

    inputX = 0;
    inputY = 0;
    Uint32 timer = 0;
    Uint32 previousTime = SDL_GetTicks();
    Uint32 currentTime = SDL_GetTicks();
    Uint32 deltaTime;
    Uint32 randomSpawnTime = 6000;

    GLuint idTextureSol = loadTexture("assets/img/herbe.jpg");
    GLuint idTextureSol2 = loadTexture("assets/img/sol.jpg");
    GLuint idTextureSkyBox = loadTexture("assets/img/skybox.jpg");

    Player player;
    Ground ground;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, (double) 1280 / 720, 1, 1000);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    SDL_Event event;
    const Uint8* states = nullptr;

    while (isRunning)
    {
        currentTime = SDL_GetTicks();
        deltaTime = currentTime - previousTime;

        if (deltaTime == 0) {
            deltaTime = MS_PER_SECOND;
        }
        previousTime = currentTime;

        glClearColor(0.f, 0.5f, 1.0f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslated(0,-3,30);
        gluLookAt(-50, 10, -50, 0, 0, 0, 0, 1, 0);

        SDL_PollEvent(&event);
        states = SDL_GetKeyboardState(NULL);
        if (event.type == SDL_QUIT)
            isRunning = false;

        if (states[SDL_SCANCODE_LEFT])
        {
            if(player.getPosX() < 19)
                inputX += .5;
        }

        if (states[SDL_SCANCODE_RIGHT])
        {
            if(player.getPosX() > -19)
                inputX -= .5;
        }

        if (states[SDL_SCANCODE_UP])
        {
            if(player.getPosZ() < 19)
                inputY += .5;
        }

        if (states[SDL_SCANCODE_DOWN])
        {
            if(player.getPosZ() > -19)
                inputY -= .5;
        }


        player.setPosX(inputX);
        player.setPosY(-3.0);
        player.setPosZ(inputY);
        player.draw();

        //drawPyramid();
        ground.draw(idTextureSol);
        drawUpperFloor(idTextureSol2);
        drawBoxes(player,ground);

        if(!isGameOver)
        {
            timer += deltaTime;
            if(timer >= 3000)
            {
                spawnBox();
                //randomSpawnTime = (rand() % 5000) + 1000;
                timer -= 3000;
            }

            if(count >= MAX_BOX_COLLISION_COUNT)
            {
                isGameOver = true;
                std::cout << "GAME OVER!" << std::endl;
            }
        }

        SDL_Delay(3);
        glFlush();
        SDL_GL_SwapWindow(win);
    }

    glDeleteTextures(1, &idTextureSol);
    glDeleteTextures(1, &idTextureSkyBox);

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
    return 0;
}