#pragma once
#include <type_traits>

template <typename T>
struct crtp
{
	T& get() { return static_cast<T&>(*this); }
	T const& get() const { return static_cast<T const&>(*this); }
};

class drawRenderer;

template<typename thing>
class Drawable:crtp<thing> {//requires a Draw function!
public:
	//template<typename...args>
	void draw(drawRenderer& renderer)const {
		this->get().Draw(renderer);
	}
};
