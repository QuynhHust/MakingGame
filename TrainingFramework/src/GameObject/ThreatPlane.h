#pragma once
#include"Sprite2D.h"
#include<stdlib.h>
#include<time.h>

class ThreatPlane : public Sprite2D
{
public:
	ThreatPlane(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~ThreatPlane();
	enum TypeMove
	{
		LEVELONE = 51,
		LEVELTWO = 52,
	};
	bool GetIsLive() { return m_IsLive; }
	void SetIsLive(bool islive) { m_IsLive = islive; }
	TypeMove GetTypeMove() { return m_TypeMove; }
	void SetTypeMove() { m_TypeMove = LEVELTWO; }
	int GetCout() { return m_Cout; }
	void SetCout(int i) { m_Cout = i; }
	void SetRandPos(int i);

	void Update(GLfloat time) override;
private:
	int m_Cout;
	Vector2 m_move;
	TypeMove m_TypeMove;
};
