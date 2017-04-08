#pragma once
#ifndef APP_H
#define APP_H
#include <map>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include "texture.h"
#include "GLSLthingy.h"
#include "imgLoader.h"
#include "SpriteBatch.h"
#include "camera2D.h"
#include "fpslimiter.h"
#include <thread>
#include <future>
#include <glm/glm.hpp>
#include <array>
enum class Keys:uint8_t{A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
               N1,N2,N3,N4,N5,N6,N7,N8,N9,N0,
               NUM1,NUM2,NUM3,NUM4,NUM5,NUM6,NUM7,NUM8,NUM9,NUM0,
               LALT,RALT,LSHIFT,RSHIFT,ESC,SPACE,END,HOME,PAGEDOWN,
               PAGEUP,INSERT,UP,DOWN,LEFT,RIGHT,COLON,ENTER,BACKSPACE,
			   DASH,EQUAL,TAB,MAX};

enum class mouseB:uint8_t{MIDDLE,LEFT,RIGHT,MAX};


class app
{
    public:
        app(GLFWwindow* );
        //app(const app&);
        virtual ~app();
        void update();
        int getKey(const Keys &key)const;
        const glm::vec2& getMousePos()const;
        int getMouseButton(const mouseB&Button)const;
        texture getTexture(const std::string&);
        //void addTexture(const std::string&,const std::string&);
        //void addShader(const std::string&,const std::string&,const std::string&,const std::vector<std::string>&);
        void setMaxFPS(int);
        void wait();
        camera2D camera;
		/*
        void start();
        void end();
		*/
        //void draw(const glm::vec4& dimensions,const glm::vec4& uv,GLuint text,Color colour,const float& depth);
        //void updateKeys();
		GLFWwindow * getWindowPtr() const { return _window; };
    protected:

    private:
		struct keys {
			//std::unordered_map<Keys, int> k;
			std::array<uint16_t, (size_t)Keys::MAX> k = {};
			//std::unordered_map<mouseB, int> m;
			std::array<uint16_t,(size_t)mouseB::MAX> m = {};
		};
        //void test();
        GLFWwindow* _window;
        keys _keys;
        double _ypos;
        double _xpos;
        //SpriteBatch _spriteBatch;
        //std::vector<Glyph> m_drawBatchs;
        glm::vec2 m_mousePos;
        std::unordered_map<std::string,texture> _textures;
        //std::map<std::string,std::shared_ptr<GLSLthingy>> _GLSLstuffs;
        int _maxFPS;
        //double currentFrame=0;
        //double _prevFrame = glfwGetTime();
        fpslimiter _fpsLimiter;

};

#endif // APP_H
