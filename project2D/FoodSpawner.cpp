#include "FoodSpawner.h"
#include "Level.h"
#include <time.h>

FoodSpawner::FoodSpawner(float dt)
{
	srand(time(NULL));

	m_DoesFoodExist = false;

	m_Timer = 0.0f;
}

FoodSpawner::~FoodSpawner()
{

}

void FoodSpawner::Spawn(float dt)
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
	else
	{
		m_Timer += dt;

		if (m_Timer >= RespawnTime)
		{
			m_Timer = 0.0f;
			m_DoesFoodExist = false;
			Level::SetMap(m_MapX, m_MapY, E_LevelSlot_Empty);
		}
	}
}

void FoodSpawner::SetFood()
{
	m_DoesFoodExist = false;
}

