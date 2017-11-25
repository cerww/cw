#include "guiRenderer.h"



guiRenderer::guiRenderer(){	
	m_glslThing.compileshad("texture.vert", "texture.frag");
	m_glslThing.addAttribute("vertPosition");
	m_glslThing.addAttribute("vertColor");
	m_glslThing.addAttribute("vertUV");

	m_glslThing.linkshader();
	m_spriteBatch.start();
}

void guiRenderer::render_impl(const camera2D& cam){
	m_glslThing.use();
	m_spriteBatch.stop();

	glActiveTexture(GL_TEXTURE0);
	GLint textlocate = m_glslThing.getUniformLocate("Text");
	glUniform1i(textlocate, 0);

	GLint camLocate = m_glslThing.getUniformLocate("orthiMat");
	glm::mat4 abc = cam.getCamMatrix();
	glUniformMatrix4fv(camLocate, 1, GL_FALSE, &abc[0][0]);

	m_spriteBatch.renderBatch();
	m_glslThing.unuse();
	m_spriteBatch.start();
}
