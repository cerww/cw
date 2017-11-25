#include "GUI.h"
#include "things.h"



GUI::GUI(glm::vec4 t_dims):m_dims(t_dims){}

void GUI::draw_impl(guiRenderer& renderer,glm::vec2 a)const{
	for (auto& i : m_objs){
		i.draw(renderer, a + getPos());
	}
		
}

void GUI::update_impl(glm::vec2 mousePos, int mouseClick){	
	if (pointInBox(m_dims, mousePos))
		for(auto& i:m_objs)
			i.update(mousePos - getPos(), mouseClick);
}

