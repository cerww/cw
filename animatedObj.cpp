#include "animatedObj.h"
#include <iostream>

animatedObj::animatedObj(glm::vec4 dims,std::string animationInfo):m_dims(dims){
    getAniInfo(std::move(animationInfo));
     //std::cout<<dims.x<<' '<<dims.y<<' '<<dims.z<<' '<<dims.w<<'\n';
}


void animatedObj::setAnimation(const std::string& partName)noexcept{
    const auto it = m_animations.find(partName);
    if(it==m_animations.end()){
        return;
    }
	currentAni = &it->second;
    m_currentFrame = 0;
    m_endingFrame = currentAni->num*currentAni->speed;

	m_uv.x = (currentAni->start%m_frameW)*1.0f / (float)(m_frameW);
	m_uv.y = (currentAni->start / m_frameW)*1.0f / (float)m_frameW;
}

void animatedObj::updateFrame() noexcept{
	if (!currentAni) {
		return;
	}
	++m_currentFrame;
	if (m_currentFrame == m_endingFrame) {
		switch (currentAni->mode){
		case animatedObj::animationMode::REPEAT:
			m_currentFrame = currentAni->start;
			break;
		case animatedObj::animationMode::STAY:
			--m_currentFrame;
			break;
		case animatedObj::animationMode::END:
			m_currentFrame = 0;
			m_endingFrame = 0;
			currentAni = nullptr;
			m_currentPart = "";
			return;
			break;
		default:
			return;
			break;
		}
	}

	m_uv.x = ((currentAni->start + (m_currentFrame / currentAni->speed)) % m_frameW)*1.0f / (float)(m_frameW);
	m_uv.y = ((currentAni->start + (m_currentFrame / currentAni->speed)) / m_frameW)*1.0f / (float)m_frameW;
}

void animatedObj::getAniInfo(const std::string& animationInfo) {
	try {
		unsigned ocurrent = 0;
		auto current = animationInfo.find('\n');

		m_texture = resourceManager::getTexture(animationInfo.substr(0, current - ocurrent));

		ocurrent = (unsigned)current + 1;
		current = animationInfo.find(' ', current + 1);
		m_frameW = (unsigned)atoi(animationInfo.substr(ocurrent, current - ocurrent).c_str());
		ocurrent = (unsigned)current + 1;
		current = animationInfo.find('\n', current + 1);
		m_frameH = atoi(animationInfo.substr(ocurrent, current - ocurrent).c_str());

		while (current < animationInfo.size() - 3) {
			ocurrent = (unsigned)current + 1;
			current = animationInfo.find(' ', current + 1);
			std::string aniName = animationInfo.substr(ocurrent, current - ocurrent);

			ocurrent = (unsigned)current + 1;
			current = animationInfo.find(' ', current + 1);
			int start = atoi(animationInfo.substr(ocurrent, current - ocurrent).c_str());

			ocurrent = (unsigned)current + 1;
			current = animationInfo.find(' ', current + 1);
			int num = atoi(animationInfo.substr(ocurrent, current - ocurrent).c_str());

			ocurrent = (unsigned)current + 1;
			current = animationInfo.find(' ', current + 1);
			animationMode m = (animationMode)atoi(animationInfo.substr(ocurrent, current - ocurrent).c_str());

			ocurrent = (unsigned)current + 1;
			current = animationInfo.find_first_of(" \n", current + 1);
			int speed = atoi(animationInfo.substr(ocurrent, current - ocurrent).c_str());
			
			m_animations.insert(std::make_pair(std::move(aniName), framey(start, num, m, speed)));
		}
	}
	catch(...){
		//somehow crash
		//std::cout << e << std::endl;
		std::cout << animationInfo << " is not valid" << std::endl;
		currentAni = nullptr;
		return;
	}
	m_uv.z = 1.0f / (float)m_frameW;
	m_uv.w = 1.0f / (float)m_frameH;
}

void animatedObj::init(glm::vec4 dims,const std::string& aniInfo){
    m_dims = dims;
    getAniInfo(aniInfo);
}

void animatedObj::draw_impl(drawRenderer& renderer){
	renderer.draw(m_dims, m_uv, m_texture.id, colours::BLACK, 1.0f);
	updateFrame();
}

