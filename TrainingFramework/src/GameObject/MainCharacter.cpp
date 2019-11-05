#include"MainCharacter.h"

extern GLint screenWidth;
extern GLint screenHeight;

MainCharacter::MainCharacter(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	:Sprite2D()
{
	m_pModel = model;
	m_pShader = shader;
	m_pCamera = nullptr;
	m_pTexture = texture;
	m_move = Vector2(0,0);

	m_Vec3Position = Vector3(0, 0, 0);
	m_iHeight = 50;
	m_iWidth = 100;
	m_Vec3Scale = Vector3((float)m_iWidth / screenWidth, (float)m_iHeight / screenHeight, 1);
	
}
MainCharacter::~MainCharacter()
{
	//todo
}


void MainCharacter::CharacterMove()
{
	m_Vec2DPos += m_move;
}

void MainCharacter::Update(GLfloat deltatime) {
	m_Vec2DPos += m_move;
}