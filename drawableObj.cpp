#include "drawableObj.h"

drawableObj::drawableObj(glm::vec4 dims,std::string file, Color color):
	m_dims(dims), 
	m_color(color),
	m_texture(resourceManager::getTexture(std::move(file))){
    
}

drawableObj::drawableObj(glm::vec4 dims, texture t, Color color) : m_dims(std::move(dims)),m_texture(t), m_color(color) {
	//m_texture = resourceManager::getTexture(file);
}

void drawableObj::init(glm::vec4 dims,const std::string& file){
    m_dims = dims;
    m_texture = resourceManager::getTexture(file);
}

void drawableObj::move(glm::vec2 movea){
    m_dims.x += movea.x;
    m_dims.y += movea.y;
}

void drawableObj::Draw(drawRenderer & renderer)const{
	renderer.draw(m_dims,m_uv,m_texture.id,m_color,1.0f);
}

void drawRenderer::Render(const camera2D& cam){
    glslProg.use();

    stop();

    glActiveTexture(GL_TEXTURE0);
    GLint textlocate = glslProg.getUniformLocate("Text");
    glUniform1i(textlocate,0);

    GLint camLocate = glslProg.getUniformLocate("orthiMat");
    glm::mat4 abc = cam.getCamMatrix();
	glUniformMatrix4fv(camLocate, 1, GL_FALSE, &abc[0][0]);

    renderBatch();

    glslProg.unuse();

    start();
}
drawRenderer::drawRenderer(){
    glslProg.compileshad("texture.vert","texture.frag");
    glslProg.addAttribute("vertPosition");
    glslProg.addAttribute("vertColor");
    glslProg.addAttribute("vertUV");

    glslProg.linkshader();
    start();
}

