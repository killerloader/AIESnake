#pragma once
#include "Renderer2D.h"
#include <glm\glm.hpp>

class Player
{
public: 

	Player();
	~Player();

	struct PlayerBody
	{
		int posX;
		int posY;
		bool isActive;
	};

	void Update(float dt);
	void SetDirection(char Direction);
	void SetSpeed(float Speed);
	void Eat();
	void Reset();
	void Die(); //call reset? redundant? LUL
	void TranslatePlayer();
	void SetTail(int tailpos);
	void Spawn();

	bool CheckCollision(); //collusion logic here

	int m_Length;
	glm::vec2  m_Direction;
	float m_Speed;

protected:
	aie::Texture*	m_texture;


private:
	//headpos
	//position
	//tailpos
};