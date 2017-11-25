#pragma once
#include "Drawable.h"
#include "guiRenderer.h"


template<typename T>
class guiDrawable:public crtpb<T>{
public:	
	void draw(guiRenderer& renderer, const glm::vec2 a = {}) const{
		this->self().draw_impl(renderer,a);
	}
	void update(glm::vec2 a,int b){
		this->self().update_impl(a, b);
	}
};
