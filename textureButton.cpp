#include "textureButton.h"
#include "things.h"
#include "texture.h"
#include "drawableObj.h"

void textureButton::draw_button(guiRenderer& renderer, glm::vec2 offSet)const {
	renderer.draw(offSet, getDims(), defaultUV, m_textures[(int)getState()], m_colours[(int)getState()], 1.0f);
}
