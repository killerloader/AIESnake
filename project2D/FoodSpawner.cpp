#include "FoodSpawner.h"
#include "Level.h"

FoodSpawner::FoodSpawner()
{
	m_oldMapTile = nullptr;
	m_timer = 0.0f;
}

FoodSpawner::~FoodSpawner()
{

}

void FoodSpawner::Spawn()
{
	int x, y;
	while (true)
	{
		y = rand() % MAP_SIZE_Y;
		x = rand() % MAP_SIZE_X;

		if (Level::GetMapOccupied(x, y))
			continue;

		Level::SetMap(x, y, E_LevelSlot_Food);
		m_oldMapTile = Level::GetMapTile(x, y);

		break;
	}
}

void FoodSpawner::Update(float dt)
{
	if (m_oldMapTile == nullptr || m_oldMapTile->SlotType != E_LevelSlot_Food)
	{
		m_timer += dt;
		if (m_timer > 1.0f)
		{
			Spawn();
			m_timer = 0.0f;
		}
	}
}