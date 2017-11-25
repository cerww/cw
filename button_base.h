#pragma once
#include "Drawable.h"
#include "guiDrawable.h"
#include "things.h"

static constexpr uint8_t s_callbackEnableBit = 0b1;

template<typename Derived>//2x crtp XD
class button_base:public guiDrawable<button_base<Derived>>{
public:	
	button_base() = default;
	button_base(glm::vec4 t_dims,std::function<void()> t_callback):
		m_dims(t_dims),
		m_callback(t_callback){};
	void update_impl(glm::vec2 mousePos,int mouseClick){
		if(pointInBox(m_dims,mousePos)){
			if(mouseClick){
				m_state = state::CLICK;
				if(mouseClick == 1 && (m_flagBits & s_callbackEnableBit))
					m_callback();				
			}else{
				m_state = state::HOVER;
			}
		}else{
			m_state = state::NORMAL;
		}
	};
	void draw_impl(guiRenderer& renderer, const glm::vec2 offSet)const{
		static_cast<const Derived const*>(this)->draw_button(renderer, offSet);
	};
	void toggleCallback() {
		m_flagBits ^= s_callbackEnableBit;
	}
	void enableCallback() {
		m_flagBits |= s_callbackEnableBit;
	}
	void disableCallback() {
		m_flagBits &= ~s_callbackEnableBit;
	}
	template<typename Fn>
	void setCallback(Fn f){
		m_callback = std::move(f);
	}
	enum class state :char { NORMAL, HOVER, CLICK };
	state getState()const { return m_state; }
	uint8_t getFlagBits()const { return m_flagBits; }
	glm::vec4 getDims()const { return m_dims; }
	void doClick(){
		m_callback();
	}
private:
	glm::vec4 m_dims;
	std::function<void()> m_callback;
	state m_state = state::NORMAL;
	uint8_t m_flagBits = 0b1;
};


