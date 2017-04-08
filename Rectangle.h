#pragma once
#include "drawableObj.h"

class Rectangle:public drawableObj {
public:
	static const texture flatColor;
	Rectangle() = default;
	Rectangle(glm::vec4,Color);
private:

};
