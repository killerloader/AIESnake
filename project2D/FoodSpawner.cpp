#include "FoodSpawner.h"
#include "Level.h"
#include <time.h>

FoodSpawner::FoodSpawner(float dt)
{
	srand(time(NULL));

	m_DoesFoodExist = false;
}

FoodSpawner::~FoodSpawner()
{

}

void FoodSpawner::Spawn()
{
	if (m_DoesFoodExist == false)
	{

		m_MapX = rand() % MAP_SIZE_X;
		m_MapY = rand() % MAP_SIZE_Y;

		if (Level::GetMap(m_MapX, m_MapY) == E_LevelSlot_Empty)
		{
			Level::SetMap(m_MapX, m_MapY, E_LevelSlot_Food);
			m_DoesFoodExist = true;
		}
	}
}

void FoodSpawner::SetFood()
{
	m_DoesFoodExist = false;
}

