//
// Created by jlidou on 2018-12-11.
//

#ifndef FIRSTOPENGL_MONCARRE_H
#define FIRSTOPENGL_MONCARRE_H


#include <SDL2/SDL_pixels.h>

class MonCarre {

    float x,y;
    SDL_Color color;



    void dessiner();
    void deplacer(float dx,float dy, float dTheta);

};


#endif //FIRSTOPENGL_MONCARRE_H
