#pragma once
#include "GameStatebase.h"

class Sprite2D;
class Sprite3D;
class Text;
class SpriteAnimation;
class MainCharacter;
class Bullets;
class ThreatPlane;

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
	void MakeMyBullets();
	void MakeThreatBullets();
	void SetNewPostionForBullet();
	bool IsListAvailability(std::vector<std::shared_ptr<Bullets>> list);
private:
	int m_point = 0;
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Sprite2D> m_BackGround2;
	std::shared_ptr<Text>  m_score;
	std::vector<std::shared_ptr<SpriteAnimation>> m_listAnimation;
	std::shared_ptr<MainCharacter> m_Character;
	std::vector<std::shared_ptr<Bullets>> m_MyBullets;
	std::vector<std::shared_ptr<Bullets>> m_ThreatBullets;
	std::shared_ptr<Bullets> m_TempBullet;
	SoLoud::Soloud m_soloud;
	SoLoud::Wav m_wav;
	SoLoud::Soloud m_soloud1;
	SoLoud::Wav m_explosionWav;
	std::vector<std::shared_ptr<ThreatPlane>> m_listThreatOne;
	std::shared_ptr<ThreatPlane> m_Threat;
	std::shared_ptr<SpriteAnimation> m_Colision;
	//std::vector<std::shared_ptr<ThreatPlane>> m_listThreatTwo;
};

