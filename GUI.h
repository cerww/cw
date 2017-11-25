#pragma once
#include "Drawable.h"
#include <vector>
#include <glm\glm.hpp>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include "guiDrawable.h"



class guiRenderer;

class guiObject:public guiDrawable<guiObject> {
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
	void update_impl(glm::vec2 a,int b){
		m_self->update(a, b);
	};
	void draw_impl(guiRenderer& renderer, glm::vec2 a)const;

	void* get() {
		return m_self.get();
	};
private:
	struct concept{
		virtual void draw(guiRenderer&,glm::vec2) = 0;
		virtual void update(glm::vec2, int) = 0;//mouse pos, mouse click
	};
	template<typename T>
	struct obj:concept{
		obj(T s) :stuffs(s) {};

		void draw(guiRenderer& renderer, glm::vec2 a) const override final {	
			stuffs.draw(renderer, a);
		};

		void update(glm::vec2 mousePos, int clickTime) override final{
			stuffs.update(mousePos, clickTime);
		};
		T stuffs;
	};
	std::unique_ptr<concept> m_self = nullptr;
};

class GUI:public guiDrawable<GUI>{
public:
	GUI(glm::vec4);
	void draw_impl(guiRenderer&, glm::vec2 a = {})const;
	void update_impl(glm::vec2,int);//mouse pos, mouse click
	template<typename T>
	decltype(auto) addObject(T other){
		m_objs.push_back(std::move(other));		
		return (T*)(m_objs.back().get());
	};
	template<typename T,typename ... args>
	decltype(auto) emplaceObj(args... Args){
		return (T*)m_objs.emplace_back(T(std::forward<args>(Args)...)).get();
	}
	glm::vec2 getPos()const{
		return { m_dims.x,m_dims.y };
	}
	template<typename T>
	void removeItem(T* item){
		for(int i = 0;i<m_objs.size();++i){
			if(m_objs[i].get() == item){
				std::swap(m_objs.back(), m_objs[i]);
				m_objs.pop_back();
				return;
			}
		}
	}
private:
	std::vector<guiObject> m_objs;//order doesn't matter
	glm::vec4 m_dims = {};
};


inline void guiObject::draw_impl(guiRenderer& renderer,glm::vec2 a)const{
	m_self->draw(renderer, a);
};

