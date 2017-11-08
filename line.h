#pragma once
#include "drawableObj.h"
#include "Rectangle.h"
#include "Drawable.h"

class line:public Drawable<line>{
public:
	line() = default;
	line(glm::vec2 t_p1, glm::vec2 t_p2, Color t_color = colours::WHITE, size_t t_width = 2) :m_p1(t_p1), m_p2(t_p2), m_color(t_color), m_width(t_width) {};
	void Draw(drawRenderer&);
private:
	glm::vec2 m_p1;
	glm::vec2 m_p2;
	Color m_color;
	size_t m_width;
};

enum class line_type {
	ROUND,
	BLOCK
};

template<line_type type>
void drawLine(drawRenderer&, glm::vec2 p1, glm::vec2 p2, Color color, size_t width);
