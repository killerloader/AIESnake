#include "Player.h"
#include "Input.h"
#include "Level.h"

Player::Player()
{
	m_Length = 3;
	m_Speed = 1;
	m_Direction = glm::vec2(1, 0);
	myQueue = new std::deque<PlayerBody>;
	
	PlayerBody temp = PlayerBody(1, 1, 4); // Tail
	myQueue->push_back(temp);
	Level::SetMap(1, 1, E_LevelSlot_SnakeTail);

	temp = PlayerBody(2, 1, 2); // Body
	myQueue->push_front(temp);
	Level::SetMap(2, 1, E_LevelSlot_SnakeBody);

	temp = PlayerBody(3, 1, 3); // Head
	myQueue->push_front(temp);
	Level::SetMap(3, 1, E_LevelSlot_SnakeHead);

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


	if (timer >= .2)
	{
		
		if (CheckCollision())
		{
			Reset();
		}
		Eat();

		TranslatePlayer();
		timer = 0;
	}

	timer += dt;
}

void Player::TranslatePlayer()
{
	m_lastDirection = m_Direction;
	myQueue->front().ArrayID = 2;
	Level::SetMap(m_HeadPos.posX, m_HeadPos.posY, E_LevelSlot_SnakeBody);

	PlayerBody NewHead = PlayerBody(m_HeadPos.posX + m_Direction.x, m_HeadPos.posY + m_Direction.y, 3);
	myQueue->push_front(NewHead);
	Level::SetMap(NewHead.posX, NewHead.posY, E_LevelSlot_SnakeHead);

	Level::SetMap(myQueue->back().posX, myQueue->back().posY, E_LevelSlot_Empty);
	myQueue->pop_back();

	PlayerBody NewTail = PlayerBody(myQueue->back().posX, myQueue->back().posY, 4);
	Level::SetMap(NewTail.posX, NewTail.posY, E_LevelSlot_SnakeTail);

	myQueue->front().ArrayID = 4;
	m_HeadPos = myQueue->front();
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

	PlayerBody NextSquare = PlayerBody(m_HeadPos.posX + m_Direction.x, m_HeadPos.posY + m_Direction.y, 3);

	if (Level::GetMap(NextSquare.posX, NextSquare.posY) == E_LevelSlot_Food)
	{
		PlayerBody NewHead = PlayerBody(m_HeadPos.posX + m_Direction.x, m_HeadPos.posY + m_Direction.y, 3);
		myQueue->push_front(NewHead);
		Level::SetMap(NewHead.posX, NewHead.posY, E_LevelSlot_SnakeHead);
	}

	m_Length += 1;
	Level::EatFood();

}

bool Player::CheckCollision() // Check if player is colliding with wall or itself
{
	PlayerBody NextSquare = PlayerBody(m_HeadPos.posX + m_Direction.x, m_HeadPos.posY + m_Direction.y, 3);
	
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

	PlayerBody temp = PlayerBody(1, 1, 4); // Tail
	myQueue->push_back(temp);
	Level::SetMap(1, 1, E_LevelSlot_SnakeTail);

	temp = PlayerBody(2, 1, 2); // Body
	myQueue->push_front(temp);
	Level::SetMap(2, 1, E_LevelSlot_SnakeBody);

	temp = PlayerBody(3, 1, 3); // Head
	myQueue->push_front(temp);
	Level::SetMap(3, 1, E_LevelSlot_SnakeHead);

	m_HeadPos = temp;
	m_Direction = glm::vec2(1, 0);
	m_lastDirection = m_Direction;
}

void Player::Die()
{
	// Reset the game, set pos, play sound?
	Reset();
}