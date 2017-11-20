#pragma once
#include "Drawable.h"
#include <vector>
#include <glm\glm.hpp>
#include <memory>
#include <algorithm>

class guiObject {
public:
	guiObject() = default;

	template<typename T>
	guiObject(T other):m_self(std::make_unique<obj<T>>(std::move(other))){}

	template<typename T>
	guiObject& operator=(T other){
		m_self = std::make_unique<obj<T>>(std::move(other));
		return *this;
	}
	//guiObject& operator=(guiObject&& other) = default;
	//guiObject& operator=(const guiObject&) = delete;
	void update(glm::vec2 a,int b){
		m_self->update(a,b);
	};
	void Draw(drawRenderer& renderer){
		m_self->Draw(renderer);
	};
private:
	struct concept{
		virtual void Draw(drawRenderer&) = 0;
		virtual void update(glm::vec2, int) = 0;//mouse pos, mouse click
	};
	template<typename T>
	struct obj:concept{
		obj(T s) :stuffs(s) {};

		void Draw(drawRenderer& renderer) override final{
			stuffs.draw(renderer);
		};
		void update(glm::vec2 mousePos, int clickTime) override final{
			stuffs.update(mousePos, clickTime);
		};//mouse pos, mouse click
		T stuffs;
	};
	std::unique_ptr<concept> m_self = nullptr;
};


class GUI:public Drawable<GUI>{
public:
	GUI(glm::vec4);
	void Draw(drawRenderer&);
	void update(glm::vec2,int);//mouse pos, mouse click
	template<typename T>
	void addObject(T other){
		m_objs.push_back(std::move(other));
	};
	void removeItem(int i){
		std::swap(m_objs[i], m_objs.back());
		m_objs.pop_back();
	}
	template<typename T,typename ... args>
	decltype(auto) emplaceObj(args... Args){
		return m_objs.emplace_back(T(std::forward<args>(Args)...));
	}
	glm::vec2 getPos()const{
		return { m_dims.x,m_dims.y };
	}
private:
	std::vector<guiObject> m_objs;//order doesn't matter
	glm::vec4 m_dims = {};
};

