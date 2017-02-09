#pragma once
#include "Texture.h"
#include "application.h"

class Food : public aie::Application
{
public:
	Food();
	~Food();

	void Start();
	
protected:
	aie::Texture* m_FoodTexture;
};