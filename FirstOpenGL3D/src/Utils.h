//
// Created by jlidou on 2018-12-12.
//

#ifndef FIRSTOPENGL_UTILS_H
#define FIRSTOPENGL_UTILS_H

#include <gl/gl.h>
#include <gl/glu.h>

class Utils {
public:
    static void dessinerRepere(float taille){
    glLineWidth(5.f);
        glBegin(GL_LINES);

            glColor3ub(255,0,0);
                glVertex3f(0,0,0);
                glVertex3f(taille,0,0);
            glColor3ub(0,255,0);
                glVertex3f(0,0,0);
                glVertex3f(0,taille,0);
            glColor3ub(0,0,255);
                glVertex3f(0,0,0);
                glVertex3f(0,0,taille);
        glEnd();
    }

};


#endif //FIRSTOPENGL_UTILS_H
