#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "SpriteAnimation.h"
#include "MainCharacter.h"
#include "Bullets.h"
#include "ThreatPlane.h"

//new
extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
const Vector2 MOVE_UP = Vector2(0, -15);
const Vector2 MOVE_DOWN = Vector2(0, 15);
const Vector2 MOVE_RIGHT = Vector2(15, 0);
const Vector2 MOVE_LEFT = Vector2(-15, 0);
const GLint NUMENEMY = 6;


GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
	m_soloud.deinit();
}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition((GLfloat)(screenWidth / 2), (GLfloat)(screenHeight / 2));
	m_BackGround->SetSize(screenWidth, screenHeight);

	
	m_BackGround2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround2->Set2DPosition((GLfloat)(screenWidth+ screenWidth / 2), (GLfloat)(screenHeight / 2));
	m_BackGround2->SetSize(screenWidth, screenHeight);


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared<Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	//main character
	texture = ResourceManagers::GetInstance()->GetTexture("Fly");
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_Character = std::make_shared<MainCharacter>(model, shader, texture);
	m_Character->Set2DPosition(m_Character->Get2DPosition());
	m_Character->SetSize(100, 70);

	//Threat enemy one
	texture = texture = ResourceManagers::GetInstance()->GetTexture("ThreatOne");
	threat = std::make_shared<ThreatPlane>(model, shader, texture);
	threat->SetSize(150, 50);
	threat->Set2DPosition(900, 25);
	/*for (int i = 0; i < NUMENEMY; i++)
	{
		m_listThreatOne.push_back(thr);
	}*/

	//animation coin
	texture = ResourceManagers::GetInstance()->GetTexture("coin1");
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	obj->Set2DPosition(150, 30);
	obj->SetSize(52, 52);
	m_listAnimation.push_back(obj);
	//animation colision
	texture = ResourceManagers::GetInstance()->GetTexture("Explosion");
	m_Colision = std::make_shared<SpriteAnimation>(model, shader, texture, 5, 0.1f);
	m_Colision->SetSize(70,70);

	// Bullets
	MakeBullets();

	//sound game
	m_soloud.init();
	m_wav.load("shot.wav");
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
	}
		
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	if(bIsPressed)
	{
		for (int i = 0; i < m_listBullets.size(); i++)
		{
			if (m_listBullets.at(i)->GetIsLive() == false)
			{
				m_listBullets.at(i)->SetIsLive(true);
				m_listBullets.at(i)->StartMove(m_Character->Get2DPosition());
				int x = m_soloud.play(m_wav);
				m_soloud.setVolume(x, 1.0f);
				break;
			}
		}
		
	}
}

void GSPlay::Update(float deltaTime)
{
	for (auto obj : m_listAnimation)
	{
		obj->Update(deltaTime);
	}
	for (int i = 0; i < m_listBullets.size(); i++)
	{
		m_listBullets[i]->Update(deltaTime);
		if (m_listBullets[i]->CheckColision(threat))
		{
			m_listBullets[i]->SetIsLive(false);
			threat->SetIsLive(false);
			m_Colision->Set2DPosition(m_listBullets[i]->Get2DPosition().x, m_listBullets[i]->Get2DPosition().y);
			m_Colision->SetIsShow(true);
		}
	}
	MakeBullets();
	m_Character->Update(deltaTime);
	threat->Update(deltaTime);
	m_Colision->Update(deltaTime);

	//move background
	if (m_BackGround->Get2DPosition().x <= (GLfloat)(-screenWidth / 2))
	{
		m_BackGround->Set2DPosition((GLfloat)(2 * screenWidth) + m_BackGround->Get2DPosition().x, (GLfloat)(screenHeight/2));
	}
		m_BackGround->Set2DPosition(m_BackGround->Get2DPosition() - Vector2(100.0f, 0.0f)*deltaTime);

	if (m_BackGround2->Get2DPosition().x <= (GLfloat)(-screenWidth / 2))
	{
		m_BackGround2->Set2DPosition((GLfloat)(2 * screenWidth) + m_BackGround2->Get2DPosition().x, (GLfloat)(screenHeight / 2));
	}
	    m_BackGround2->Set2DPosition(m_BackGround2->Get2DPosition() - Vector2(100.0f, 0.0f)*deltaTime);
	
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_BackGround2->Draw();
	for (auto obj : m_listAnimation)
	{
		obj->Draw();
	}
	for (auto bul : m_listBullets)
	{
		bul->Draw();
	}
	for (auto thr : m_listThreatOne)
	{
		thr->Draw();
	}
	m_score->Draw();
	m_Character->Draw();
	m_Character->SetMove(Vector2(0, 0));
	threat->Draw();
	if (m_Colision->GetIsShow() == true)
	{
		m_Colision->Draw();
	}
}

void GSPlay::SetNewPostionForBullet()
{

}
void GSPlay::MakeBullets()
{
	if(IsListAvailability(m_listBullets)==false)//neu listbull khong kha dung
	{
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		auto texture = ResourceManagers::GetInstance()->GetTexture("Bullet");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		std::shared_ptr<Bullets> bul = std::make_shared<Bullets>(model, shader, texture);
		bul->SetSize(15, 15);
		bul->Set2DPosition(-1, -1);
		m_listBullets.push_back(bul);
		printf("makebull\n");
	}
}
bool GSPlay::IsListAvailability(std::vector<std::shared_ptr<Bullets>> list)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list.at(i)->GetIsLive() == false)
		{
			return true;// mot phan tu false
		}
	}
	return false;// tat ca is true
}
