#pragma once
#include "drawableObj.h"

class Rectangle:public drawableObj {
public:
	static texture flatColor;
	Rectangle() = default;
	Rectangle(glm::vec4,Color);
	//void draw(drawRenderer& r) const override;
private:
	static bool Loaded;
};
