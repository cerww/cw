#include "line.h"
#include "circle.h"
#include <glm\trigonometric.hpp>

void line::draw(drawRenderer& renderer){
	const math::radians angle = math::atan2((m_p1 - m_p2).x, (m_p1 - m_p2).y);
	renderer.draw(glm::vec4{ m_p1.x,m_p1.y,m_width,glm::length(m_p1 - m_p2) }, fullPicUV, Rectangle::getFlatColor().id, m_color, 1.0f, angle);
}

template<bool type>
void drawLine(drawRenderer & renderer, glm::vec2 p1, glm::vec2 p2, Color color, size_t width){
	const math::radians angle = math::atan2((p1 - p2).x, (p1 - p2).y);
	auto length = glm::length(p1 - p2);
	renderer.draw(	glm::vec4{ p1.x,p1.y,width,length },
					fullPicUV,
					Rectangle::getFlatColor().id,
					color,
					1.0f, 
					angle,
					glm::vec2{ math::cos(angle) * length - math::cos(angle) * width,math::sin(angle)*width - math::sin(angle) * length });
	if constexpr(!type){
		circle::drawCircle(renderer, p1, width / 2, color);
		circle::drawCircle(renderer, p2, width / 2, color);
	}
}