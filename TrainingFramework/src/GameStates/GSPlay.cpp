#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include"SpriteAnimation.h"
#include"MainCharacter.h"
#include"Bullet.cpp"


//new
extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
const Vector2 MOVE_UP = Vector2(0, -15);
const Vector2 MOVE_DOWN = Vector2(0, 15);
const Vector2 MOVE_RIGHT = Vector2(15, 0);
const Vector2 MOVE_LEFT = Vector2(-15, 0);


GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared<Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));
	    
	//main character
	texture = ResourceManagers::GetInstance()->GetTexture("Fly");
	shader  = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_Character = std::make_shared<MainCharacter>(model,shader,texture);
	m_Character->Set2DPosition(m_Character->Get2DPosition());
	m_Character->SetSize(100, 70);

	//Bullet
	texture = ResourceManagers::GetInstance()->GetTexture("Bullet");
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_Bullet = std::make_shared<Bullet>(model, shader, texture);
	m_Bullet->Set2DPosition(500, 100);
	m_Bullet->SetSize(15, 10);

	//animation coin
	texture = ResourceManagers::GetInstance()->GetTexture("coin1");
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	obj->Set2DPosition(150, 30);
	obj->SetSize(52, 52);
	m_listAnimation.push_back(obj);
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed)
	{
		switch (key)
		{

		case KEY_UP:
		{
			m_Character->SetMove(MOVE_UP);

		}break;
		case KEY_DOWN:
		{
			m_Character->SetMove(MOVE_DOWN);

		}break;
		case KEY_RIGHT:
		{
			m_Character->SetMove(MOVE_RIGHT);
		}break;
		case KEY_LEFT:
		{
			m_Character->SetMove(MOVE_LEFT);
		}break;
		
		}
		m_Character->Update(0.01f);
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSPlay::Update(float deltaTime)
{
	for (auto obj : m_listAnimation)
	{
		obj->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	for (auto obj : m_listAnimation)
	{
		obj->Draw();
	}
	m_score->Draw();
	m_Character->Draw();
	m_Bullet->Draw();
	
}

void GSPlay::SetNewPostionForBullet()
{

}