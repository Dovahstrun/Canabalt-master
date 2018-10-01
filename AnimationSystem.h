#pragma once

// Library Includes
#include <SFML/Graphics.hpp>
#include <map>

// Project Includes
#include "Animation.h"

class AnimationSystem
{
public:

	AnimationSystem();

	// Setup
	void SetSprite(sf::Sprite& _sprite);
	Animation& CreateAnimation(std::string _name);

	void Play();
	void Play(std::string _newAnimation);
	void Pause();
	void Stop();

	void Update(sf::Time _frameTime);

private:

	sf::Sprite* m_sprite;
	std::map<std::string, Animation> m_animations;
	Animation* m_currentAnimation;

};
