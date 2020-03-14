#pragma once

#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <vector>

#include "Global.h"
#include "Shader.h"
#include "Window.h"
#include "HUD.h"
#include "Texture.h"

class Menu
{
public:
	Menu() = default;

	void loadVertices();
	void loadTextures();
	void use();
	void load();
	void loadShader();

	void setOption(int op);

private:
	std::vector<HUD*> HUDList;
	Shader hudShader;

	unsigned int indices[6] = {
		0, 1, 3,
		2, 1, 3
	};

	Texture backgroundTexture;
	Texture menuTxt;
	Texture audioTxt;
	Texture HUDSizeTxt;

	Texture audioTxt1;
	Texture audioTxt2;
	Texture HUDSizeTxt1;
	Texture HUDSizeTxt2;


	// Vertex Shader of HUD_shader
	const char* vHshader = "Shaders/HUD_shader.vert";

	//Fragment shader of HUD_shader
	const char* fHshader = "Shaders/HUD_shader.frag";

	GLfloat backgroundVertices[20] = {
		0.0f / 1600 * mainWindow.getWidth(), 0.f / 900.0f * mainWindow.getHeight(), 0.0f,	0.0f, 0.0f,								//bottom left
		0.0f / 1600 * mainWindow.getWidth(), 900.0f / 900.0f * mainWindow.getHeight(), 0.0f,		0.0f, 1.0f,								//top left
		1600.0f / 1600 * mainWindow.getWidth(), 900 / 900.0f * mainWindow.getHeight(), 0.0f,		1.0f, 1.0f,								//top right
		1600.0f / 1600 * mainWindow.getWidth(), 0.f / 900.0f * mainWindow.getHeight(), 0.0f,	1.0f, 0.0f								//bottom right
	};


};

