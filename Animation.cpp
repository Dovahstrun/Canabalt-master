//Project includes
#include "Animation.h"

Animation::Animation()
	: m_frames()
	, m_sprite (nullptr)
	, m_playBackSpeed (15.0f)
	, m_loop (false)
	, m_playing (false)
	, m_nextFrameChange ()
	, m_currentFrame (0)
{

}

void Animation::Update(sf::Time _frameTime)
{
	//is it time to change to a new frame?
	m_nextFrameChange -= _frameTime;
	if (m_nextFrameChange.asSeconds() <= 0)
	{
		//Its time to change the frame

		//Change to the next frame
		++m_currentFrame;

		//Did we reach the end?
		if (m_currentFrame >= m_frames.size())
		{
			//We did reach the end

			//TODO: What if no loop?

			//Wrap around to the beginning
			m_currentFrame = 0;
		}

		//Update sprites texture to match new frame
		//Does our sprite exist
		if (m_sprite) //Is not equak to 0 aka null aka nullptr
		{
			m_sprite->setTexture(*m_frames[m_currentFrame]);
		}

		//determine time for next frame change
		//Convert frames per second to seconds per frame
		float timeToChange = 1.0f / m_playBackSpeed;
		m_nextFrameChange = sf::seconds(timeToChange);

	}
}

void Animation::addFrame(sf::Texture& _newFrame)
{
	m_frames.push_back(&_newFrame);
}

void Animation::setSprite(sf::Sprite& _sprite)
{
	m_sprite = &_sprite;
}