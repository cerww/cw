#pragma once
#include <glm\glm.hpp>
inline bool pointInBox(glm::vec4 p1,
	                   glm::vec2 p2) {
	return (p2.x >= p1.x&&p1.x + p1.z >= p2.x&&p1.y <= p2.y&&p1.y + p1.w>= p2.y);
}

inline bool boxInBox(const glm::vec2&& p1, int width1, int height1,
					 const glm::vec2&& p2, int width2, int height2) {
	return (p2.x >= p1.x&&p1.x + width1 >= p2.x&&p1.y <= p2.y&&p1.y + height1 >= p2.y) ||
		(p2.x + width2 >= p1.x&&p1.x + width1 >= p2.x + width2&&p1.y <= p2.y&&p1.y + height1 >= p2.y) ||
		(p2.x + width2 >= p1.x&&p1.x + width1 >= p2.x + width2&&p1.y <= p2.y + height2&&p1.y + height1 >= p2.y + height2) ||
		(p2.x >= p1.x&&p1.x + width1 >= p2.x&&p1.y <= p2.y + height2&&p1.y + height1 >= p2.y + height2);
}

inline bool boxInBox(const glm::vec4 b1,const glm::vec4 b2) {
	return 
		pointInBox(b1, { b2.x,b2.y }) ||
		pointInBox(b1, { b2.x + b2.z,b2.y }) ||
		pointInBox(b1, { b2.x + b2.z,b2.y + b2.w }) ||
		pointInBox(b1, { b2.x,b2.y + b2.w });
}