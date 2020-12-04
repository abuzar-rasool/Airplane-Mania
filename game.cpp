#include "game.hpp"
#include "unit.hpp"
#include <iostream>
#include <time.h>
#include "text.hpp"
#include "sound.hpp"

bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Airplane Mania", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}

			// loading media into various objects of different classes and customizing them
			startMenu.loadImage(gRenderer,"mainmenu.jpeg");
			startMenu.customize(gRenderer,0, 0, 600, 800);

			gamePausedMenu.loadImage(gRenderer, "bar2.png");
			gamePausedMenu.customize(gRenderer,300,350, 250, 220);

			bgSound.LoadMusic("background.wav");
			spawnPlaneSound.LoadSoundEffect("Plane_Spawn.wav");
			spawnBird1.LoadSoundEffect("Bird_Spawn1.wav");
			spawnBird2.LoadSoundEffect("Bird_Spawn2.wav");
			planeCrashSound.LoadSoundEffect("Plane_Blast.wav");
			birdDied1.LoadSoundEffect("BIrd_Scream3.wav");
			BirdPlaneCollision.LoadSoundEffect("Plane_BIrd_Coliision.wav");
			FlareSound.LoadSoundEffect("Flare.wav");
			Cheer.LoadSoundEffect("Cheer.wav");
			Score.LoadSoundEffect("Score.wav");

		}
	}

	return success;
}

bool Game::loadMedia()

{
	//Loading success flag
	bool success = true;

	assets = loadTexture("assets.png");
	gTexture = loadTexture("bg.jpg");
	if (assets == NULL || gTexture == NULL)
	{
		printf("Unable to run due to error: %s\n", SDL_GetError());
		success = false;
	}


	return success;
}

void Game::close()
{
	remove_all();
	//Free loaded images
	SDL_DestroyTexture(assets);
	assets = NULL;
	SDL_DestroyTexture(gTexture);

	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

// default func that's used for loading images
SDL_Texture *Game::loadTexture(std::string path)
{
	//The final texture
	SDL_Texture *newTexture = NULL;
	//Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

// updating the flare creating an animation
void Game::updateFlare(){
	for(Flare *i: flares){
		// checking if the flare is still on screen
		if(!i->isAlive()){
			// deleting the pointer
			delete i;
			flares.remove(i);
		}
		
	}
}

// this func update blasts
void Game::updateBlasts(){
	for(Blast *i: blasts){
		// checking if blast is going on
		if(!i->isAlive()){
			// deleting pointer
			delete i;
			blasts.remove(i);
		}
		
	}
}

// this func update the bird movement based on different conditions
void Game::updateBirds(){
	if (isPause == false) {
		for(Bird *i: birds){
			// checking if bird is alive
			if(!i->isAlive()){
				// checking if a bird is scared or not
				if(i->get_scared() == true){	
					Score.playSoundEffect();
					// set score
					set_score(5);
				}
				else{
					// set score if the bird dieds
					set_score(-10); //Bird Died
				}

				// deleting pointer
				delete i;
				birds.remove(i);
			}
		}
	}
}

// this updates the planes based on different conditions
void Game::updatePlanes(){
	for(Plane *i: planes){
		// if plane is alive means no collisions
		if(!i->isAlive()){
			try{

			}catch(exception e){
				printf("There was an exception");
			}
			blasts.push_back(new Blast(assets, i->getMover()));
			set_score(-30); //Plane Crashed
			planeCrashSound.playSoundEffect();
			planes.remove(i);
			delete i;
		}
		// this is true when a plane passes successfully without collision
		else if (i->getMover().x > 800){
			set_score(50);
			//Safe Passage Successful
			// sound for successful passage
			planes.remove(i);
		}	
	}
}

// this func spawns birds in the game loop
void Game::spawnBirds(){
	if (isPause == false) {
		for (int i = 0; i < no_of_birds; i++)
	{
		//Randomly spawn Bird1, Bird2 and Bir
		int rnd = rand() % 3 + 1;
		if (rnd == 1)
		{
			birds.push_back(new Bird1(assets));
			spawnBird1.playSoundEffect();
		}
		else if(rnd==2)
		{
			birds.push_back(new Bird2(assets));
			spawnBird2.playSoundEffect();
		}else{
			birds.push_back(new Bird3(assets));
			spawnBird1.playSoundEffect();
		}
		}
	}
}

// this func handles the score count
void Game::set_score(int s){
	score = score+s;
	if(s > 0){
		Score.playSoundEffect();
	}
	
}

// this func handles the entire collision logic
void Game::Check4Collision(){
	for (Bird *i : birds){
		for (Plane *j : planes)
		{	
			// this condition is true when bird collides with a plane
			if (abs(i->getMover().x - j->getMover().x) <= j->getMover().w && abs(i->getMover().y - j->getMover().y) <= j->getMover().h && j->stillFlying())
			{	
				// calling crashed func which calls crashing animation
				j->crashed();
				i->crashed();
				// sound effect for collision
				BirdPlaneCollision.playSoundEffect();
				//cout << "Thuk Gaya Jhaaz"<<endl;
			}
		}
		for (Flare *k : flares)
		{	
			// this condition is true when flare hits a bird
			if (abs(i->getMover().x - k->getMover().x) <= i->getMover().w && abs(i->getMover().y - k->getMover().y) <= i->getMover().h && i->stillFlying())
			{

				i->crashed();
				k->collisionhappen();
				birdDied1.playSoundEffect();
				//cout << "Bird Margai"<<endl;

			}
			// this condition is true when bird gets scared by the nearby flare
			else if(abs(i->getMover().x - k->getMover().x) <= i->getMover().w+100 && abs(i->getMover().y - k->getMover().y) <= i->getMover().h+100 && i->stillFlying() && k->collide && !i->scare){
				i->scared();
				k->collisionhappen();
			}
			if (k->getMover().y<0){
				flares.remove(k);
			}
		}
	}
}

// func used for spawning planes
void Game::spawnPlanes()
{
	for (int i = 0; i < no_of_planes; i++)
	{
		planes.push_back(new Plane(assets));
		spawnPlaneSound.playSoundEffect();
	}
}

// this func contains the timer logic
void Game::timer(){
	if (gameState == "running" && isPause == false){
		static time_t start = time(0);
		static time_t secs = 0, temp;
		static int count = 0;
		
		// checking if game is paused
		if (pauseflag == true){
			start = time(0)-runtime;
			pauseflag = false;
		}

		// checking the absolute diff b/w start and current time
		secs = difftime( time(0), start);
		if (runtime != secs){
			count ++;
			// start spawning after 5 seconds
			if (count == 5){
				int rnd = rand() % 3 + 1;
				if (rnd == 1){
					spawnBirds();
				}
				else if (rnd == 2){
					spawnPlanes();
				}
				else{
					spawnBirds();
					spawnPlanes();
				}
				count = 0;
			}
		}
		runtime = runtime + (secs-runtime) + temp;
		temp = 0; 
	}
}


// drawing all the objects by calling relevant class functions
void Game::drawAllObjects()
{
	for (Bird *i : birds){
		i->childDraw(gRenderer);
	}

	for (Flare *i : flares){
		i->childDraw(gRenderer);
	}

	for (Blast *i : blasts){	
		i->childDraw(gRenderer);
	}

	for (Plane *i : planes){
		i->childDraw(gRenderer);
	}
}

// func that write texts and links with Text class
void Game::writeText(std::string content, int fontSize, int xCo, int yCo, SDL_Color color) {
	Text text(gRenderer, "defaultFont.ttf", fontSize, content, color);
	text.display(xCo,yCo, gRenderer);
}

// this func is removing all game objects
void Game::remove_all(){
	// removing birds
	for(auto&& i : birds) {
		delete i;
	}
	// removing flares
	for(auto&& i : flares) {
		delete i;
	}
	// removing blasts
	for(auto&& i : blasts) {
		delete i;
	}
	// removing planes
	for(auto&& i : planes) {
		delete i;
	}

	birds.clear();
	flares.clear();
	blasts.clear();
	planes.clear();
}

void Game::run()
{
	SDL_RenderClear(gRenderer);
	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;
	int pauseCounter = 0;
	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
		
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			// this condition is for shooting flares when a user clicks on the bottom half of the canvas
			if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && isPause == false && gameState == "running")
			{
				//this is a good location to add pigeon in linked list.
				int xMouse, yMouse;
				SDL_GetMouseState(&xMouse, &yMouse);

				// activates when user clicks below 400 y axis
				if (yMouse > 400)
				{
					//launch flare in sky
					SDL_Rect currentPosition = {xMouse, yMouse, 15, 15};
					planeCrashSound.playSoundEffect();
					flares.push_back(new Flare(assets, currentPosition));
					FlareSound.playSoundEffect();
				}
			}

			// this condition is true when user pressed the key P and the game stopped
			else if (e.type == SDL_KEYDOWN && gameState == "running") {
				if (e.key.keysym.sym == SDLK_p && isPause == false){
					// showing menu and text 
					gamePausedMenu.show(gRenderer);
					writeText("Game Paused", 24, 340, 375, {5, 236, 252});
					writeText("Press 'P' key to Resume", 16, 330, 425, {5, 236, 252});
					writeText("Press 'H' key for Home", 16, 330, 450, {5, 236, 252});
					writeText("Press 'Q' key to Quit", 16, 330, 475, {5, 236, 252});
					// playing sound effects
					spawnPlaneSound.playSoundEffect();
					SDL_RenderPresent(gRenderer);
					// changing the bool values to true
					isPause = true;
					pauseflag = true;
				}
				// if a user press "P" key again, the game resumes
				else if (e.key.keysym.sym == SDLK_p && isPause == true) {
					spawnPlaneSound.playSoundEffect();
					isPause = false;
				}
				// if the user press the Q key, game quits
				else if (e.key.keysym.sym == SDLK_q && isPause == true) {
					quit = true;
				}
				// if a user presses H, game will return to home menu
				else if (e.key.keysym.sym == SDLK_h && isPause == true){
					gameState = "notRunning";
					isPause = false;
					pauseflag = true;
					runtime = NULL;
					score = 0;
					remove_all();
				}
 			}
			
			// this condition is true when we are on Main menu and if a user clicks on screen. 
			if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && isPause == false && gameState == "notRunning")
			{
				int xMouse, yMouse;
				SDL_GetMouseState(&xMouse, &yMouse);
				// this checks if user clicked on start game button
				if (xMouse > 590 && xMouse < 700 && yMouse > 280 && yMouse <320) {
					gameState = "running";
				}
				// this checks if user clicked on quit game button
				else if (xMouse > 590 && xMouse < 700 && yMouse > 445 && yMouse < 480) {
					quit = true;
				}
			}
		}

		
		SDL_RenderClear(gRenderer);						 //removes everything from renderer
		SDL_RenderCopy(gRenderer, gTexture, NULL, NULL); //Draws background to renderer
		// SDL_RenderCopy(gRenderer, text, NULL, &textRect);

		
		// playing background music
		bgSound.playMusic();

		// this condition is true when the timer for the game stops and a menu popups with highscores and other details
		if (120-runtime == 0){
			gamePausedMenu.show(gRenderer);
			writeText("Game End", 24, 340, 375, {5, 240, 252});
			writeText("Youe Total Score is: " + to_string(score), 16, 330, 410, {5, 236, 252});
			writeText("Press 'P' key to Resume", 16, 330, 450, {5, 236, 252});
			writeText("Press 'H' key for Home", 16, 330, 475, {5, 236, 252});
			writeText("Press 'Q' key to Quit", 16, 330, 500, {5, 236, 252});
			Cheer.playSoundEffect();
			SDL_RenderPresent(gRenderer);
			isPause = true;
			pauseflag = true;
			runtime = NULL;
			score = 0;

			// deleting all objects
			remove_all();
		}

		// this condition is true when the game is in running state
		if (isPause == false && gameState == "running") {
			// this is the score board on the top right corner
			writeText("Score", 30, 700, 10, {255,255,255,0});
			writeText(to_string(score), 20, 720, 45, {255,255,255,0});
			// this is the timer on the top right corner
			writeText("Timer", 30, 10, 10, {255,255,255,0});
			writeText(to_string(120 - runtime), 20, 30, 45, {255,255,255,0});

			// animating all the objects including flares, planes, birds and etc.
			updateFlare();
			updatePlanes();
			updateBlasts();
			updateBirds();
			drawAllObjects();
			
			// checking for collisions
			Check4Collision();
			// rendering the changes
			SDL_RenderPresent(gRenderer);

		// this condition is true when a user paused the game
		} else if (gameState == "notRunning" && isPause == false) {
			startMenu.show(gRenderer);
			SDL_RenderPresent(gRenderer);
		}
			  //draws all objects
		 //displays the updated renderer
		
		// this is the timer running
		timer();
		SDL_Delay(100);				  //causes sdl engine to delay for specified miliseconds
	}
}
