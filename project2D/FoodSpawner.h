#pragma once
#define SizeOfList 16

class MapTile;

class FoodSpawner
{
public:

	FoodSpawner();
	~FoodSpawner();
	
	void Spawn();

	void Update(float dt);

private:
	const MapTile* m_oldMapTile;
	float m_timer;
	//int m_ListOfFood[SizeOfList];
};