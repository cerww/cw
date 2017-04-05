#pragma once
#include "drawableObj.h"

class slider {
public:
	static const texture bar;// = imgLoader::loadPNG("sliderBar.png");
	static const texture barSlider;// = imgLoader::loadPNG("sliderThing.png");
	slider() = default;
	slider(glm::vec4,int = 0,int = 100,int = 50);
	virtual void draw(drawRenderer&)const;

private:
	glm::vec4 m_dims;
	//int m_current;
	int m_min = 0;
	int m_max = 100;
	int m_current;
};