#include "line.h"
#include "circle.h"
#include <glm\trigonometric.hpp>

void line::Draw(drawRenderer& renderer){
	//const math::radians angle = math::atan2((m_p1 - m_p2).x, (m_p1 - m_p2).y);
	drawLine<line_type::BLOCK>(renderer, m_p1,m_p2,m_color,m_width);
}

