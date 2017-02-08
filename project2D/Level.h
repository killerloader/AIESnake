#pragma once

#include "Player.h"
#include "FoodSpawner.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#define MAP_SIZE_X 16
#define MAP_SIZE_Y 16
#define MAP_CELLSIZE_X 32
#define MAP_CELLSIZE_Y 32

enum E_LevelSlot
{
	E_LevelSlot_Wall = -1,
	E_LevelSlot_Empty = 0,
	E_LevelSlot_Food,
	E_LevelSlot_SnakeBody,
	E_LevelSlot_SnakeHead,
	E_LevelSlot_SnakeTail
};

struct MapTile
{
	MapTile(E_LevelSlot type, int x, int y)
	{
		SlotType = type;
		ArrayID = -1;
		X = x;
		Y = y;
	}

	E_LevelSlot SlotType;
	int ArrayID;	//Remembered point in the map array. For optimization.
	int X, Y;//X and Y slot position.
};

class Level
{
public:
	static void Update(float dt);
	static void Draw(aie::Renderer2D& renderer);
	static void Initializer();
	static void DeInitializer();
	static void SetMap(int x, int y, E_LevelSlot slotType);
	static bool GetMapOccupied(int x, int y);
	static bool IsInitialized();
	static E_LevelSlot GetMap(int x, int y);
	static const MapTile& GetMapTile(int x, int y);

private:
	static bool m_initialized;
	static Player* m_player;
	static FoodSpawner* m_foodSpawner;
	static MapTile*** m_MapArray;
	static MapTile** m_MapTiles;//Optimization, so we can ignore map tiles which don't actually exist.
	static int m_MapTileCount;
	static int m_Score;
	static aie::Font* m_font;
};