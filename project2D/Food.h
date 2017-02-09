#pragma once

class Food
{
public:
	Food();
	~Food();
	void Start();
	
protected:
	aie::Texture* m_FoodTexture;
};