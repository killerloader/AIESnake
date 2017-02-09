#pragma once
#include <glm\glm.hpp>

#define SizeOfList 16

class FoodSpawner
{
public:

	FoodSpawner(float dt);
	~FoodSpawner();
	
	void Spawn();
	void SetFood();

protected:
	int m_FoodObject;
	
	bool m_DoesFoodExist;

	glm::vec2 m_MapLocation;

	int m_MapX;
	int m_MapY;

};