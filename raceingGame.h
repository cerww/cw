#ifndef RACEINGGAME_H
#define RACEINGGAME_H
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
#include "pic.h"
#include "SpriteBatch.h"
#include "manager.h"
#include "camera2D.h"
#include "fpslimiter.h"
#include <thread>
#include <future>
#include <glm/glm.hpp>
#include "resourceManager.h"
#include "app.h"

class raceingGame
{
    public:
        raceingGame(GLFWwindow*);
        raceingGame()= default;
        virtual ~raceingGame();
        void doStuff();
    protected:

    private:
        app m_window;
        camera2D m_camera;
        resourceManager m_manager;
        SpriteBatch m_sprites;
};

#endif // RACEINGGAME_H
