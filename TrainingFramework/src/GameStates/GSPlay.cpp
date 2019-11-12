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
	m_CoutTime = 0;
}


GSPlay::~GSPlay()
{
	//m_soloud.deinit();
	//m_soloud1.deinit();
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
	m_score = std::make_shared<Text>(shader, font, "score: ", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	//main character
	texture = ResourceManagers::GetInstance()->GetTexture("Fly");
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_Character = std::make_shared<MainCharacter>(model, shader, texture);
	m_Character->Set2DPosition(m_Character->Get2DPosition());
	m_Character->SetSize(100, 70);

	//Threat enemy one
	for (int i = 0; i < NUMENEMY; i++)
	{
		texture = texture = ResourceManagers::GetInstance()->GetTexture("ThreatOne");
		m_Threat = std::make_shared<ThreatPlane>(model, shader, texture);
		m_Threat->SetSize(150, 50);
		m_Threat->SetRandPos(i + 1);
		m_listThreatOne.push_back(m_Threat);
	}

	//animation coin
	texture = ResourceManagers::GetInstance()->GetTexture("coin1");
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	obj->Set2DPosition(130, 18);
	obj->SetSize(26, 26);
	obj->SetIsShow(true);
	m_listAnimation.push_back(obj);

	//animation colision
	texture = ResourceManagers::GetInstance()->GetTexture("explosion2");
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	m_Colision = std::make_shared<SpriteAnimation>(model, shader, texture, 10, 0.05f);
	m_Colision->SetSize(96,88);

	// myBullets
	MakeMyBullets();
	// ThreatBullets
	MakeThreatBullets();

	//sound game
	m_soloud.init();
	m_wav.load("shot.wav");
	m_soloud1.init();
	m_explosionWav.load("colision.wav");

	//open file luu tru score
	m_FileScore.open("score.txt", std::ios::out);
	if (m_FileScore.fail() == true)
	{
		printf("cannot open file!!!\n");
	}
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
		for (int i = 0; i < m_MyBullets.size(); i++)
		{
			if (m_MyBullets.at(i)->GetIsLive() == false)
			{
				m_MyBullets.at(i)->SetIsLive(true);
				m_MyBullets.at(i)->StartMove(m_Character->Get2DPosition());
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
		obj->SetIsShow(true);
	}
	for (int i = 0; i < m_MyBullets.size(); i++)
	{
		m_MyBullets[i]->Update(deltaTime);
		for (int j = 0; j < m_listThreatOne.size(); j++)
		{
			if (m_MyBullets[i]->CheckColision(m_listThreatOne[j])) //xu ly va cham cua dan myplane vs threatplane
			{
				int x = m_soloud1.play(m_explosionWav);
				m_soloud1.setVolume(x, 2.0f);
				m_MyBullets[i]->SetIsLive(false);
				m_listThreatOne[j]->SetIsLive(false);
				m_Colision->Set2DPosition(m_MyBullets[i]->Get2DPosition().x, m_MyBullets[i]->Get2DPosition().y);
				m_Colision->SetIsShow(true);
				m_point++;
			}
		}
		
	}
	MakeMyBullets();
	MakeThreatBullets();
	if (m_Character->GetIsLive() == true)
	{
		m_Character->Update(deltaTime);
	}
	else
	{
		m_FileScore<<m_point;
		m_FileScore.close();
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_End);
		
	}
	for (int i = 0;i<m_listThreatOne.size();i++)
	{
		m_listThreatOne[i]->Update(deltaTime);
		m_listThreatOne[i]->SetRandPos(i);
		if (m_listThreatOne[i]->CheckColision(m_Character) == true)
		{
			m_Character->SetIsLive(false);
		}
		//threat ban dan
		if ((m_CoutTime % 100) == 0) // sau 100 lan update
		{
			for (int j = 0; j < m_ThreatBullets.size(); j++)
			{
				if (m_ThreatBullets[j]->GetIsLive() == false)
				{
					m_ThreatBullets[j]->SetIsLive(true);
					m_ThreatBullets[j]->StartMove(m_listThreatOne[i]->Get2DPosition()+Vector2(-50,20));
					break;
				}
			}
		}
	}
	for (int i = 0; i < m_ThreatBullets.size(); i++)
	{
		m_ThreatBullets[i]->Update(deltaTime);
		if (m_ThreatBullets[i]->CheckColision(m_Character)) //xu ly va cham cua dan ThreatPlane vs MyPlane
			{
				int x = m_soloud1.play(m_explosionWav);
				m_soloud1.setVolume(x, 2.0f);
				m_ThreatBullets[i]->SetIsLive(false);
				m_Character->SetIsLive(false);
				m_Colision->Set2DPosition(m_ThreatBullets[i]->Get2DPosition().x, m_ThreatBullets[i]->Get2DPosition().y);
				m_Colision->SetIsShow(true);
				m_Character->SetIsLive(false);
			}

	}
	//m_Threat->Update(deltaTime);
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
	//point
		std::string s = "Score: "+std::to_string(m_point);
		m_score->SetText(s);
		m_CoutTime++;
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_BackGround2->Draw();
	for (auto obj : m_listAnimation)
	{
		obj->Draw();
	}
	for (auto bul : m_MyBullets)
	{
		bul->Draw();
	}
	for (auto bul : m_ThreatBullets)
	{
		bul->Draw();
	}
	for (auto thr : m_listThreatOne)
	{
		if(thr->GetIsLive() == true)
		thr->Draw();
	}
	m_score->Draw();
	m_Character->Draw();
	m_Character->SetMove(Vector2(0, 0));
	if (m_Colision->GetIsShow() == true)
	{
		m_Colision->Draw();
	}
}

void GSPlay::SetNewPostionForBullet()
{

}
void GSPlay::MakeMyBullets()
{
	if(IsListAvailability(m_MyBullets)==false)//neu listbull khong kha dung
	{
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		auto texture = ResourceManagers::GetInstance()->GetTexture("Bullet");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		std::shared_ptr<Bullets> bul = std::make_shared<Bullets>(model, shader, texture);
		bul->SetSize(15, 15);
		bul->Set2DPosition(-10, -10);
		m_MyBullets.push_back(bul);
		printf("makebull\n");
	}
}
void GSPlay::MakeThreatBullets()
{
	if (IsListAvailability(m_ThreatBullets) == false)//neu listbull khong kha dung
	{
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		auto texture = ResourceManagers::GetInstance()->GetTexture("Bullet");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		std::shared_ptr<Bullets> bul = std::make_shared<Bullets>(model, shader, texture);
		bul->SetSize(15, 15);
		bul->Set2DPosition(1024, 800);
		bul->SetDir(bul->DIR_LEFT);
		m_ThreatBullets.push_back(bul);
		printf("makeThreatbull\n");
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
