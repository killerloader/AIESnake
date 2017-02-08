#include "Level.h"

//Initialize all static variables.
bool Level::m_initialized = false;
Player* Level::m_player = nullptr;
FoodSpawner* Level::m_foodSpawner = nullptr;
MapTile*** Level::m_MapArray = nullptr;
MapTile** Level::m_MapTiles = nullptr;
int Level::m_MapTileCount = 0;
int Level::m_Score = 0;
aie::Font* Level::m_font = nullptr;

void Level::Initializer()
{
	if (m_initialized)
		return;

	m_initialized = true;

	m_MapArray = new MapTile**[MAP_SIZE_X];

	for (int i = 0; i < MAP_SIZE_X; i++)
	{
		m_MapArray[i] = new MapTile*[MAP_SIZE_Y];

		for (int ii = 0; ii < MAP_SIZE_Y; ii++)
		{
			m_MapArray[i][ii] = new MapTile(E_LevelSlot_Empty, i, ii);
		}
	}

	m_foodSpawner = new FoodSpawner();
	m_player = new Player();

	//Setup map tiles with maximum number of tiles possible.
	m_MapTiles = new MapTile*[MAP_SIZE_X * MAP_SIZE_Y];

	for (int i = 0; i < MAP_SIZE_X * MAP_SIZE_Y; i++)
		m_MapTiles[i] = nullptr;

	m_MapTileCount = 0;

	//Load font:
	m_font = new aie::Font("./font/consolas.ttf", 32);

	SetMap(1, 1, E_LevelSlot_Food);
	SetMap(2, 1, E_LevelSlot_SnakeBody);
	SetMap(3, 1, E_LevelSlot_Food);
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

	//Destroy all actual objects
	for (int i = 0; i < MAP_SIZE_X; i++)
		for (int ii = 0; ii < MAP_SIZE_Y; ii++)
			delete m_MapArray[i][ii];
		
	//Destroy all 2nd dimension arrays.
	for (int i = 0; i < MAP_SIZE_X; i++)
		delete[] m_MapArray[i];

	//Destroy first dimension array.
	delete[] m_MapArray;

	delete[] m_MapTiles;
	m_MapTileCount = 0;

	//Destroy font.
	delete m_font;
}

E_LevelSlot Level::GetMap(int x, int y)
{
	if (x < 0 || y < 0 || x > MAP_SIZE_X || y > MAP_SIZE_Y)
		return E_LevelSlot_Errortype;

	return m_MapArray[x][y]->SlotType;
}

const MapTile& Level::GetMapTile(int x, int y)
{
	return *m_MapArray[x][y];
}

bool Level::GetMapOccupied(int x, int y)
{
	return m_MapArray[x][y]->SlotType != E_LevelSlot_Empty;
}

bool Level::IsInitialized()
{
	return m_initialized;
}

void Level::Update(float dt)
{
	m_player->Update(/* dt*/);
	//m_foodSpawner->Update(dt);
}

void Level::Draw(aie::Renderer2D& renderer)
{
	for (int i = 0; i < m_MapTileCount; i++)
	{
		switch (m_MapTiles[i]->SlotType)
		{
		case E_LevelSlot_Food: renderer.setRenderColour(1, 0, 0, 1); break;
		case E_LevelSlot_SnakeBody: renderer.setRenderColour(1, 1, 1, 1); break;
		case E_LevelSlot_SnakeHead: renderer.setRenderColour(1, 1, 1, 1); break;
		case E_LevelSlot_SnakeTail: renderer.setRenderColour(1, 1, 1, 1); break;
		}

		//Draw from corner instead of center.
		renderer.drawBox(m_MapTiles[i]->X * MAP_CELLSIZE_X + MAP_CELLSIZE_X / 2, m_MapTiles[i]->Y * MAP_CELLSIZE_Y + MAP_CELLSIZE_Y / 2, MAP_CELLSIZE_X, MAP_CELLSIZE_Y);
	}

	//Draw white score.
	renderer.setRenderColour(1, 1, 1, 1);
	char fps[32];
	sprintf_s(fps, 32, "Score: %i", m_Score);
	renderer.drawText(m_font, fps, 0, MAP_SIZE_X * MAP_CELLSIZE_X - 24);
}

void Level::SetMap(int x, int y, E_LevelSlot slotType)
{
	m_MapArray[x][y]->SlotType = slotType;

	//If not cached yet. Only add if not empty.
	if (m_MapArray[x][y]->ArrayID == -1 && slotType != E_LevelSlot_Empty)
	{
		m_MapArray[x][y]->ArrayID = m_MapTileCount;
		m_MapTiles[m_MapTileCount] = m_MapArray[x][y];
		m_MapTileCount++;
	}
	else if(m_MapArray[x][y]->ArrayID != -1 && slotType == E_LevelSlot_Empty)//If now empty, but has an array ID assigned.
	{
		//Move end to removed node, as order doesn't matter, and this is the quickest way of removing.
		//If there is only one value, or the value you are moving is the end, this should still work.
		m_MapTiles[m_MapArray[x][y]->ArrayID] = m_MapTiles[m_MapTileCount - 1];
		m_MapTiles[m_MapTileCount - 1]->ArrayID = m_MapTileCount - 1;//Update array ID for new position.
		m_MapTiles[m_MapTileCount - 1] = nullptr;
		m_MapTileCount--;

		//Remove from cached tiles.
		m_MapArray[x][y]->ArrayID = -1;
	}
}