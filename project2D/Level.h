#pragma once

#include "Player.h"
#include "FoodSpawner.h"

#define MAP_SIZE_X 16
#define MAP_SIZE_Y 16
#define MAP_CELLSIZE_X 32
#define MAP_CELLSIZE_Y 32

enum E_LevelSlot
{
	E_LevelSlot_Errortype = -1,
	E_LevelSlot_Empty = 0,
	E_LevelSlot_Food,
	E_LevelSlot_Snake
};

static class Level
{
public:
	void Initializer();
	void DeInitializer();
	void SetMap(int x, int y, E_LevelSlot slotType);
	E_LevelSlot GetMap(int x, int y);
	bool GetMapOccupied(int x, int y);
	bool IsInitialized();

	void Update();
	void Draw();

private:
	E_LevelSlot** m_MapArray;
	float m_Height;
	float m_Width;
	bool m_initialized = false;
	Player* m_player;
	FoodSpawner* m_foodSpawner;
};