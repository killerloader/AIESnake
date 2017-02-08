#pragma once
#include "Renderer2D.h"
#include <glm\glm.hpp>

class Player
{
public: 

	Player();
	~Player();

	int m_Length;
	glm::vec2  m_Direction;
	float m_Speed;

	void SetDirection(char Direction);
	void SetSpeed(float Speed);
	void Eat();
	void Reset();
	void Die(); // call reset? redundant? LUL

	bool Check(); //collusion logic here


protected:
	aie::Texture*	m_texture;


private:

};