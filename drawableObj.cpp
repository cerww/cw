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

/*
template<typename type>
void drawRenderer::draw(const Drawable<type>& item)
*/
/*
template<typename ...args>
void drawRenderer::draw(args... Args){
	spriteB.draw(std::forward<args>(Args)...);
}
*/
void drawRenderer::Render(const camera2D& cam){
    glslProg.use();

    end();

    glActiveTexture(GL_TEXTURE0);
    GLint textlocate = glslProg.getUniformLocate("Text");
    glUniform1i(textlocate,0);

    GLint camLocate = glslProg.getUniformLocate("orthiMat");
    glm::mat4 abc = cam.getCamMatrix();
    glUniformMatrix4fv(camLocate,1,GL_FALSE,&abc[0][0]);

    renderBatch();

    glslProg.unuse();

    begin();
}
drawRenderer::drawRenderer(){
    glslProg.compileshad("texture.vert","texture.frag");
    glslProg.addAttribute("vertPosition");
    glslProg.addAttribute("vertColor");
    glslProg.addAttribute("vertUV");

    glslProg.linkshader();

    //spriteB.init();
    begin();
}
/*
void drawRenderer::draw(glm::vec4 dimensions, glm::vec4 uv, GLuint text, Color colour, float depth, math::radians angle, glm::vec2 offSetAfterRotation){
	spriteB.draw(dimensions, uv, text, colour, depth, angle, offSetAfterRotation);
}
void drawRenderer::draw(glm::vec4 dimensions, glm::vec4 uv, GLuint text, Color colour, float depth, math::radians angle){
	spriteB.draw(dimensions, uv, text, colour, depth, angle);
}
void drawRenderer::draw(glm::vec4 dimensions, glm::vec4 uv, GLuint text, Color colour, float depth, glm::vec2 dir){
	spriteB.draw(dimensions, uv, text, colour, depth, dir);
}
void drawRenderer::draw(glm::vec4 dimensions, glm::vec4 uv, GLuint text, Color colour, float depth){
	spriteB.draw(dimensions, uv, text, colour, depth);
}

*/