#ifndef RENDERER_H
#define RENDERER_H
#include "SpriteBatch.h"
#include "resourceManager.h"
#include "GLSLthingy.h"
#include "camera2D.h"
#include <memory>
class renderer //interface class 
{
    public:
        //renderer();
        renderer() = default;
        //virtual ~renderer()= default;
        virtual void render(const camera2D& cam) = 0;
    protected:
        GLSLthingy glslProg;
        //std::unique_ptr<GLSLthingy> glslProg;
        SpriteBatch spriteB;
    private:
//        resourceManager* manager;
};

#endif // RENDERER_H

