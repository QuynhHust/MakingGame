#include"ThreatPlane.h"

extern GLint screenWidth;
extern GLint screenHeight;

ThreatPlane::ThreatPlane(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	m_pCamera = nullptr;
	m_move = Vector2(0, 0);
	m_IsLive = true;
	m_TypeMove = LEVELONE;
	m_Cout = 0;
	m_Vec2DPos = Vector2(-200.0f, -200.0f);

	m_Vec3Position = Vector3(0, 0, 0);
	m_Vec3Scale = Vector3((float)m_iWidth / screenWidth, (float)m_iHeight / screenHeight, 1);

}
ThreatPlane::~ThreatPlane() 
{
	//
}

void ThreatPlane::Update(GLfloat time)
{
	if (m_IsLive == true)
	{
		if (m_TypeMove == LEVELONE)
		{
			m_move = Vector2(-200.0f, 0.0f)*time;
			if (m_Vec2DPos.x < -75) { m_IsLive = false; m_move = Vector2(0.0f, 0.0f); }
		}
		else if (m_TypeMove == LEVELTWO)
		{
			if (m_Cout <= 100) { m_move = Vector2(-200.0f, 0.0f)*time; }
			else if (100 < m_Cout&& m_Cout <= 500) { m_move = Vector2(-100.0f, 100.0f)*time; }
			else if (500<m_Cout&&m_Cout<=900) { m_move = Vector2(-100.0f, -100.0f)*time; }
			else m_Cout = 0;
		}
		m_Vec2DPos += m_move;
		Set2DPosition(m_Vec2DPos);
		m_Cout++;
	}
}