#pragma once
#include"Sprite2D.h"
class Bullet :public Sprite2D
{

private:
	bool m_IsMove;
	unsigned int m_BulletType;
	unsigned int m_BulletDir;
	Vector2 m_move;
public:
	Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Bullet();

	enum BulletDir
	{
		DIR_UP = 11,
		DIR_DOWN = 12,
		DIR_RIGHT = 13,
		DIR_LEFT = 14,
	};
	enum BulletType
	{
		DEFAULT = 18,
		LAZE = 19,
	};
	void SetMove(Vector2 move) { m_move = move; }
	void Update(GLfloat time);
	
};
