#pragma once
#include <glm\glm.hpp>

#define SizeOfList 16
#define RespawnTime 10.0f

class FoodSpawner
{
public:

	FoodSpawner(float dt);
	~FoodSpawner();
	
	void Spawn(float dt);
	void SetFood();

protected:
	int m_FoodObject;
	
	bool m_DoesFoodExist;

	glm::vec2 m_MapLocation;

	int m_MapX;
	int m_MapY;
	float m_Timer;
};