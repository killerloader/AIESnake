#include "FoodSpawner.h"
#include "Level.h"
#include <time.h>

FoodSpawner::FoodSpawner(float dt)
{
	srand(time(NULL));
}

FoodSpawner::~FoodSpawner()
{

}

void FoodSpawner::Spawn()
{
	if (m_DoesFoodExist == false)
	{
		Level::SetMap((rand() % 16 + 1), (rand() % 16 + 1), E_LevelSlot_Food);
		m_DoesFoodExist == true;
	}
}

void FoodSpawner::SetFood()
{
	m_DoesFoodExist == false;
}

