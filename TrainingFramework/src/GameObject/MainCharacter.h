#pragma once
#include"Sprite2D.h"

class MainCharacter : public Sprite2D
{
private:
	bool m_IsLive;
	Vector2 m_move;
public:
	MainCharacter(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~MainCharacter();

	void SetMove(Vector2 vec2) { m_move = vec2; }
	bool GetIsLive() { return m_IsLive; }
	void SetIsLive(bool islive) { m_IsLive = islive; }
	void CharacterMove();
	void Update(GLfloat time);

};

