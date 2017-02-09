#include "Player.h"
#include "Input.h"
#include "Level.h"

Player::Player()
{
	m_Length = 3;
	m_Speed = 1;
	m_Direction = glm::vec2(1, 0);
	myQueue = new std::deque<PlayerBody>;
	
	PlayerBody temp = PlayerBody(1, 1); // Tail
	myQueue->push_back(temp);
	Level::SetMap(1, 1, E_LevelSlot_SnakeTail, E_BlockFacing_Right);

	temp = PlayerBody(2, 1); // Body
	myQueue->push_front(temp);
	Level::SetMap(2, 1, E_LevelSlot_SnakeBody, E_BlockFacing_Right);

	temp = PlayerBody(3, 1); // Head
	myQueue->push_front(temp);
	Level::SetMap(3, 1, E_LevelSlot_SnakeHead, E_BlockFacing_Right);

	m_HeadPos = temp;
	m_lastDirection = m_Direction;
}

Player::~Player()
{
	delete myQueue;
}

void Player::Update(float dt)
{
	aie::Input* input = aie::Input::getInstance();

	// use arrow keys to move camera
	if (input->isKeyDown(aie::INPUT_KEY_UP))
		SetDirection('u');

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		SetDirection('d');

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		SetDirection('l');

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		SetDirection('r');
	
	static float timer = 0; 


	if (timer >= GAME_STEP)
	{
		
		if (CheckCollision())
		{
			Reset();
			return;
		}
		Eat();

		TranslatePlayer();
		timer = 0;
	}

	timer += dt;
}

void Player::TranslatePlayer()
{
	E_BlockFacing newDir;

	if (m_Direction.x == 0 && m_Direction.y == -1)//down
		newDir = E_BlockFacing_Down;
	else 	if (m_Direction.x == 0 && m_Direction.y == 1)//up
		newDir = E_BlockFacing_Up;
	else 	if (m_Direction.x == 1 && m_Direction.y == 0)//right
		newDir = E_BlockFacing_Right;
	else 	if (m_Direction.x == -1 && m_Direction.y == 0)//left
		newDir = E_BlockFacing_Left;

	//Move tail (First so that we can't hit our tail if we're right behind it.
	Level::SetMap(myQueue->back().posX, myQueue->back().posY, E_LevelSlot_Empty);
	myQueue->pop_back();

	PlayerBody NewTail = PlayerBody(myQueue->back().posX, myQueue->back().posY);
	E_BlockFacing oldBehindTailDir = Level::GetMapTile(NewTail.posX, NewTail.posY)->Facing;
	Level::SetMap(NewTail.posX, NewTail.posY, E_LevelSlot_SnakeTail, oldBehindTailDir);

	//Move head
	m_HeadPos = myQueue->front();
	E_BlockFacing oldHeadDir = Level::GetMapTile(m_HeadPos.posX, m_HeadPos.posY)->Facing;

	m_lastDirection = m_Direction;
	Level::SetMap(m_HeadPos.posX, m_HeadPos.posY, E_LevelSlot_SnakeBody, oldHeadDir);

	PlayerBody NewHead = PlayerBody(m_HeadPos.posX + m_Direction.x, m_HeadPos.posY + m_Direction.y);
	myQueue->push_front(NewHead);
	Level::SetMap(NewHead.posX, NewHead.posY, E_LevelSlot_SnakeHead, newDir);

	m_HeadPos = NewHead;
}

void Player::SetDirection(char direction)
{
	if (direction == 'u' && -m_lastDirection != glm::vec2(0, 1))
	{
		m_Direction = glm::vec2(0,1);
	}

	else if (direction == 'd' && -m_lastDirection != glm::vec2(0, -1))
	{
		m_Direction = glm::vec2(0,-1);
	}

	else if (direction == 'l' && -m_lastDirection != glm::vec2(-1, 0))
	{
		m_Direction = glm::vec2(-1,0);
	}

	else if (direction == 'r' && -m_lastDirection != glm::vec2(1, 0))
	{
		m_Direction = glm::vec2(1,0);
	}

	else
	{	
		//LUL
	}
}

void Player::Eat() // add to list and increment length
{
	if (Level::GetMap(m_HeadPos.posX + m_Direction.x, m_HeadPos.posY + m_Direction.y) == E_LevelSlot_Food)
	{
		E_BlockFacing newDir;

		if (m_Direction.x == 0 && m_Direction.y == -1)//down
			newDir = E_BlockFacing_Down;
		else 	if (m_Direction.x == 0 && m_Direction.y == 1)//up
			newDir = E_BlockFacing_Up;
		else 	if (m_Direction.x == 1 && m_Direction.y == 0)//right
			newDir = E_BlockFacing_Right;
		else 	if (m_Direction.x == -1 && m_Direction.y == 0)//left
			newDir = E_BlockFacing_Left;

		Level::EatFood();

		//Remove Food
		Level::SetMap(m_HeadPos.posX + m_Direction.x, m_HeadPos.posY + m_Direction.y, E_LevelSlot_Empty);

		E_BlockFacing oldHeadDir = Level::GetMapTile(m_HeadPos.posX, m_HeadPos.posY)->Facing;

		m_lastDirection = m_Direction;
		Level::SetMap(m_HeadPos.posX, m_HeadPos.posY, E_LevelSlot_SnakeBody, oldHeadDir);

		m_HeadPos = PlayerBody(m_HeadPos.posX + m_Direction.x, m_HeadPos.posY + m_Direction.y);
		myQueue->push_front(m_HeadPos);
		Level::SetMap(m_HeadPos.posX, m_HeadPos.posY, E_LevelSlot_SnakeHead, newDir);

		m_Length += 1;
		
		Level::AddScore();
	}
}

bool Player::CheckCollision() // Check if player is colliding with wall or itself
{
	PlayerBody NextSquare = PlayerBody(m_HeadPos.posX + m_Direction.x, m_HeadPos.posY + m_Direction.y);
	
	if (Level::GetMap(NextSquare.posX, NextSquare.posY) == E_LevelSlot_Wall)
	{
		return true;
	}
	else if (Level::GetMap(NextSquare.posX, NextSquare.posY) == E_LevelSlot_SnakeBody)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::Reset()
{
	for (int i = 0; i < MAP_SIZE_X; i++)
	{
		for (int j = 0; j < MAP_SIZE_Y; j++)
		{
			Level::SetMap(i, j, E_LevelSlot_Empty);
		}
	}
	
	m_Length = 3;
	delete myQueue;
	myQueue = new std::deque<PlayerBody>;

	PlayerBody temp = PlayerBody(1, 1); // Tail
	myQueue->push_back(temp);
	Level::SetMap(1, 1, E_LevelSlot_SnakeTail, E_BlockFacing_Right);

	temp = PlayerBody(2, 1); // Body
	myQueue->push_front(temp);
	Level::SetMap(2, 1, E_LevelSlot_SnakeBody, E_BlockFacing_Right);

	temp = PlayerBody(3, 1); // Head
	myQueue->push_front(temp);
	Level::SetMap(3, 1, E_LevelSlot_SnakeHead, E_BlockFacing_Right);

	m_HeadPos = temp;
	m_Direction = glm::vec2(1, 0);
	m_lastDirection = m_Direction;

	Level::EatFood();
	Level::ResetScore();
}

void Player::Die()
{
	// Reset the game, set pos, play sound?
	Reset();
}