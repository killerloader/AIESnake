#include "Player.h"
#include "Input.h"

Player::Player()
{
	m_Length = 3;
	m_Speed = 1;
}

Player::~Player()
{

}

void Player::Update()
{
	TranslatePlayer();
}

void Player::TranslatePlayer()
{
	headpos += m_Direction;
}

void Player::SetDirection(char direction)
{
	if (direction == 'u')
	{
		m_Direction = glm::vec2(0,1);
	}

	else if (direction == 'd')
	{
		m_Direction = glm::vec2(0,-1);
	}

	else if (direction == 'l')
	{
		m_Direction = glm::vec2(-1,0);
	}

	else if (direction == 'r')
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

bool Player::Check() // Check if player is colliding with wall or itself
{
	//if ()
	//{
	//
	//}
	//
	//else
	//{
	//	return false;
	//}
}

	
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