#include "input.h"
#include "window.h"
#include "things.h"
#include "drawableObj.h"


void input::update_impl(glm::vec2 pos, int click){
	m_selected = click && pointInBox(m_dims, pos);	
}

void input::draw_impl(drawRenderer & renderer){
	renderer.draw(m_dims, defaultUV, 0, colours::WHITE, 1.0f);
}

void input::update_impl2(window& win,camera2D Cam){
	if(win.getCodePoint()){
		if (win.getCodePoint() != 127)//127 is backspace
			m_text.push_back(win.getCodePoint());
		else
			m_text.pop_back();
	}
}
