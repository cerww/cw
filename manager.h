#ifndef MANAGER_H
#define MANAGER_H
#include <GL/glew.h>
#include "camera2D.h"
class manager
{
    public:
        manager();
        virtual ~manager();
        static GLuint currentTextId;
        static GLuint windowHeight;// *-1
        static GLuint windowWidth;
        static GLuint maxFps;
        static camera2D currentCamera;
    protected:

    private:
};

#endif // MANAGER_H
