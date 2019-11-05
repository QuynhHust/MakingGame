#pragma once
#include"Sprite2D.h"
#include"Bullet.h"

class MainCharacter : public Sprite2D
{
private:
	Vector2 m_move;
public:
	std::list<std::shared_ptr<Bullet>> m_listBullet;
	MainCharacter(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~MainCharacter();

	//void SetBullet(std::shared_ptr<Bullet> bul);
	void SetMove(Vector2 vec2) { m_move = vec2; }
	void CharacterMove();
	void Update(GLfloat deltatime) override;

};
