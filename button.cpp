#include "button.h"

//template<typename fn>
button::button(glm::vec4 d, texture t, Color C, std::function<void()> f,const std::string& s) :	drawableObj(d, t, C),
	m_hoverColor(C),
	m_hoverTexture(t),
	m_clickColor(C),
	m_clickTexture(t),
	m_function(f),
	m_text(s){}




void button::doClick() {

	m_function();

	//std::swap(C,C2);
}

