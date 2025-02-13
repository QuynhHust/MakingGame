#pragma once
#include "gamestatebase.h"
#include "GameButton.h"

class SpriteAmination;
class Sprite2D;

class GSMenu :
	public GameStateBase
{
public:
	GSMenu();
	~GSMenu();
	
	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

private:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::vector<std::shared_ptr<SpriteAmination>> m_listAmination;
	std::list<std::shared_ptr<GameButton>>	m_listButton;

};

