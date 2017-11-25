#ifndef DRAWABLEOBJ_H
#define DRAWABLEOBJ_H
#include "renderer.h"
#include <string>
#include "texture.h"
#include "resourceManager.h"
#include "mathStuff.h"
#include "Drawable.h"
const glm::vec4 defaultUV = { 0.0f,0.0f,1.0f,1.0f };

class drawRenderer :public renderer<drawRenderer>,private SpriteBatch {//msvs doesnt like me ;-;, hacky way around this
public:
	drawRenderer();
	/*
	void draw(glm::vec4 dimensions, glm::vec4 uv, GLuint text, Color colour, float depth, math::radians angle, glm::vec2 offSetAfterRotation);
	void draw(glm::vec4 dimensions, glm::vec4 uv, GLuint text, Color colour, float depth, math::radians angle);
	void draw(glm::vec4 dimensions, glm::vec4 uv, GLuint text, Color colour, float depth, glm::vec2 dir);
	void draw(glm::vec4 dimensions, glm::vec4 uv, GLuint text, Color colour, float depth);
	*/
	using SpriteBatch::draw;

	template<typename type>
	void drawObj(const type& item) {
		item.draw(*this);
	};
	
	void render_impl(const camera2D& cam);
private:
	GLSLthingy glslProg;
	//SpriteBatch spriteB;
};
//for things that don't need to be drawn weird

class drawableObj:public Drawable<drawableObj>
{
public:
	drawableObj() = default;
	drawableObj(glm::vec4, std::string file, Color = { 255,255,255,255 });
	drawableObj(glm::vec4, texture file, Color = { 255,255,255,255 });
	void draw_impl(drawRenderer&)const;

    void init(glm::vec4,const std::string& file);
    void move(glm::vec2);
    glm::vec2 getSpot()const{return glm::vec2(m_dims.x,m_dims.y);};
	void setSpot(glm::vec4 t)noexcept { m_dims = t; }
	void setColor(Color c)noexcept { m_color = c; }
	Color getColor()noexcept { return m_color; }
	glm::vec4 uv = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
protected:
	Color m_color;
    texture m_texture;
    glm::vec4 m_dims;		
};

#endif // DRAWABLEOBJ_H