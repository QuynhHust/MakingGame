#include"MainCharacter.h"

extern GLint screenWidth;
extern GLint screenHeight;

MainCharacter::MainCharacter(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	:Sprite2D(model, shader, texture)
{
	m_pCamera = nullptr;
	m_move = Vector2(0,0);
	m_Vec2DPos = Vector2(70, 250);
	m_IsLive = true;

	m_Vec3Position = Vector3(0, 0, 0);
	m_iHeight = 50;
	m_iWidth = 100;
	m_Vec3Scale = Vector3((float)m_iWidth / screenWidth, (float)m_iHeight / screenHeight, 1);
	
}
MainCharacter::~MainCharacter()
{
	//todo
}


void MainCharacter::CharacterMove()
{
	//
}

void MainCharacter::Update(GLfloat time) 
{
		m_Vec2DPos += m_move * 60 * time;
		Set2DPosition(m_Vec2DPos);
		if (m_Vec2DPos.y <= 35) { m_Vec2DPos.y = 35; }
		else if (m_Vec2DPos.y >= screenHeight - 35) { m_Vec2DPos.y = screenHeight - 35; }
		else if (m_Vec2DPos.x <= 50) { m_Vec2DPos.x = 50; }
		else if (m_Vec2DPos.x >= screenWidth - 50) { m_Vec2DPos.x = screenWidth - 50; }
}