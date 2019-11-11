#include"Bullets.h"

extern GLint screenWidth;
extern GLint screenHeight;

Bullets::Bullets(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	:Sprite2D()
{
	m_pModel = model;
	m_pShader = shader;
	m_pCamera = nullptr;
	m_pTexture = texture;
	m_IsLive = true;
	m_BulletType = DEFAULT;
	m_BulletDir = 0;
	m_Vec2DPos = Vector2(-1, -1);

	m_Vec3Position = Vector3(0, 0, 0);
	m_iHeight = 50;
	m_iWidth = 100;
	m_Vec3Scale = Vector3((float)m_iWidth / screenWidth, (float)m_iHeight / screenHeight, 1);
}
Bullets::~Bullets()
{
	//todo
}

void Bullets::Update(GLfloat time)
{
	if (m_IsLive == true)
	{
		m_Vec2DPos += Vector2(500.0f*time, 0.0f);
		Set2DPosition(m_Vec2DPos);
		if (m_Vec2DPos.x <= 50 || m_Vec2DPos.x >= screenWidth - 50) { m_IsLive = false; }
	}
	else Set2DPosition(-1, -1);
}