#pragma once
#include "Drawable.h"
#include <string>
#include <glm\glm.hpp>
#include "camera2D.h"
#include "guiDrawable.h"

class window;
class input:public guiDrawable<input>
{
public:
	input(glm::vec4 t_dims,std::string t_text):m_dims(t_dims),m_text(t_text){};
	void draw_impl(drawRenderer& renderer);
	void update_impl(glm::vec2, int);
	void update_impl2(window&, camera2D Cam);
private:
	glm::vec4 m_dims;
	std::string m_text;
	bool m_selected = false;
};

