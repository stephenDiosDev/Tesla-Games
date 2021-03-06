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
#include "Controller.h"

class StartScreen
{
public:
	StartScreen() = default;

	void loadVertices();
	void loadTextures();
	void use();
	void load();
	void loadShader();

	void loadController(Controller *controller);


private:
	//I think it's more like a 2D graphic shader than a HUD shader, wrong name now :(
	std::vector<HUD*> HUDList;
	Shader hudShader;
	int op;

	unsigned int indices[6] = {
		0, 1, 3,
		2, 1, 3
	};

	Texture backgroundTexture;
	Texture logoTexture;
	Texture startText;
	Texture settingText;
	Texture exitText;
	Texture startText1;
	Texture startText2;
	Texture settingText1;
	Texture settingText2;
	Texture exitText1;
	Texture exitText2;
	Texture dpadTexture;
	Texture selectTexture;

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

	GLfloat logoVertices[20] = {
		468.5f / 1600 * mainWindow.getWidth(), 0.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		468.5f / 1600 * mainWindow.getWidth(), 858.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		1131.5f / 1600 * mainWindow.getWidth(), 858.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		1131.5f / 1600 * mainWindow.getWidth(), 0.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	GLfloat startVertices[20] = {
		550.f / 1600 * mainWindow.getWidth(), 550.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		550.f / 1600 * mainWindow.getWidth(), 750.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		1050.f / 1600 * mainWindow.getWidth(), 750.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		1050.f / 1600 * mainWindow.getWidth(), 550.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};
	
	GLfloat settingVertices[20] = {
		550.f / 1600 * mainWindow.getWidth(), 650.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		550.f / 1600 * mainWindow.getWidth(), 850.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		1050.f / 1600 * mainWindow.getWidth(), 850.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		1050.f / 1600 * mainWindow.getWidth(), 650.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};
	
	GLfloat exitVertices[20] = {
		550.f / 1600 * mainWindow.getWidth(), 750.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		550.f / 1600 * mainWindow.getWidth(), 950.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		1050.f / 1600 * mainWindow.getWidth(), 950.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		1050.f / 1600 * mainWindow.getWidth(), 750.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	GLfloat dpadVertices[20] = {
		0.f / 1600 * mainWindow.getWidth(), 800.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		0.f / 1600 * mainWindow.getWidth(), 920.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		300.f / 1600 * mainWindow.getWidth(), 920.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		300.f / 1600 * mainWindow.getWidth(), 800.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};

	GLfloat selectVertices[20] = {
		0.f / 1600 * mainWindow.getWidth(), 760.f / 900.0f * mainWindow.getHeight(), 1.0f,	0.0f, 0.0f,
		0.f / 1600 * mainWindow.getWidth(), 880.f / 900.0f * mainWindow.getHeight(), 1.0f,		0.0f, 1.0f,
		300.f / 1600 * mainWindow.getWidth(), 880.f / 900.0f * mainWindow.getHeight(), 1.0f,		1.0f, 1.0f,
		300.f / 1600 * mainWindow.getWidth(), 760.f / 900.0f * mainWindow.getHeight(), 1.0f,	1.0f, 0.0f
	};
	void setOption(int op);
};

