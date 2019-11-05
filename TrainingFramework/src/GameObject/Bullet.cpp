#include"Bullet.h"

extern GLint screenWidth;
extern GLint screenHeight;

Bullet::Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	:Sprite2D()
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
Bullet::~Bullet()
{
	//todo
}

void Bullet::Update(GLfloat time)
{
	m_Vec2DPos += m_move;
	Set2DPosition(m_Vec2DPos);
	Draw();
	if (m_Vec2DPos.x <= 50) { m_Vec2DPos.x = 50; }
	else if (m_Vec2DPos.x >= screenWidth - 50) { m_Vec2DPos.x = screenWidth - 50;}
}
