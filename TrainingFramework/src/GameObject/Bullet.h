#pragma once
#include"Sprite2D.h"
class Bullet :public Sprite2D
{
private:
	Vector2 m_move;
public:
	Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Bullet();

	void SetMove(Vector2 move) { m_move = move; }
	void Update(GLfloat time);
	void Init();
};
