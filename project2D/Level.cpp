#include "Level.h"

/*
	- Pointless comment here!
*/

void Level::Initializer()
{
	m_MapArray = new E_LevelSlot*[MAP_SIZE_X];

	for (int i = 0; i < MAP_SIZE_X; i++)
	{
		m_MapArray[i] = new E_LevelSlot[MAP_SIZE_Y];

		for (int ii = 0; ii < MAP_SIZE_Y; ii++)
		{
			m_MapArray[i][ii] = E_LevelSlot_Empty;
		}
	}

	m_foodSpawner = new FoodSpawner();
	m_player = new Player();
}

E_LevelSlot Level::GetMap(int x, int y)
{
	if (x < 0 || y < 0 || x > MAP_SIZE_X || y > MAP_SIZE_Y)
		return E_LevelSlot_Errortype;

	return m_MapArray[x][y];
}

bool Level::GetMapOccupied(int x, int y)
{
	return m_MapArray[x][y] != 0;
}

void Level::Update()
{
	//Player->
	//m_foodSpawner->
}

void Level::Draw()
{

}

void Level::SetMap(int x, int y, E_LevelSlot slotType)
{

}