#pragma once
#include <glm\glm.hpp>
#include <tuple>
#include <cmath>
#include <glm/gtx/intersect.hpp>
#include <array>
#include "mathStuff.h"

inline bool pointInBox(const glm::vec4 p1,
	const glm::vec2 p2) {
	return (p2.x >= p1.x&&p1.x + p1.z >= p2.x&&p1.y <= p2.y&&p1.y + p1.w >= p2.y);
}

inline bool boxInBox(const glm::vec2&& p1, int width1, int height1,
					 const glm::vec2&& p2, int width2, int height2) {
	return (p2.x >= p1.x&&p1.x + width1 >= p2.x&&p1.y <= p2.y&&p1.y + height1 >= p2.y) ||
		(p2.x + width2 >= p1.x&&p1.x + width1 >= p2.x + width2&&p1.y <= p2.y&&p1.y + height1 >= p2.y) ||
		(p2.x + width2 >= p1.x&&p1.x + width1 >= p2.x + width2&&p1.y <= p2.y + height2&&p1.y + height1 >= p2.y + height2) ||
		(p2.x >= p1.x&&p1.x + width1 >= p2.x&&p1.y <= p2.y + height2&&p1.y + height1 >= p2.y + height2);
}

inline bool boxInBox(const glm::vec4 b1, const glm::vec4 b2) {
	return
		pointInBox(b1, { b2.x,b2.y }) ||
		pointInBox(b1, { b2.x + b2.z,b2.y }) ||
		pointInBox(b1, { b2.x + b2.z,b2.y + b2.w }) ||
		pointInBox(b1, { b2.x,b2.y + b2.w });
}

inline bool inRange(double a, glm::vec2 c) {
	//if(c.)
	return a >= std::min(c.x, c.y) && a <= std::max(c.x, c.y);
}

inline bool inRange(const double a, double lower, double upper) {
	if (upper < lower)
		std::swap(upper, lower);
	return a >= lower - 0.1 && a <= upper + 0.1;
}

inline std::tuple<glm::vec2, bool> doLinesIntersect(const glm::vec2 p1s, const glm::vec2 p1e,
													const glm::vec2 p2s, const glm::vec2 p2e) {
	const double denominator = (p1s.x - p1e.x)*(p2s.y - p2e.y) - (p1s.y - p1e.y)*(p2s.x - p2e.x);

	if (denominator == 0.0) {
		return { {},0 };
	}

	const glm::vec2 reVec((((glm::determinant(glm::mat2(p1s, p1e)) * (p2s.x - p2e.x)) - (p1s.x - p1e.x)*glm::determinant(glm::mat2(p2s, p2e))) / denominator),
						 (((glm::determinant(glm::mat2(p1s, p1e)) * (p2s.y - p2e.y)) - (p1s.y - p1e.y)*glm::determinant(glm::mat2(p2s, p2e))) / denominator));

	//cuz math, idk how this works
	//yay i figured out how this works

	return { reVec,inRange(reVec.x,p1s.x,p1e.x) && inRange(reVec.y,p2s.y,p2e.y) || inRange(reVec.x,{ p2s.x,p2e.x }) && inRange(reVec.y,{ p1s.y,p1e.y }) }; 
	//cuz floating point error
}

enum class intersect :uint8_t { NONE, LEFT, RIGHT, TOP, BOTTOM };

inline std::tuple<glm::vec2, intersect> ifIntersectBox(const glm::vec2 start, const glm::vec2 velocity, const glm::vec4 box) {//assumes start isnt inside box
	if (!pointInBox(box, start + velocity)) {
		return { velocity,intersect::NONE };
	}

	const auto temp = start + velocity;

	decltype(doLinesIntersect({}, {}, {}, {})) c;

	if (velocity.x < 0.0) {//right side
		c = doLinesIntersect(start, start + velocity, { box.x + box.z,box.y }, { box.x + box.z,box.y + box.w });
		if (std::get<1>(c)) {
			return { start - std::get<0>(c),intersect::RIGHT };
		}
	}
	else if (velocity.x > 0.0) {//left side
		c = doLinesIntersect(start, start + velocity, { box.x,box.y }, { box.x,box.y + box.w });
		if (std::get<1>(c)) {
			return { start - std::get<0>(c),intersect::LEFT };
		}
	}

	if (velocity.y > 0.0) {//bottom
		c = doLinesIntersect(start, temp, { box.x,box.y }, { box.x + box.z,box.y });//are these right?
		if (std::get<1>(c)) {
			return { start - std::get<0>(c),intersect::BOTTOM };
		}
	}
	else if (velocity.y < 0.0) {//top
		c = doLinesIntersect(start, start + velocity, { box.x,box.y + box.w }, { box.x + box.z,box.y + box.w });
		if (std::get<1>(c)) {
			return { start - std::get<0>(c),intersect::TOP };
		}
	}

	return { { 0,0 },intersect::NONE };//this shouldnt be running
}

