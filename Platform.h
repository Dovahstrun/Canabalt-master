#pragma once

//Library includes
#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>

//Project Include 
//#include "AnimationSystem.h"

class Platform
{
public:

	Platform();
	void Spawn();
	void Draw(sf::RenderTarget& _target);

	sf::FloatRect GetCollider();

private:

	//Assets
	sf::Sprite m_sprite;

};