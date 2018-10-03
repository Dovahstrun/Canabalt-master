//Project Includes
#include "Player.h"
#include "AssetManager.h"

//Constants
#define JUMP_SPEED -1500.0f
#define GRAVITY 2000.0f
#define RUN_SPEED_INITIAL 500.0f
#define RUN_ACCEL 100.0f

//Constructor
Player::Player()
	:m_sprite()
	,m_jumpSound()
	,m_deathSound()
	,m_landSound()
	,m_animation()
	,m_velocity(0.0f, 0.0f)
	,m_touchingGround(false)
{
	//Sprite Setup
	m_sprite.setTexture(AssetManager::GetTexture("graphics/playerJump.png"));
	 //Sound setup
	m_jumpSound.setBuffer(AssetManager::GetSoundBuffer("audio/jump.wav"));
	m_deathSound.setBuffer(AssetManager::GetSoundBuffer("audio/death.wav"));
	m_landSound.setBuffer(AssetManager::GetSoundBuffer("audio/landing.wav"));

	//Testing animation
	m_animation.SetSprite(m_sprite);

	Animation& runAnimation = m_animation.CreateAnimation("run");
	runAnimation.addFrame(AssetManager::GetTexture("graphics/playerRun1.png"));
	runAnimation.addFrame(AssetManager::GetTexture("graphics/playerRun2.png"));
	runAnimation.setLoop(true);
	runAnimation.setPlayBackSpeed(10.0f);


	Animation& jumpAnimation = m_animation.CreateAnimation("jump");
	jumpAnimation.addFrame(AssetManager::GetTexture("graphics/playerJump.png"));

	m_animation.Play("jump");
}

void Player::Input(sf::Event _gameEvent)
{
	//Check if the player has pressed the jump button
	if (_gameEvent.type == sf::Event::KeyPressed)
	{
		//Check if the button was space
		if (_gameEvent.key.code == sf::Keyboard::Space)
		{
			//Player has tried to jump

			//Play jump sound
			m_jumpSound.play();

			//Set the player's upward velocity
			m_velocity.y = JUMP_SPEED;

			//Play jump animation
			m_animation.Play("jump");
		}
	}
}


		/// --------------------------------------
		/// UPDATE
		/// --------------------------------------
void Player::Update(sf::Time _frameTime)
{
	//Process the animation
	m_animation.Update(_frameTime);

	//Apply gravity to our velocity
	if (m_touchingGround == false)
	{
		float velocityChange = GRAVITY * _frameTime.asSeconds();
		m_velocity.y += velocityChange;
	}

	//Move sprite base on velocity
	sf::Vector2f currentPosition = m_sprite.getPosition();
	sf::Vector2f positionChange = m_velocity * _frameTime.asSeconds();
	m_sprite.setPosition(currentPosition + positionChange);
}

void Player::Draw(sf::RenderTarget& _target)
{
	_target.draw(m_sprite);
}

void Player::Spawn()
{
	m_sprite.setPosition(0, 0);
	m_animation.Play("jump");
	m_velocity.y = 0;
	m_velocity.x = RUN_SPEED_INITIAL;
}

sf::Vector2f Player::GetPosition()
{
	return m_sprite.getPosition();
}

void Player::HandleCollision(sf::FloatRect _platform)
{
	//Record whether we used to be touching the grounf
	bool wereTouchingGround = m_touchingGround;
	//Assume we did not collide
	m_touchingGround = false;


	////Assume our collision will fail (that we're not touching the ground)
	//m_touchingGround = false;
	//Get the collider for the player
	sf::FloatRect playerCollider = m_sprite.getGlobalBounds();

	//does our sprite interesect the platofrms?
	if (playerCollider.intersects(_platform))
	{
		//Yes it intersects

		//Check if the bottom of the players feet is touching the top of the platform
		sf::FloatRect feetCollider = playerCollider;
		//Set the top of our feet to be 10 pixels from the bottom of the player collider
		feetCollider.top += playerCollider.height - 10;
		//Set our feet collider height to be 10 pixels
		feetCollider.height = 10;

		//Create platform top collider
		sf::FloatRect platformTop = _platform;
		platformTop.height = 10;

		//Are the feet touching the top of the platform
		if (feetCollider.intersects(platformTop))
		{
			//Yes feet are touching
			m_touchingGround = true;

			//Check if we are falling downward
			if (wereTouchingGround == false && m_velocity.y > 0)
			{
				//We have touched the ground
				m_animation.Play("run");
				m_landSound.play();
				m_velocity.y = 0;
				
			}
		}

	}
	//If there was not a collision, set touching ground to false
	if (!m_touchingGround && wereTouchingGround)
	{
		m_animation.Play("jump");
	}

}