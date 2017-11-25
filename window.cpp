#include "window.h"

std::unordered_map<GLFWwindow*, window*> window::m_refs = {};

window::window(GLFWwindow* window):_window(window){

	glfwMakeContextCurrent(window);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	if (glewInit() != GLEW_OK) {
		std::cout << "glew failed to init" << std::endl;
		glfwTerminate();
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_ALPHA_TEST);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
	glfwSetCharCallback(_window, [](GLFWwindow* win,uint32_t t_codePoint) {
		window::setCodePoint(win, t_codePoint);
	});
	glfwSetScrollCallback(_window, [](GLFWwindow* win, double x, double y) {
		window::setScrolled(win, x, y);
	});
	m_refs[window] = this;
}

int window::getKey(Keys key)const {
    return _keys.k[(int)key];
}

int window::getMouseButton(mouseB Button)const{
    return _keys.m[(int)Button];
}

glm::vec2 window::getMousePos()const{
    return m_mousePos;
}

void window::setMaxFPS(int newfps){
	_fpsLimiter.fps = newfps;
}
texture window::getTexture(const std::string &textname){
    auto it= _textures.find(textname);
    if(it==_textures.end()){
        _textures[textname]=imgLoader::loadPNG(textname);
    }return _textures[textname];
}


void window::update(){
    glfwSwapBuffers(_window);
    /* Poll for and process events */
	m_scrolled = {};
	m_codePoint = 0;
    glfwPollEvents();
    glfwGetCursorPos(_window,&m_mousePos.x,&m_mousePos.y);
	//std::vector<event> events;
    //glfwGetCursorPos(_window,&_xpos,&_ypos);
    if(glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT))++_keys.m[(int)mouseB::LEFT];else _keys.m[(int)mouseB::LEFT]=0;
    if(glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_RIGHT))++_keys.m[(int)mouseB::RIGHT];else _keys.m[(int)mouseB::RIGHT]=0;
    if(glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_MIDDLE))++_keys.m[(int)mouseB::MIDDLE];else _keys.m[(int)mouseB::MIDDLE]=0;
    //keys
	_keys.k[(int)Keys::A] = (_keys.k[(int)Keys::A] + 1) * glfwGetKey(_window, GLFW_KEY_A);
	_keys.k[(int)Keys::B] = (_keys.k[(int)Keys::B] + 1) * glfwGetKey(_window, GLFW_KEY_B);
	_keys.k[(int)Keys::C] = (_keys.k[(int)Keys::C] + 1) * glfwGetKey(_window, GLFW_KEY_C);
	_keys.k[(int)Keys::D] = (_keys.k[(int)Keys::D] + 1) * glfwGetKey(_window, GLFW_KEY_D);
	_keys.k[(int)Keys::E] = (_keys.k[(int)Keys::E] + 1) * glfwGetKey(_window, GLFW_KEY_E);
	_keys.k[(int)Keys::F] = (_keys.k[(int)Keys::F] + 1) * glfwGetKey(_window, GLFW_KEY_F);
	_keys.k[(int)Keys::G] = (_keys.k[(int)Keys::G] + 1) * glfwGetKey(_window, GLFW_KEY_G);
	_keys.k[(int)Keys::H] = (_keys.k[(int)Keys::H] + 1) * glfwGetKey(_window, GLFW_KEY_H);
	_keys.k[(int)Keys::I] = (_keys.k[(int)Keys::I] + 1) * glfwGetKey(_window, GLFW_KEY_I);
	_keys.k[(int)Keys::J] = (_keys.k[(int)Keys::J] + 1) * glfwGetKey(_window, GLFW_KEY_J);
	_keys.k[(int)Keys::K] = (_keys.k[(int)Keys::K] + 1) * glfwGetKey(_window, GLFW_KEY_K);
	_keys.k[(int)Keys::L] = (_keys.k[(int)Keys::L] + 1) * glfwGetKey(_window, GLFW_KEY_L);
	_keys.k[(int)Keys::M] = (_keys.k[(int)Keys::M] + 1) * glfwGetKey(_window, GLFW_KEY_M);
	_keys.k[(int)Keys::N] = (_keys.k[(int)Keys::N] + 1) * glfwGetKey(_window, GLFW_KEY_N);
	_keys.k[(int)Keys::O] = (_keys.k[(int)Keys::O] + 1) * glfwGetKey(_window, GLFW_KEY_O);
	_keys.k[(int)Keys::P] = (_keys.k[(int)Keys::P] + 1) * glfwGetKey(_window, GLFW_KEY_P);
	_keys.k[(int)Keys::Q] = (_keys.k[(int)Keys::Q] + 1) * glfwGetKey(_window, GLFW_KEY_Q);
	_keys.k[(int)Keys::R] = (_keys.k[(int)Keys::R] + 1) * glfwGetKey(_window, GLFW_KEY_R);
	_keys.k[(int)Keys::S] = (_keys.k[(int)Keys::S] + 1) * glfwGetKey(_window, GLFW_KEY_S);
	_keys.k[(int)Keys::T] = (_keys.k[(int)Keys::T] + 1) * glfwGetKey(_window, GLFW_KEY_T);
	_keys.k[(int)Keys::U] = (_keys.k[(int)Keys::U] + 1) * glfwGetKey(_window, GLFW_KEY_U);
	_keys.k[(int)Keys::V] = (_keys.k[(int)Keys::V] + 1) * glfwGetKey(_window, GLFW_KEY_V);
	_keys.k[(int)Keys::W] = (_keys.k[(int)Keys::W] + 1) * glfwGetKey(_window, GLFW_KEY_W);
	_keys.k[(int)Keys::X] = (_keys.k[(int)Keys::X] + 1) * glfwGetKey(_window, GLFW_KEY_X);
	_keys.k[(int)Keys::Y] = (_keys.k[(int)Keys::Y] + 1) * glfwGetKey(_window, GLFW_KEY_Y);
	_keys.k[(int)Keys::Z] = (_keys.k[(int)Keys::Z] + 1) * glfwGetKey(_window, GLFW_KEY_Z);
	_keys.k[(int)Keys::N0] = (_keys.k[(int)Keys::N0] + 1) * glfwGetKey(_window, GLFW_KEY_0);
	_keys.k[(int)Keys::N1] = (_keys.k[(int)Keys::N1] + 1) * glfwGetKey(_window, GLFW_KEY_1);
	_keys.k[(int)Keys::N2] = (_keys.k[(int)Keys::N2] + 1) * glfwGetKey(_window, GLFW_KEY_2);
	_keys.k[(int)Keys::N3] = (_keys.k[(int)Keys::N3] + 1) * glfwGetKey(_window, GLFW_KEY_3);
	_keys.k[(int)Keys::N4] = (_keys.k[(int)Keys::N4] + 1) * glfwGetKey(_window, GLFW_KEY_4);
	_keys.k[(int)Keys::N5] = (_keys.k[(int)Keys::N5] + 1) * glfwGetKey(_window, GLFW_KEY_5);
	_keys.k[(int)Keys::N6] = (_keys.k[(int)Keys::N6] + 1) * glfwGetKey(_window, GLFW_KEY_6);
	_keys.k[(int)Keys::N7] = (_keys.k[(int)Keys::N7] + 1) * glfwGetKey(_window, GLFW_KEY_7);
	_keys.k[(int)Keys::N8] = (_keys.k[(int)Keys::N8] + 1) * glfwGetKey(_window, GLFW_KEY_8);
	_keys.k[(int)Keys::N9] = (_keys.k[(int)Keys::N9] + 1) * glfwGetKey(_window, GLFW_KEY_9);
	_keys.k[(int)Keys::LEFT] = (_keys.k[(int)Keys::LEFT] + 1) * glfwGetKey(_window, GLFW_KEY_LEFT);
	_keys.k[(int)Keys::RIGHT] = (_keys.k[(int)Keys::RIGHT] + 1) * glfwGetKey(_window, GLFW_KEY_RIGHT);
	_keys.k[(int)Keys::UP] = (_keys.k[(int)Keys::UP] + 1) * glfwGetKey(_window, GLFW_KEY_UP);
	_keys.k[(int)Keys::DOWN] = (_keys.k[(int)Keys::DOWN] + 1) * glfwGetKey(_window, GLFW_KEY_DOWN);
	_keys.k[(int)Keys::ESC] = (_keys.k[(int)Keys::ESC] + 1) * glfwGetKey(_window, GLFW_KEY_ESCAPE);
	_keys.k[(int)Keys::SPACE] = (_keys.k[(int)Keys::SPACE] + 1) * glfwGetKey(_window, GLFW_KEY_SPACE);
	_keys.k[(int)Keys::RSHIFT] = (_keys.k[(int)Keys::RSHIFT] + 1) * glfwGetKey(_window, GLFW_KEY_RIGHT_SHIFT);
	_keys.k[(int)Keys::LSHIFT] = (_keys.k[(int)Keys::LSHIFT] + 1) * glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT);
	_keys.k[(int)Keys::RCTRL] = (_keys.k[(int)Keys::RCTRL] + 1) * glfwGetKey(_window, GLFW_KEY_RIGHT_CONTROL);
	_keys.k[(int)Keys::LCTRL] = (_keys.k[(int)Keys::LCTRL] + 1) * glfwGetKey(_window, GLFW_KEY_LEFT_CONTROL);
	_keys.k[(int)Keys::ENTER] = (_keys.k[(int)Keys::ENTER] + 1) * glfwGetKey(_window, GLFW_KEY_ENTER);
	
	
	/*
	if (glfwGetKey(_window, GLFW_KEY_A)) ++_keys.k[(int)Keys::A]; else { _keys.k[(int)Keys::A] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_B)) ++_keys.k[(int)Keys::B]; else { _keys.k[(int)Keys::B] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_C)) ++_keys.k[(int)Keys::C]; else { _keys.k[(int)Keys::C] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_D)) ++_keys.k[(int)Keys::D]; else { _keys.k[(int)Keys::D] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_E)) ++_keys.k[(int)Keys::E]; else { _keys.k[(int)Keys::E] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_F)) ++_keys.k[(int)Keys::F]; else { _keys.k[(int)Keys::F] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_G)) ++_keys.k[(int)Keys::I]; else { _keys.k[(int)Keys::G] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_H)) ++_keys.k[(int)Keys::H]; else { _keys.k[(int)Keys::I] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_J)) ++_keys.k[(int)Keys::J]; else { _keys.k[(int)Keys::J] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_K)) ++_keys.k[(int)Keys::K]; else { _keys.k[(int)Keys::K] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_L)) ++_keys.k[(int)Keys::L]; else { _keys.k[(int)Keys::L] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_M)) ++_keys.k[(int)Keys::M]; else { _keys.k[(int)Keys::M] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_N)) ++_keys.k[(int)Keys::N]; else { _keys.k[(int)Keys::N] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_O)) ++_keys.k[(int)Keys::O]; else { _keys.k[(int)Keys::O] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_P)) ++_keys.k[(int)Keys::P]; else { _keys.k[(int)Keys::P] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_Q)) ++_keys.k[(int)Keys::Q]; else { _keys.k[(int)Keys::Q] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_R)) ++_keys.k[(int)Keys::R]; else { _keys.k[(int)Keys::R] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_S)) ++_keys.k[(int)Keys::S]; else { _keys.k[(int)Keys::S] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_T)) ++_keys.k[(int)Keys::T]; else { _keys.k[(int)Keys::T] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_U)) ++_keys.k[(int)Keys::U]; else { _keys.k[(int)Keys::U] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_V)) ++_keys.k[(int)Keys::V]; else { _keys.k[(int)Keys::V] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_W)) ++_keys.k[(int)Keys::W]; else { _keys.k[(int)Keys::W] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_X)) ++_keys.k[(int)Keys::X]; else { _keys.k[(int)Keys::Y] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_Y)) ++_keys.k[(int)Keys::Y]; else { _keys.k[(int)Keys::X] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_Z)) ++_keys.k[(int)Keys::Z]; else { _keys.k[(int)Keys::Z] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_0)) ++_keys.k[(int)Keys::N0]; else { _keys.k[(int)Keys::N0] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_1)) ++_keys.k[(int)Keys::N1]; else { _keys.k[(int)Keys::N1] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_2)) ++_keys.k[(int)Keys::N2]; else { _keys.k[(int)Keys::N2] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_3)) ++_keys.k[(int)Keys::N3]; else { _keys.k[(int)Keys::N3] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_4)) ++_keys.k[(int)Keys::N4]; else { _keys.k[(int)Keys::N4] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_5)) ++_keys.k[(int)Keys::N5]; else { _keys.k[(int)Keys::N5] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_6)) ++_keys.k[(int)Keys::N6]; else { _keys.k[(int)Keys::N6] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_7)) ++_keys.k[(int)Keys::N7]; else { _keys.k[(int)Keys::N7] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_8)) ++_keys.k[(int)Keys::N8]; else { _keys.k[(int)Keys::N8] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_9)) ++_keys.k[(int)Keys::N9]; else { _keys.k[(int)Keys::N9] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_LEFT)) ++_keys.k[(int)Keys::LEFT]; else { _keys.k[(int)Keys::LEFT] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_RIGHT)) ++_keys.k[(int)Keys::RIGHT]; else { _keys.k[(int)Keys::RIGHT] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_UP)) ++_keys.k[(int)Keys::UP]; else { _keys.k[(int)Keys::UP] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_DOWN)) ++_keys.k[(int)Keys::DOWN]; else { _keys.k[(int)Keys::DOWN] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE)) ++_keys.k[(int)Keys::ESC]; else { _keys.k[(int)Keys::ESC] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_SPACE)) ++_keys.k[(int)Keys::SPACE]; else { _keys.k[(int)Keys::SPACE] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_RIGHT_SHIFT)) ++_keys.k[(int)Keys::RSHIFT]; else { _keys.k[(int)Keys::RSHIFT] = 0; }
	if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT)) ++_keys.k[(int)Keys::LSHIFT]; else { _keys.k[(int)Keys::LSHIFT] = 0; }
	*/
}
void window::wait(){
    _fpsLimiter.limitFPS();

}

void window::initialize(){
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	if (glewInit() != GLEW_OK) {
		std::cout << "glew failed to init" << std::endl;
		glfwTerminate();
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
