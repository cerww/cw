#include "line.h"
#include <glm\trigonometric.hpp>

void line::draw(drawRenderer& renderer){
	math::radians angle = math::atan2((m_p1 - m_p2).x, (m_p1 - m_p2).y);
	renderer.draw({ m_p1.x,m_p1.y,m_width,glm::length(m_p1 - m_p2) }, fullPicUV, Rectangle::getFlatColor().id, m_color, 1.0f, angle);
}

