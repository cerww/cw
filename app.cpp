#include "app.h"
app::app(GLFWwindow* window):_window(window),_ypos(0.0f),_xpos(0.0f),_maxFPS(60){
    //_spriteBatch.init();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_ALPHA_TEST);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    //keybourd
	/*
    _keys.k[(int)Keys::A]=0;
    _keys.k[(int)Keys::B]=0;
    _keys.k[(int)Keys::C]=0;
    _keys.k[(int)Keys::D]=0;
    _keys.k[(int)Keys::E]=0;
    _keys.k[(int)Keys::F]=0;
    _keys.k[(int)Keys::G]=0;
    _keys.k[(int)Keys::H]=0;
    _keys.k[(int)Keys::I]=0;
    _keys.k[(int)Keys::J]=0;
    _keys.k[(int)Keys::K]=0;
    _keys.k[(int)Keys::L]=0;
    _keys.k[(int)Keys::M]=0;
    _keys.k[(int)Keys::N]=0;
    _keys.k[(int)Keys::O]=0;
    _keys.k[(int)Keys::P]=0;
    _keys.k[(int)Keys::Q]=0;
    _keys.k[(int)Keys::R]=0;
    _keys.k[(int)Keys::S]=0;
    _keys.k[(int)Keys::T]=0;
    _keys.k[(int)Keys::U]=0;
    _keys.k[(int)Keys::V]=0;
    _keys.k[(int)Keys::W]=0;
    _keys.k[(int)Keys::X]=0;
    _keys.k[(int)Keys::Y]=0;
    _keys.k[(int)Keys::Z]=0;
    _keys.k[(int)Keys::N0]=0;
    _keys.k[(int)Keys::N9]=0;
    _keys.k[(int)Keys::N8]=0;
    _keys.k[(int)Keys::N7]=0;
    _keys.k[(int)Keys::N6]=0;
    _keys.k[(int)Keys::N5]=0;
    _keys.k[(int)Keys::N4]=0;
    _keys.k[(int)Keys::N3]=0;
    _keys.k[(int)Keys::N2]=0;
    _keys.k[(int)Keys::N1]=0;
    _keys.k[(int)Keys::DOWN]=0;
    _keys.k[(int)Keys::UP]=0;
    _keys.k[(int)Keys::RIGHT]=0;
    _keys.k[(int)Keys::LEFT]=0;
    _keys.k[(int)Keys::ESC]=0;
    //mouse
    _keys.m[(int)mouseB::LEFT]=0;
    _keys.m[(int)mouseB::RIGHT]=0;
    _keys.m[(int)mouseB::MIDDLE]=0;
	*/
    camera.init(width,height);
}
int app::getKey(const Keys &key)const {
    return _keys.k[(int)key];
}
//GLuint manager::currentTextId=0;
int app::getMouseButton(const mouseB &Button)const{
    return _keys.m[(int)Button];
}

const glm::vec2& app::getMousePos()const{
    return m_mousePos;
}
/*
void app::start(){
    //std::thread t(&app::updateKeys,this);
    //drawing
//    updateKeys();
    _GLSLstuffs["pics"]->use();
    glActiveTexture(GL_TEXTURE0);
    GLint textlocate=_GLSLstuffs["pics"]->getUniformLocate("Text");
    glUniform1i(textlocate,0);

    GLint camLocate=_GLSLstuffs["pics"]->getUniformLocate("orthiMat");
    glm::mat4 abc = camera.getCamMatrix();
    glUniformMatrix4fv(camLocate,1,GL_FALSE,&abc[0][0]);
    //t.join();
    _spriteBatch.begin();
}

void app::end(){
    _spriteBatch.end();
    camera.update();
    _spriteBatch.renderBatch();
    _GLSLstuffs["pics"]->unuse();
    //fps limiter
    _fpsLimiter.limitFPS();
}*/
void app::setMaxFPS(int newfps){
    _maxFPS=newfps;
}
texture app::getTexture(const std::string &textname){
    auto it= _textures.find(textname);
    if(it==_textures.end()){
        _textures[textname]=imgLoader::loadPNG(textname);

    }//std::cout<<textname<<std::endl;
    return _textures[textname];
}
/*
void app::addTexture(const std::string &name,const std::string&path){
    auto it= _textures.find(name);
    if(it!=_textures.end()){
        return;
    }
_textures[name]=imgLoader::loadPNG(path);
}*/

/*
void app::addShader(const std::string& shaderName,const std::string& vertexFile,const std::string& fragFile,const std::vector<std::string>& attributes){
    _GLSLstuffs[shaderName]=std::make_shared<GLSLthingy>();
    _GLSLstuffs[shaderName]->compileshad(vertexFile,fragFile);
    for(auto x:attributes)
        _GLSLstuffs[shaderName]->addAttribute(x);
    _GLSLstuffs[shaderName]->linkshader();
}
*/

void app::update(){
    glfwSwapBuffers(_window);
    //manager::currentCamera.update();
    camera.update();
    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //glClearColor(1.0,1.0,1.0,1.0);
    /* Poll for and process events */
    glfwPollEvents();
    glfwGetCursorPos(_window,&_xpos,&_ypos);
    m_mousePos = glm::vec2(_xpos,_ypos);
    //glfwGetCursorPos(_window,&_xpos,&_ypos);
    if(glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT))++_keys.m[(int)mouseB::LEFT];else _keys.m[(int)mouseB::LEFT]=0;
    if(glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_RIGHT))++_keys.m[(int)mouseB::RIGHT];else _keys.m[(int)mouseB::RIGHT]=0;
    if(glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_MIDDLE))++_keys.m[(int)mouseB::MIDDLE];else _keys.m[(int)mouseB::MIDDLE]=0;
    //keys
    if(glfwGetKey(_window,GLFW_KEY_A)) ++_keys.k[(int)Keys::A]; else _keys.k[(int)Keys::A]=0;
    if(glfwGetKey(_window,GLFW_KEY_B)) ++_keys.k[(int)Keys::B]; else _keys.k[(int)Keys::B]=0;
    if(glfwGetKey(_window,GLFW_KEY_C)) ++_keys.k[(int)Keys::C]; else _keys.k[(int)Keys::C]=0;
    if(glfwGetKey(_window,GLFW_KEY_D)) ++_keys.k[(int)Keys::D]; else _keys.k[(int)Keys::D]=0;
    if(glfwGetKey(_window,GLFW_KEY_E)) ++_keys.k[(int)Keys::E]; else _keys.k[(int)Keys::E]=0;
    if(glfwGetKey(_window,GLFW_KEY_F)) ++_keys.k[(int)Keys::F]; else _keys.k[(int)Keys::F]=0;
    if(glfwGetKey(_window,GLFW_KEY_G)) ++_keys.k[(int)Keys::I]; else _keys.k[(int)Keys::G]=0;
    if(glfwGetKey(_window,GLFW_KEY_H)) ++_keys.k[(int)Keys::H]; else _keys.k[(int)Keys::I]=0;
    if(glfwGetKey(_window,GLFW_KEY_J)) ++_keys.k[(int)Keys::J]; else _keys.k[(int)Keys::J]=0;
    if(glfwGetKey(_window,GLFW_KEY_K)) ++_keys.k[(int)Keys::K]; else _keys.k[(int)Keys::K]=0;
    if(glfwGetKey(_window,GLFW_KEY_L)) ++_keys.k[(int)Keys::L]; else _keys.k[(int)Keys::L]=0;
    if(glfwGetKey(_window,GLFW_KEY_M)) ++_keys.k[(int)Keys::M]; else _keys.k[(int)Keys::M]=0;
    if(glfwGetKey(_window,GLFW_KEY_N)) ++_keys.k[(int)Keys::N]; else _keys.k[(int)Keys::N]=0;
    if(glfwGetKey(_window,GLFW_KEY_O)) ++_keys.k[(int)Keys::O]; else _keys.k[(int)Keys::O]=0;
    if(glfwGetKey(_window,GLFW_KEY_P)) ++_keys.k[(int)Keys::P]; else _keys.k[(int)Keys::P]=0;
    if(glfwGetKey(_window,GLFW_KEY_Q)) ++_keys.k[(int)Keys::Q]; else _keys.k[(int)Keys::Q]=0;
    if(glfwGetKey(_window,GLFW_KEY_R)) ++_keys.k[(int)Keys::R]; else _keys.k[(int)Keys::R]=0;
    if(glfwGetKey(_window,GLFW_KEY_S)) ++_keys.k[(int)Keys::S]; else _keys.k[(int)Keys::S]=0;
    if(glfwGetKey(_window,GLFW_KEY_T)) ++_keys.k[(int)Keys::T]; else _keys.k[(int)Keys::T]=0;
    if(glfwGetKey(_window,GLFW_KEY_U)) ++_keys.k[(int)Keys::U]; else _keys.k[(int)Keys::U]=0;
    if(glfwGetKey(_window,GLFW_KEY_V)) ++_keys.k[(int)Keys::V]; else _keys.k[(int)Keys::V]=0;
    if(glfwGetKey(_window,GLFW_KEY_W)) ++_keys.k[(int)Keys::W]; else _keys.k[(int)Keys::W]=0;
    if(glfwGetKey(_window,GLFW_KEY_X)) ++_keys.k[(int)Keys::X]; else _keys.k[(int)Keys::Y]=0;
    if(glfwGetKey(_window,GLFW_KEY_Y)) ++_keys.k[(int)Keys::Y]; else _keys.k[(int)Keys::X]=0;
    if(glfwGetKey(_window,GLFW_KEY_Z)) ++_keys.k[(int)Keys::Z]; else _keys.k[(int)Keys::Z]=0;
    if(glfwGetKey(_window,GLFW_KEY_0)) ++_keys.k[(int)Keys::N0]; else _keys.k[(int)Keys::N0]=0;
    if(glfwGetKey(_window,GLFW_KEY_1)) ++_keys.k[(int)Keys::N1]; else _keys.k[(int)Keys::N1]=0;
    if(glfwGetKey(_window,GLFW_KEY_2)) ++_keys.k[(int)Keys::N2]; else _keys.k[(int)Keys::N2]=0;
    if(glfwGetKey(_window,GLFW_KEY_3)) ++_keys.k[(int)Keys::N3]; else _keys.k[(int)Keys::N3]=0;
    if(glfwGetKey(_window,GLFW_KEY_4)) ++_keys.k[(int)Keys::N4]; else _keys.k[(int)Keys::N4]=0;
    if(glfwGetKey(_window,GLFW_KEY_5)) ++_keys.k[(int)Keys::N5]; else _keys.k[(int)Keys::N5]=0;
    if(glfwGetKey(_window,GLFW_KEY_6)) ++_keys.k[(int)Keys::N6]; else _keys.k[(int)Keys::N6]=0;
    if(glfwGetKey(_window,GLFW_KEY_7)) ++_keys.k[(int)Keys::N7]; else _keys.k[(int)Keys::N7]=0;
    if(glfwGetKey(_window,GLFW_KEY_8)) ++_keys.k[(int)Keys::N8]; else _keys.k[(int)Keys::N8]=0;
    if(glfwGetKey(_window,GLFW_KEY_9)) ++_keys.k[(int)Keys::N9]; else _keys.k[(int)Keys::N9]=0;
    if(glfwGetKey(_window,GLFW_KEY_LEFT)) ++_keys.k[(int)Keys::LEFT]; else _keys.k[(int)Keys::LEFT]=0;
    if(glfwGetKey(_window,GLFW_KEY_RIGHT)) ++_keys.k[(int)Keys::RIGHT]; else _keys.k[(int)Keys::RIGHT]=0;
    if(glfwGetKey(_window,GLFW_KEY_UP)) ++_keys.k[(int)Keys::UP]; else _keys.k[(int)Keys::UP]=0;
    if(glfwGetKey(_window,GLFW_KEY_DOWN)) ++_keys.k[(int)Keys::DOWN]; else _keys.k[(int)Keys::DOWN]=0;
    if(glfwGetKey(_window,GLFW_KEY_ESCAPE)) ++_keys.k[(int)Keys::ESC]; else _keys.k[(int)Keys::ESC]=0;
    if(glfwGetKey(_window,GLFW_KEY_SPACE)) ++_keys.k[(int)Keys::SPACE]; else _keys.k[(int)Keys::SPACE]=0;
    if(glfwGetKey(_window,GLFW_KEY_RIGHT_SHIFT)) ++_keys.k[(int)Keys::RSHIFT]; else _keys.k[(int)Keys::RSHIFT]=0;
    if(glfwGetKey(_window,GLFW_KEY_LEFT_SHIFT)) ++_keys.k[(int)Keys::LSHIFT]; else _keys.k[(int)Keys::LSHIFT]=0;
    //camera.update();

}
void app::wait(){
    _fpsLimiter.limitFPS();

}
app::~app()
{

}

