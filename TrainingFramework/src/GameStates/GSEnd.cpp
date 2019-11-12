#include "GSEnd.h"


extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSEnd::GSEnd()
{
}


GSEnd::~GSEnd()
{
}



void GSEnd::Init()
{
	// mo file score.txt de lay point
	std::fstream m_FileScore("score.txt", std::ios::in);
	m_FileScore>>m_yourscore;


	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(115, 40);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
	});
	m_listButton.push_back(button);

	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_quit");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(115, 100);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		exit(0);
	});
	m_listButton.push_back(button);

	// your point
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_point = std::make_shared< Text>(shader, font,"Your Score: "+std::to_string(m_yourscore), TEXT_COLOR::RED, 2.0);
	m_point->Set2DPosition(Vector2(screenWidth / 2 - 120, 120));
}

void GSEnd::Exit()
{
}


void GSEnd::Pause()
{

}

void GSEnd::Resume()
{

}


void GSEnd::HandleEvents()
{

}

void GSEnd::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSEnd::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSEnd::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	m_point->Update(deltaTime);
}

void GSEnd::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_point->Draw();
}