#pragma once
#include"Sprite2D.h"
class Bullets :public Sprite2D
{

private:
	bool m_IsMove;
	unsigned int m_BulletType;
	unsigned int m_BulletDir;
	Vector2 m_move;
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

	bool GetIsMove() { return m_IsMove; }
	void SetIsMove(bool b) { m_IsMove = b; }
	
	void StartMove(Vector2 vec2,Vector2 move) { Set2DPosition(vec2); m_move = move; }
	void Update(GLfloat time) override;
	
};

