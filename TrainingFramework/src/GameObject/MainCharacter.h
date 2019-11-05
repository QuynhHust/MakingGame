#pragma once
#include"Sprite2D.h"

class MainCharacter : public Sprite2D
{
private:
	Vector2 m_move;
public:
	MainCharacter(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~MainCharacter();

	void SetMove(Vector2 vec2) { m_move = vec2; }
	void CharacterMove();
	void Update(GLfloat deltatime) override;

};
