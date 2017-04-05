#include "slider.h"

//pics that all sliders use!
const texture slider::bar = imgLoader::loadPNG("sliderBar.png");
const texture slider::barSlider = imgLoader::loadPNG("sliderThing.png");

slider::slider(glm::vec4 dims, int min, int max, int start) :
	m_dims(dims),
	m_min(min),
	m_max(max),
	m_current(start) {
	if (m_min > m_max) {
		std::swap(m_min, m_max);
	}
}

void slider::draw(drawRenderer & renderer) const{
	//m_dims;
	const glm::vec4 barDims = { m_dims.x,m_dims.y,m_dims.z, m_dims.w *((float)(m_current - m_min) / (float)(m_max / m_min) )};
	//barDims.w = m_dims.w *(float)(m_current-m_min)/(float)(m_max/m_min);
	renderer.draw(m_dims, fullPicUV, bar.id, { 255,255,255,255 }, 1.0f);
	renderer.draw(barDims, fullPicUV, barSlider.id, { 255,255,255,255 }, 1.0f);
}

/*

L*(current-min)/(max-min)   ~    L is m_dims.w

*/

