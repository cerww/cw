#pragma once
#include "app.h"
#include "vertex.h"
#include "drawableObj.h"
#include "things.h"
#include <functional>

//template<typename fn>
class button:private drawableObj {
public:
	button() = default;
	//button(glm::vec4, texture, Color C, fn f, Color C2);
	button(glm::vec4, texture, Color C, std::function<void()> f,const std::string&);
	//template<typename ... Args>
	void doClick();
	const auto& getText() const { return m_text; };
	void setText(const std::string& s) {
		m_text = s;
	}

	void setHoverColor(Color c) {
		m_hoverColor = std::move(c);
	}
	void setHoverTexture(texture t){
		m_hoverTexture = std::move(t);
	}

	void setClickColor(Color c) {
		m_clickColor = std::move(c);
	}
	void setClickTexture(texture t) {
		m_clickTexture = std::move(t);
	}

	void getState(const app&);
	

protected:
	Color m_hoverColor;
	texture m_hoverTexture;

	Color m_clickColor;
	texture m_clickTexture;

	std::string m_text;

private:
	enum class state {NORMAL,HOVER,CLICKED};
	std::function<void()> m_function;
	//bool m_clicked = 0;
	state m_currentState = state::NORMAL;
};
/*
inline auto makeButton(glm::vec4 d, texture t, Color C, fn f,const std::string& s) {
	return button(d, t, C, f,s);
}*/

inline void ktest() {
	int b = 0;
	const auto f = [&b]() {std::cout << "abc" << std::endl; };
	auto a = button({}, {}, {}, f, "");
}
