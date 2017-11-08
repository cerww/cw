#include "line.h"
#include "circle.h"
#include <glm\trigonometric.hpp>

void line::Draw(drawRenderer& renderer){
	const math::radians angle = math::atan2((m_p1 - m_p2).x, (m_p1 - m_p2).y);
	drawLine<line_type::BLOCK>(renderer, m_p1,m_p2,m_color,m_width);
}

template<line_type type>
void drawLine(drawRenderer & renderer,const glm::vec2 p1,const glm::vec2 p2,const Color color,const size_t width){
	const math::radians angle = math::atan2((p1 - p2).x, (p1 - p2).y);
	const double length = glm::length(p1 - p2);
	renderer.draw(	glm::vec4{ p1.x,p1.y,width,length },
		defaultUV,
					Rectangle::getFlatColor().id,
					color,
					1.0f, 
					angle,
					glm::vec2{ math::cos(angle) * length - math::cos(angle) * width,math::sin(angle)*width - math::sin(angle) * length });
	if constexpr(type == line_type::ROUND){
		circle::drawCircle(renderer, p1, width / 2, color);
		circle::drawCircle(renderer, p2, width / 2, color);
	}
}