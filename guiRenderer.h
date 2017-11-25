#pragma once
#include "renderer.h"
#include "SpriteBatch.h"

class guiRenderer:public renderer<guiRenderer>
{
public:
	guiRenderer();
	void render_impl(const camera2D& cam);

	template<typename...Args>
	void draw(const glm::vec2 offSet,glm::vec4 dims,Args... args){
		dims.x += offSet.x;
		dims.y += offSet.y;
		m_spriteBatch.draw(dims, std::forward<Args>(args)...);
	};
private:
	GLSLthingy m_glslThing;
	SpriteBatch m_spriteBatch;
};

