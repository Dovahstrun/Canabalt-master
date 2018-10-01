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
	//Only process the animation if it is playing
	if (m_playing)
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

				//Should we loop?
				if (m_loop)
				{
					//We should not loop
					//Wrap around to the beginning
					m_currentFrame = 0;
				}
				else
				{
					//We should not loop
					//Set our frame as the last in the list
					m_currentFrame = m_frames.size() - 1;

					//Stop playback
					m_playing = false;
				}				
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
}

void Animation::Play()
{
	//Update our sprite to the current frame immediately
	if (m_sprite) //Is not equak to 0 aka null aka nullptr
	{
		m_sprite->setTexture(*m_frames[m_currentFrame]);
	}

	//Avoid a divide by zero error
	if (m_playBackSpeed != 0)
	{
		//Set playback to true
		m_playing = true;

		//determine time for next frame change
		//Convert frames per second to seconds per frame
		float timeToChange = 1.0f / m_playBackSpeed;
		m_nextFrameChange = sf::seconds(timeToChange);
	}
}

void Animation::Pause()
{
	//stop playback, keep current frame as is
	m_playing = false;
}

bool Animation::isPlaying()
{
	//Tell the calling code if we are currently playing
	return m_playing;
}

void Animation::Stop()
{
	//Stop playback and reset to first frame
	m_playing = false;
	m_currentFrame = 0;
}

void Animation::addFrame(sf::Texture& _newFrame)
{
	m_frames.push_back(&_newFrame);
}

void Animation::SetSprite(sf::Sprite& _sprite)
{
	m_sprite = &_sprite;
}

void Animation::setPlayBackSpeed(float _framesPerSecond)
{
	m_playBackSpeed = _framesPerSecond;

	//If the playback speed is zero, pause to protect from divide by zero error
	if (m_playBackSpeed == 0)
	{
		Pause();
	}
}

void Animation::setLoop(bool _loop)
{
	m_loop = _loop;
}