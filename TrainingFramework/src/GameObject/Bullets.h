#pragma once
#include"Sprite2D.h"
class Bullets :public Sprite2D
{
public:
	Bullets(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Bullets();

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
	
	void StartMove(Vector2 vec2 ) { Set2DPosition(vec2);}
	void Update(GLfloat time) override;
	void SetDir(BulletDir dir) { m_BulletDir = dir; }

private:
	unsigned int m_BulletType;
	BulletDir m_BulletDir;
	Vector2 m_move;
	
};

