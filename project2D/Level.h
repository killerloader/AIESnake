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
	E_LevelSlot_SnakeBody,
	E_LevelSlot_SnakeHead,
	E_LevelSlot_SnakeTail
};

static class Level
{
public:
	void Update();
	void Draw();
	void Initializer();
	void DeInitializer();
	void SetMap(int x, int y, E_LevelSlot slotType);
	bool GetMapOccupied(int x, int y);
	bool IsInitialized();
	E_LevelSlot GetMap(int x, int y);

private:
	float m_Height;
	float m_Width;
	bool m_initialized = false;
	Player* m_player = nullptr;
	FoodSpawner* m_foodSpawner = nullptr;
	E_LevelSlot** m_MapArray = nullptr;
};