#pragma once
#include "Renderer2D.h"
#include <glm\glm.hpp>
#include "Level.h"
#include <deque>   

class Player
{
public: 

	Player();
	~Player();

	struct PlayerBody
	{
		float posX;
		float posY;
		int ArrayID;
		
		PlayerBody()
		{

		}

		PlayerBody(float posx, float posy,int arrayid)
		{
			posX = posx;
			posY = posy;
			ArrayID = arrayid;
		}
	};

	void Update(float dt);
	void SetDirection(char Direction);
	//void SetSpeed(float Speed);
	void Eat();
	void Reset();
	void Die(); //call reset? redundant? LUL
	void TranslatePlayer();

	bool CheckCollision(); //collision logic here

	std::deque<PlayerBody>* myQueue;
	
	int m_Length;
	glm::vec2 m_Direction;
	float m_Speed;


protected:
	aie::Texture* m_texture;


private:
	PlayerBody m_HeadPos;
	PlayerBody* m_TailPos;
	PlayerBody* m_BodyPos1;
	PlayerBody* m_BodyPos2; // spot before tail
};