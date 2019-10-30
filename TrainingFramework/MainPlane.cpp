#include"MainPlane.h"
#include"Sprite2D.h"
#include "Shaders.h"
#include "Models.h"
#include "Camera.h"
#include "Texture.h"
#include<memory>

extern GLint screenWidth;
extern GLint screenHeight;

MainPlane::MainPlane(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture,GLint xPos,GLint yPos)
	: Sprite2D(model,shader,texture)
{
	m_pModel = model;
	m_pShader = shader;
	m_pCamera = nullptr;
	m_pTexture = texture;

	m_Vec3Position = Vector3(0, 0, 0);
	m_iHeight = 50;
	m_iWidth = 100;
	m_Vec3Scale = Vector3((float)m_iWidth / screenWidth, (float)m_iHeight / screenHeight, 1);
}
MainPlane::~MainPlane()
{
	//todo
}
