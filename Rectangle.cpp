#include "Rectangle.h"

const texture Rectangle::flatColor = imgLoader::loadPNG("blank.png");

Rectangle::Rectangle(glm::vec4 d,Color c):drawableObj(d,flatColor,c){}