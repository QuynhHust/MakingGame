#pragma once
#include"Sprite2D.h"

class MainPlane : public Sprite2D
{
private:
	int m_xPos;
	int m_yPos;
	int m_v;
public:
	MainPlane::MainPlane(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture,GLint xPos, GLint yPos);
	~MainPlane();

};
