/// --------------------------------------
/// Includes
/// --------------------------------------
// Libraries
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

// Project Includes
#include "AssetManager.h"
#include "Player.h"
#include "Platform.h"


int main()
{
	/// --------------------------------------
	/// GAME SETUP
	/// --------------------------------------

	// Render Window creation
	sf::RenderWindow gameWindow;
	gameWindow.create(sf::VideoMode::getDesktopMode(), "Canabalt",
		sf::Style::Titlebar | sf::Style::Close);

	// Timer functionality
	sf::Clock gameClock;

	// Create AssetManager
	AssetManager assets;

	//Seed a random number generator
	srand(time(NULL));

	// Testing AssetManager
	sf::Sprite testSprite;
	testSprite.setTexture(AssetManager::GetTexture("graphics/playerJump.png"));

	//Test sound
	sf::Sound testSound;
	testSound.setBuffer(AssetManager::GetSoundBuffer("audio/death.wav"));
	testSound.play();

	//create text
	sf::Text testText;
	testText.setFont(AssetManager::GetFont("fonts/mainfont.ttf"));
	testText.setString("Test Text");

	//Create player
	Player player;
	player.Spawn();

	//Create the game camera
	sf::View camera = gameWindow.getDefaultView();

	//Create platforms
	Platform platform;
	platform.Spawn();

	/// --------------------------------------
	/// END GAME SETUP
	/// --------------------------------------


	/// --------------------------------------
	/// GAME LOOP
	/// --------------------------------------
	while (gameWindow.isOpen())
	{
		/// --------------------------------------
		/// INPUT
		/// --------------------------------------
		sf::Event event;
		while (gameWindow.pollEvent(event))
		{

			player.Input(event);

			if (event.type == sf::Event::Closed)
			{
				gameWindow.close();
			} // End if (closed)
		} // end event polling loop

		/// --------------------------------------
		/// END INPUT
		/// --------------------------------------



		/// --------------------------------------
		/// UPDATE
		/// --------------------------------------

		sf::Time frameTime = gameClock.restart();


		player.Update(frameTime);

		//Update camera position
		camera.setCenter(player.GetPosition().x + camera.getSize().x * 0.4f, camera.getCenter().y);

		/// --------------------------------------
		/// END UPDATE
		/// --------------------------------------



		/// --------------------------------------
		/// DRAW
		/// --------------------------------------

		// Clear the window to a single colour
		gameWindow.clear();

		//Draw the game world using the camera
		gameWindow.setView(camera);

		player.Draw(gameWindow);
		platform.Draw(gameWindow);

		//Draw the UI to the window

		gameWindow.setView(gameWindow.getDefaultView());
		// Display the window contents to the screen
		gameWindow.display();

		/// --------------------------------------
		/// END DRAW
		/// --------------------------------------

	} // end of the game while loop

	/// --------------------------------------
	/// END GAME LOOP
	/// --------------------------------------

	// exit point for the program
	return 0;

} // end of the main() function
