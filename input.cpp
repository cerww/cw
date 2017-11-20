#include "input.h"
#include "window.h"
#include "things.h"
#include "drawableObj.h"


void input::update(glm::vec2 pos, int click){
	if(click){
		m_selected = pointInBox(m_dims, pos);
	}
}

void input::Draw(drawRenderer & renderer){	
	renderer.draw(m_dims, defaultUV, 0, colours::WHITE, 1.0f);
}

void input::update(window& win,camera2D Cam){
	update(Cam.scrnToWorld(win.getMousePos()), win.getMouseButton(mouseB::LEFT));
	if(win.getCodePoint()){
		if (win.getCodePoint() != 127)
			m_text += std::string(1, win.getCodePoint());
		else
			m_text.pop_back();
	}
}
