#include "Player.h"
#include "Input.h"
#include "Level.h"

Player::Player()
{
	m_Length = 3;
	m_Speed = 1;
	m_timer = 0.0f;
}

Player::~Player()
{

}

void Player::Spawn()
{
	//Add head.
	Level::SetMap(3, 0, E_LevelSlot_SnakeHead);
	m_bodyList.push_back(Level::GetMapTile(3, 0));
	//Add body.
	Level::SetMap(2, 0, E_LevelSlot_SnakeBody);
	m_bodyList.push_back(Level::GetMapTile(2, 0));
	//Add tail.
	Level::SetMap(1, 0, E_LevelSlot_SnakeTail);
	m_bodyList.push_back(Level::GetMapTile(1, 0));
}

void Player::Update(float dt)
{
	aie::Input* input = aie::Input::getInstance();

	SetDirection(' ');

	// use arrow keys to move camera
	if (input->isKeyDown(aie::INPUT_KEY_UP))
		SetDirection('u');

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		SetDirection('d');

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		SetDirection('l');

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		SetDirection('r');
	
	m_timer += dt;

	if (m_timer >= 0.2f)
	{
		m_timer -= 0.2f;
		TranslatePlayer();
	}
	
	//SetTail()
}

void Player::TranslatePlayer()
{
	//tailpos = lastbody's pos

	//m_Direction

	if (m_bodyList.front()->X + m_Direction.x >= MAP_SIZE_X || m_bodyList.front()->Y + m_Direction.y >= MAP_SIZE_Y || m_bodyList.front()->X + m_Direction.x < 0 || m_bodyList.front()->Y + m_Direction.y < 0 || (m_Direction.x == 0 && m_Direction.y == 0))
		return;

	//Keep checking for collisions until there is nothing
	bool doLoop = true;
	while (doLoop)
	{
		//Check for collisions
		switch (Level::GetMap(m_bodyList.front()->X + m_Direction.x, m_bodyList.front()->Y + m_Direction.y))
		{
		case E_LevelSlot_Food://Hit food
		{
			Level::SetMap(m_bodyList.front()->X, m_bodyList.front()->Y, E_LevelSlot_SnakeBody);
			Level::SetMap(m_bodyList.front()->X + m_Direction.x, m_bodyList.front()->Y + m_Direction.y, E_LevelSlot_SnakeHead);
			const MapTile* newHead = Level::GetMapTile(m_bodyList.front()->X + m_Direction.x, m_bodyList.front()->Y + m_Direction.y);
			m_bodyList.push_front(newHead);
			break;
		}
		case E_LevelSlot_Wall:doLoop = false; break;
		//case E_LevelSlot_SnakeBody:
		//case E_LevelSlot_SnakeTail:doLoop = false; break;
		case E_LevelSlot_Empty:doLoop = false; break;
		}
	}

	/*
		Note: Must use the setmap function and not set it directly with the maptile pointer.
		This is so the map knows what's being changed, as it has to plan accordingly.
	*/

	//HEAD

	//Set the current head to a body.
	Level::SetMap(m_bodyList.front()->X, m_bodyList.front()->Y, E_LevelSlot_SnakeBody);

	//Create a new head infront of the old head.
	Level::SetMap(m_bodyList.front()->X + m_Direction.x, m_bodyList.front()->Y + m_Direction.y, E_LevelSlot_SnakeHead);

	//Get a pointer to the new head tile.
	const MapTile* newHead = Level::GetMapTile(m_bodyList.front()->X + m_Direction.x, m_bodyList.front()->Y + m_Direction.y);

	//Push the new tile onto the list of body parts at the start.
	m_bodyList.push_front(newHead);

	//TAIL

	//Set the old tail to an empty slot.
	Level::SetMap(m_bodyList.back()->X, m_bodyList.back()->Y, E_LevelSlot_Empty);

	//Remove the old tail from the body list.
	m_bodyList.pop_back();

	//Set the body peice behind the tail into the new tail.
	Level::SetMap(m_bodyList.back()->X, m_bodyList.back()->Y, E_LevelSlot_SnakeTail);

	//Remember the direction we moved in so that we cannot move in the opposite direction next time.
	m_lastDir = m_Direction;
}

void Player::SetDirection(char direction)
{
	if (direction == 'u' && -m_lastDir != glm::vec2(0, 1))
	{
		m_Direction = glm::vec2(0,1);
	}

	else if (direction == 'd' && -m_lastDir != glm::vec2(0, -1))
	{
		m_Direction = glm::vec2(0,-1);
	}

	else if (direction == 'l' && -m_lastDir != glm::vec2(-1, 0))
	{
		m_Direction = glm::vec2(-1,0);
	}

	else if (direction == 'r' && -m_lastDir != glm::vec2(1, 0))
	{
		m_Direction = glm::vec2(1,0);
	}

	else
	{
		//LUL
	}
}

void Player::SetSpeed(float Speed)
{

}

void Player::Eat() // add to list and increment length
{
	m_Length += 1;
}

//bool Player::CheckCollision() // Check if player is colliding with wall or itself
//{
//	if ()
//	{
//	
//	}
//	
//	else
//	{
//		return false;
//	}
//}

	
void Player::Reset()
{
	m_Length = 2;
}

void Player::Die()
{
	// Reset the game, set pos, play sound?
	Reset();
}

void Player::SetTail(int tailpos)
{

}