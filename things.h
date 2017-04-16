#pragma once
#include <glm\glm.hpp>
#include <tuple>
#include <cmath>
#include <glm/gtx/intersect.hpp>
#include <array>

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

inline bool inRange(float a,glm::vec2 c) {
	//if(c.)
	return a >= std::min(c.x, c.y) && a <= std::max(c.x, c.y);
}

inline bool inRange(float a, float lower, float upper) {
	if (upper > lower)
		std::swap(upper, lower);
	return a >= lower && a <= upper;
}

inline std::tuple<glm::vec2, bool> doLinesIntersect(glm::vec2 p1s, glm::vec2 p1e,
													glm::vec2 p2s, glm::vec2 p2e) {
	float bottom = (p1s.x - p1e.x)*(p2s.y - p2e.y) - (p1s.y - p1e.y)*(p2s.x - p2s.x);
	if (bottom == 0) {
		return { {},0 };
	}

	glm::vec2 reVec;

	reVec.x = ((glm::determinant(glm::mat2(p1s, p1e)) * (p2s.x - p2e.x)) - (p1s.x - p1e.x)*glm::determinant(glm::mat2(p2s, p2e))) / bottom;

	reVec.y = ((glm::determinant(glm::mat2(p1s, p1e)) * (p2s.y - p2e.y)) - (p1s.y - p1e.y)*glm::determinant(glm::mat2(p2s, p2e))) / bottom;

	//cuz math, idk how this works

	return { reVec,inRange(reVec.x,{p1s.x,p1e.x}) && inRange(reVec.x,{p2s.x,p2e.x}) && inRange(reVec.y,{p1s.y,p1e.y}) && inRange(reVec.y,{p2s.y,p2e.y}) };

}

enum class intersect :uint8_t{NONE,LEFT,RIGHT,TOP,BOTTOM};

inline std::tuple<glm::vec2, intersect> ifIntersectBox(glm::vec2 start, glm::vec2 velocity, glm::vec4 box) {//assumes start isnt inside box
	if (!pointInBox(box, start + velocity)) {
		return { velocity,intersect::NONE };
	}

	//std::array<glm::vec4, 2> vecsToCheck;

	if (velocity.x < 0) {//right side
		//vecsToCheck[0] = { box.x + box.z,box.y + box.y,box.x + box.z,box.y };
		auto c = doLinesIntersect(start, start + velocity, { box.x + box.z,box.y }, { box.x + box.z,box.y + box.w });
		if (std::get<1>(c)) {
			return { start - std::get<0>(c),intersect::RIGHT };
		}
	}
	else if (velocity.x > 0) {//left side
		auto c = doLinesIntersect(start, start + velocity, { box.x,box.y }, { box.x,box.y + box.w });
		if (std::get<1>(c)) {
			return { start - std::get<0>(c),intersect::LEFT };
		}
	}
	//std::cout << "WORK pls" << std::endl;
	if (velocity.y > 0) {//bottom
		auto c = doLinesIntersect(start, start + velocity, { box.x,box.y }, { box.x + box.z,box.y });//are these right?
		if (std::get<1>(c)) {
			return { start - std::get<0>(c),intersect::BOTTOM };
		}
	}
	else if (velocity.y < 0) {//top
		auto c = doLinesIntersect(start, start + velocity, { box.x,box.y + box.w }, { box.x + box.z,box.y + box.w });
		if (std::get<1>(c)) {
			return { start - std::get<0>(c),intersect::TOP};
		}
	}
	return { {0,0},intersect::NONE };
}



namespace math {

	class degrees {
	public:
		degrees() = default;
		degrees(float a) :angle(a) {};
		float angle;
		/*
		degrees&& operator=(const float f) {
			return degrees(f);
		}
		*/
		operator float() {
			return angle;
		}
	};

	class radians {
	public:
		radians() = default;
		radians(float a) :angle(a) {};
		float angle;

		
		radians&& operator=(const degrees& d) const{
			return radians(d.angle*3.14159265435 / 180.0f);
		}
		
		radians&& operator=(const float d)const {
			return radians(d);
		}

		float operator=(radians r)const {
			return r.angle;
		}
		
		degrees&& operator=(const radians& r)const {
			return degrees(r.angle*180.0f / 3.1415926535);
		}
		
		operator float() const{
			return angle;
		}

		operator degrees()const {
			return degrees(angle*180.0f / 3.1415926535);
		}


	};
	
	inline double cos(const radians r) {
		return std::cos(r);
	}

	inline double sin(const radians r) {
		return std::sin(r);
	}
	
	inline double tan(const radians r) {
		return std::tan(r);
	}

	
	inline radians arccos(double d) {
		radians r = 2.0;


	}

	inline radians arcsin(double d) {}

	inline radians arctan(double d) {}
};