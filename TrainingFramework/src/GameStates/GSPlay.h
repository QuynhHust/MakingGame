#pragma once
#include "GameStatebase.h"

class Sprite2D;
class Sprite3D;
class Text;
class SpriteAnimation;
class MainCharacter;
class Bullets;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();
	void MakeBullets();
	void SetNewPostionForBullet();

private:

	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Text>  m_score;
	std::vector<std::shared_ptr<SpriteAnimation>> m_listAnimation;
	std::shared_ptr<MainCharacter> m_Character;
	std::vector<std::shared_ptr<Bullets>> m_listBullets;
	std::shared_ptr<Bullets> m_TempBullet;
};

