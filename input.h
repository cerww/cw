#pragma once
#include "Drawable.h"
#include <string>
#include <glm\glm.hpp>
#include "camera2D.h"

class window;
class input:public Drawable<input>
{
public:
	input(glm::vec4 t_dims,std::string t_text):m_dims(t_dims),m_text(t_text){};
	void Draw(drawRenderer& renderer);
	void update(window&, camera2D Cam);
private:
	glm::vec4 m_dims;
	std::string m_text;
	void update(glm::vec2, int);
	bool m_selected = false;
};

