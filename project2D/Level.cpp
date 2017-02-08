#include "Level.h"

void Level::Initializer()
{
	if (m_initialized)
		return;

	m_initialized = true;

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

//Deconstructor, destroys all data.
void Level::DeInitializer()
{
	if (!m_initialized)
		return;

	m_initialized = false;

	//Destroy player and food spawner objects.
	delete m_player;
	m_player = nullptr;

	delete m_foodSpawner;
	m_foodSpawner = nullptr;

	//Destroy all 2nd dimension arrays.
	for (int i = 0; i < MAP_SIZE_X; i++)
		delete[] m_MapArray[i];

	//Destroy first dimension array.
	delete[] m_MapArray;
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

bool Level::IsInitialized()
{
	return m_initialized;
}

void Level::Update()
{
	m_player->Update();
	//m_foodSpawner->
}

void Level::Draw()
{

}

void Level::SetMap(int x, int y, E_LevelSlot slotType)
{
	m_MapArray[x][y] = slotType;
}