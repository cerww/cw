#pragma once
#include <type_traits>

template <typename T>
struct crtpb
{
	T& self() { return static_cast<T&>(*this); }
	T const& self() const { return static_cast<T const&>(*this); }
};

class drawRenderer;

template<typename thing>
struct Drawable:crtpb<thing> {
	void draw(drawRenderer& renderer)const {
		this->self().draw_impl(renderer);
	}
};


