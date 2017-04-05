#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
class texture
{
    public:
        texture() = default;
		texture(GLuint tid, int twidth, int theight):
		        id(tid),width(twidth),height(theight){}

        GLuint id;
        int width;
        int height;
    protected:

    private:

};

#endif // TEXTURE_H
