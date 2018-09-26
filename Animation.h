#pragma once

//Library includes
#include <vector>
#include <SFML/Graphics.hpp>

class Animation
{

public:

	Animation();

	void Update(sf::Time _frameTime);

	void play();
	void pause();
	void stop();

	bool isPlaying();

	void addFrame(sf::Texture& _newFrame);
	void setSprite(sf::Sprite& _sprite);
	void setPlayBackSpeed(float _framesPerSecond);
	void setLoop(bool _setLoop);

private:

	//Settings
	std::vector<sf::Texture*> m_frames;
	sf::Sprite* m_sprite;
	bool m_loop;
	float m_playBackSpeed;

	//state
	int m_currentFrame;
	sf::Time m_nextFrameChange;
	bool m_playing;
};