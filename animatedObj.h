#ifndef ANIMATEDOBJ_H
#define ANIMATEDOBJ_H
#include "window.h"
#include <vector>
#include <array>
#include <string>
#include <glm/glm.hpp>
#include <gl/glew.h>
#include "texture.h"
#include <memory>
#include "renderer.h"
#include "resourceManager.h"
#include "drawableObj.h"
//#include <
/*
file will look like

picture dir
framesX frameY
name start n repeat/stay/end(0,1,2) speed(frames per frame)
name start n repeat speed(frames per frame)
name start n repeat speed(frames per frame)...

first ani is default ani
texture will be mapped like this
7 8 9 10 11 12 13
0 1 2  3  4  5  6
*/

class animatedObj:Drawable<animatedObj>{
    public:
        animatedObj(glm::vec4,std::string);
        animatedObj() = default;
        //void draw(app&);
		void setAnimation(const std::string&);
        void init(glm::vec4,const std::string&);//use this if you called the ctor with no agrs
		void setDims(glm::vec4 t_dims) { m_dims = std::move(t_dims); }
		void Draw(drawRenderer&);
	private:
		void updateFrame();
        enum class animationMode{REPEAT,STAY,END};
        struct framey{
            framey() = default;
			framey(int a, int y, animationMode m, int sp) :start(a), num(y), mode(m), speed(sp) {};
            int start;
            int num;
            animationMode mode;
            int speed;
        };
        int m_currentFrame;
        int m_endingFrame;
        std::string m_currentPart;
        framey* currentAni=nullptr;
        std::unordered_map<std::string,framey> m_animations;

        glm::vec4 m_dims;
        friend class renderAnimatedObjects;
    private:
        void getAniInfo(const std::string&);
        int m_frameW;
        int m_frameH;
        texture m_texture;
        glm::vec4 m_uv = glm::vec4(0.0f,0.0f,1.0f,1.0f);
};
class renderAnimatedObjects:public renderer<renderAnimatedObjects>{
    public:
        renderAnimatedObjects();
        //renderAnimatedObjects();
        //renderAnimatedObjects();
        void Render(const camera2D& cam);
        void drawObj(animatedObj&);
        //void start(){spriteB.begin();};
    private:
        //std::vector<animatedObj*> m_objs;
		GLSLthingy glslProg;
		SpriteBatch spriteB;
};
#endif // ANIMATEDOBJ_H
