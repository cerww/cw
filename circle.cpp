#include "circle.h"
texture circle::s_circle = {};

circle::circle(){
	if(!s_circle.id){
		loadCircle();
	}
}

void circle::drawCircle(drawRenderer & renderer,glm::vec2 spot, double r , Color C){
	renderer.draw({ spot.x - r,spot.y - r,r * 2,r * 2 }, fullPicUV, s_circle.id, C, 1.0f);
}

texture circle::getCircleTexture(){
	if(!s_circle.id){
		loadCircle();
	}return s_circle;
}

void circle::draw(drawRenderer& renderer) const{
	renderer.draw({spot.x-radius,spot.y-radius,radius*2,radius*2},fullPicUV,s_circle.id,colour,1.0f);
}


