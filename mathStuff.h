#pragma once
#include <cmath>
#include <ratio>


namespace math {

	template<uint64_t num, uint64_t den = 1>
	struct angleMesurement {
		constexpr angleMesurement() = default;
		constexpr angleMesurement(const long double d) :angle(d) {}
		long double angle;

		template<uint64_t num2, uint64_t den2>
		constexpr operator angleMesurement<num2, den2>() const{
			return angleMesurement<num2, den2>((angle*static_cast<double>(den*num2)) / static_cast<double>(num*den2));
		}
		constexpr uint64_t getFullRotations() const{
			return angle*den / num;
		}
	};

	template<uint64_t num, uint64_t den>
	constexpr angleMesurement<num, den>&& operator+(const angleMesurement<num, den>& a, const angleMesurement<num, den>& b) {
		return angleMesurement<num, den>(a.angle + b.angle);
	}
	
	template<uint64_t num, uint64_t den, uint64_t num2, uint64_t den2>
	constexpr angleMesurement<num, den>&& operator+(const angleMesurement<num, den>& a, const angleMesurement<num2, den2>& b) {
		return angleMesurement<num, den>(a.angle + angleMesurement<num, den>(b).angle);
	}

	template<uint64_t num, uint64_t den>
	constexpr angleMesurement<num, den>&& operator-(const angleMesurement<num, den>& a, const angleMesurement<num, den>& b) {
		return angleMesurement<num, den>(a.angle - b.angle);
	}

	template<uint64_t num, uint64_t den, uint64_t num2, uint64_t den2>
	constexpr angleMesurement<num, den>&& operator-(const angleMesurement<num, den>& a, const angleMesurement<num2, den2>& b) {
		return angleMesurement<num, den>(a.angle - angleMesurement<num, den>(b).angle);
	}


	using degrees = angleMesurement<360>;
	using radians = angleMesurement<31415926535 * 2,10000000000>;

	constexpr degrees operator"" _deg(const long double a) {
		return degrees(a);
	}

	constexpr degrees operator"" _deg(const unsigned long long a) {
		return degrees((long double)a);
	}

	constexpr radians operator"" _rad(const long double a) {
		return radians(a);
	}

	constexpr radians operator"" _rad(const unsigned long long a) {
		return radians((long double)a);
	}

	//template<uint64_t num,uint64_t den>
	double cos(const radians angle) {
		return std::cos(angle.angle);
	}

	double sin(const radians angle) {
		return std::sin(angle.angle);
	}

	double tan(const radians angle) {
		return std::tan(angle.angle);
	}

	radians acos(const double d) {
		return radians(std::acos(d));
	}

	radians asin(const double d) {
		return radians(std::asin(d));
	}

	radians atan(const double d) {
		return radians(std::atan(d));
	}
	
	radians atan2(const double d1, const double d2) {
		return radians(std::atan2(d1, d2));
	}




	/*
	class degrees {
	public:
		degrees() = default;
		degrees(double a) :angle(a) {};
		double angle;

		operator double() const {
			return angle;
		}



	};
	degrees&& operator+(const degrees& a, const degrees& b) {
		return degrees(a.angle + b.angle);
	}
	degrees&& operator-(const degrees& a, const degrees& b) {
		return degrees(a.angle - b.angle);
	}

	class radians {
	public:
		radians() = default;
		radians(double a) :angle(a) {};
		double angle;

		radians&& operator=(const float d)const {
			return radians(d);
		}

		operator double() const {
			return angle;
		}

		operator degrees()const {
			return degrees(angle*180.0f / 3.1415926535);
		}

	};

	inline double cos(const radians r) {
		return std::cos(r.angle);
	}

	inline double sin(const radians r) {
		return std::sin(r.angle);
	}

	inline double tan(const radians r) {
		return std::tan(r.angle);
	}


	inline radians arccos(double d) {
		
	}

	inline radians arcsin(double d) {}

	inline radians arctan(double d) {}
	*/
};