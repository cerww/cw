#pragma once
#include <glm\glm.hpp>
#include <tuple>
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
enum class intersect :uint8_t{NONE,LEFT,RIGHT,TOP,BOTTOM};

inline std::tuple<glm::vec2, intersect> ifIntersect(glm::vec2 start,glm::vec2 velocity, glm::vec4 box) {//assumes start isnt inside box
	if (!pointInBox(box,start+velocity)) {
		return { velocity,intersect::NONE };
	}


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

		
		radians&& operator=(const degrees& d) {
			return radians(d.angle*3.14159265435 / 180.0f);
		}
		
		radians&& operator=(const float d) {
			return radians(d);
		}

		degrees&& operator=(const radians& r) {
			return degrees(r.angle*180.0f / 3.1415926535);
		}

		operator float() {
			return angle;
		}

		operator degrees() {
			return degrees(angle*180.0f / 3.1415926535);
		}
	};
	
	inline double cos(const radians r) {
		return r.angle - r.angle*r.angle*r.angle / 6.0f + r.angle*r.angle*r.angle*r.angle*r.angle / 120.0f;
	}

	inline double sin(const radians r) {}
	
	inline double tan(const radians r) {}

	
	inline radians arccos(double d) {}

	inline radians arcsin(double d) {}

	inline radians arctan(double d) {}
};