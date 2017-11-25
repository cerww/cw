#pragma once
#include "guiDrawable.h"
#include <array>
#include "button_base.h"

class textureButton :public button_base<textureButton> {
public:
	textureButton() = default;
	template<typename fn>
	textureButton(glm::vec4 t_dims, fn F, std::array<GLuint, 3> t_textures, std::array<Color, 3> t_colours) :
		button_base<textureButton>(t_dims,std::move(F)),
		m_textures(t_textures),
		m_colours(t_colours)
	{}
	template<typename fn>
	textureButton(glm::vec4 t_dims, fn F, GLuint t_texture, Color t_colour) : 
		button_base<textureButton>(t_dims,std::move(F)),
		m_textures({ t_texture,t_texture,t_texture }),
		m_colours({ t_colour,t_colour,t_colour })
	{}
	void draw_button(guiRenderer&, glm::vec2)const;
private:
	std::array<GLuint, 3> m_textures;
	std::array<Color, 3> m_colours;
};
