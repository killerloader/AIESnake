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
		Level::SetMap((rand() % 16), (rand() % 16), E_LevelSlot_Food);
		m_DoesFoodExist = true;
	}
}

void FoodSpawner::SetFood()
{
	m_DoesFoodExist = false;
}

