#include "game.hpp"
#include "unit.hpp"
#include <iostream>
#include <time.h>
#include "text.cpp"
#include "sound.cpp"

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

			startMenu.loadImage(gRenderer,"mainmenu.jpeg");
			startMenu.customize(gRenderer,0, 0, 600, 800);

			gamePausedMenu.loadImage(gRenderer, "bar2.png");
			gamePausedMenu.customize(gRenderer,300,350, 250, 220);

			bgSound.LoadMusic("background.wav");
			spawnBirdSound.LoadSoundEffect("Plane_Spawn.wav");
			spawnPlaneSound.LoadSoundEffect("Bird_Spawn1.wav");
			planeCrashSound.LoadSoundEffect("Plane_Blast.wav");
			birdDiedSound.LoadSoundEffect("BIrd_Scream2.wav");
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

// void Game::updateEggs()
// {
// 	//check the collision of eggs and nests here
// 	//If an egg is dropped in a nest, produce a new baby pigeon
// 	//if the egg is dropped on floor, remove it from list.

// 	//The implemenation is done by iterating over eggs and nests in a
// 	// nested fashion if, if the absoulte position if egg an the nest <=20
// 	//then hatch the egg
// 	for (Unit *i : eggs)
// 	{
// 		Egg *e = (Egg *)i;
// 		if (e->dropped())
// 		{
// 			delete i;
// 			eggs.remove(i);
// 		}
// 		else
// 		{
// 			for (Unit *j : nests)
// 			{
// 				Nest *n = (Nest *)i;
// 				if (abs(i->getMover().x - j->getMover().x) <= 20 && abs(i->getMover().y - j->getMover().y) <= 20)
// 				{
// 					SDL_Rect currentPosition = {i->getMover().x + 12, i->getMover().y + 12, 12, 16};
// 					pigeons.push_back(new Pigeon(assets, currentPosition, true));
// 					delete i;
// 					eggs.remove(i);
// 				}
// 			}
// 		}
// 	}
// }

// void Game::updatePigeons()
// {
// 	//Iterate over the link list of pigeons and generated eggs with 2% probability
// 	//Remove such pigeons from the list which have laid 4 eggs.
// 	for (Unit *i : pigeons)
// 	{
// 		Pigeon *p = (Pigeon *)i;
// 		if (p->isAlive())
// 		{
// 			//If pigeon is alive then call layegg that will layEgg at 2% probablity.
// 			SDL_Rect tempmover = {p->getMover().x, p->getMover().y, 12, 16};
// 			if (p->layEgg())
// 			{
// 				eggs.push_back(new Egg(assets, tempmover));
// 			}
// 		}
// 		else
// 		{
// 			//If pigeon is not alive delete it from the memory and the array
// 			delete p;
// 			pigeons.remove(p);
// 		}
// 	}
// }

void Game::updateFlare(){
	for(Flare *i: flares){
		if(!i->isAlive()){
			delete i;
			flares.remove(i);
		}
		
	}
}

void Game::updateBlasts(){
	for(Blast *i: blasts){
		if(!i->isAlive()){
			delete i;
			blasts.remove(i);
		}
		
	}
}

void Game::updateBirds(){
	if (isPause == false) {
		for(Bird *i: birds){
			if(!i->isAlive()){
				delete i;
				birds.remove(i);
				set_score(-10); //Bird Died
			}
		}
	}
}

void Game::updatePlanes(){
	for(Plane *i: planes){
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
		else if (i->getMover().x > 800){
			set_score(50); //Safe Passage Successful
			// sound for successful passage
			planes.remove(i);
		}	
	}
}

void Game::spawnBirds(){
	if (isPause == false) {
		for (int i = 0; i < no_of_birds; i++)
	{
		//Randomly spawn Bird1, Bird2 and Bir
		int rnd = rand() % 3 + 1;
		if (rnd == 1)
		{
			birds.push_back(new Bird1(assets));
			spawnPlaneSound.playSoundEffect();
		}
		else if(rnd==2)
		{
			birds.push_back(new Bird2(assets));
			spawnPlaneSound.playSoundEffect();
		}else{
			birds.push_back(new Bird3(assets));
			spawnPlaneSound.playSoundEffect();
		}
		}
	}
}

void Game::set_score(int s){
	score = score+s;
}

void Game::Check4Collision(){
	for (Bird *i : birds){
		for (Plane *j : planes)
		{
			if (abs(i->getMover().x - j->getMover().x) <= j->getMover().w && abs(i->getMover().y - j->getMover().y) <= j->getMover().h && j->stillFlying())
			{
				j->crashed();
				i->crashed();
				planeCrashSound.playSoundEffect();
				cout << "Thuk Gaya Jhaaz"<<endl;
			}
		}
		for (Flare *k : flares)
		{
			if (abs(i->getMover().x - k->getMover().x) <= i->getMover().w && abs(i->getMover().y - k->getMover().y) <= i->getMover().h && i->stillFlying())
			{

				i->crashed();
				k->collisionhappen();
				birdDiedSound.playSoundEffect();
				cout << "Bird Margai"<<endl;
			}else if(abs(i->getMover().x - k->getMover().x) <= i->getMover().w+100 && abs(i->getMover().y - k->getMover().y) <= i->getMover().h+100 && i->stillFlying() && k->collide && !i->scare){
				i->scared();
				k->collisionhappen();
			}
			if (k->getMover().y<0){
				flares.remove(k);
			}
		}
	}
}

void Game::spawnPlanes()
{
	for (int i = 0; i < no_of_planes; i++)
	{
		planes.push_back(new Plane(assets));
		spawnBirdSound.playSoundEffect();
	}
}

void Game::timer(){
	if (gameState == "running" && isPause == false){
		static time_t start = time(0);
		static time_t secs = 0, temp;
		static int count = 0;

		if (pauseflag == true){
			start = time(0)-runtime;
			pauseflag = false;
		}

		secs = difftime( time(0), start);
		if (runtime != secs){
			// cout << "temp: "<< temp <<endl;
			// cout << "secs: "<< secs <<endl;
			count ++;
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

void Game::writeText(std::string content, int fontSize, int xCo, int yCo, SDL_Color color) {
	Text text(gRenderer, "defaultFont.ttf", fontSize, content, color);
	text.display(xCo,yCo, gRenderer);
}

void Game::remove_all(){
	for(auto&& i : birds) {
		delete i;
	}
	for(auto&& i : flares) {
		delete i;
	}
	for(auto&& i : blasts) {
		delete i;
	}
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

			if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && isPause == false && gameState == "running")
			{
				//this is a good location to add pigeon in linked list.
				int xMouse, yMouse;
				SDL_GetMouseState(&xMouse, &yMouse);

				if (yMouse > 400)
				{
					//launch flare in sky
					SDL_Rect currentPosition = {xMouse, yMouse, 15, 15};
					planeCrashSound.playSoundEffect();
					flares.push_back(new Flare(assets, currentPosition));
				}
			}
			else if (e.type == SDL_KEYDOWN && gameState == "running") {
				if (e.key.keysym.sym == SDLK_p && isPause == false){
					gamePausedMenu.show(gRenderer);
					writeText("Game Paused", 24, 340, 375, {5, 236, 252});
					writeText("Press 'P' key to Resume", 16, 330, 425, {5, 236, 252});
					writeText("Press 'H' key for Home", 16, 330, 450, {5, 236, 252});
					writeText("Press 'Q' key to Quit", 16, 330, 475, {5, 236, 252});
					spawnBirdSound.playSoundEffect();
					SDL_RenderPresent(gRenderer);
					isPause = true;
					pauseflag = true;
				}
				else if (e.key.keysym.sym == SDLK_p && isPause == true) {
					isPause = false;
				}
				else if (e.key.keysym.sym == SDLK_q && isPause == true) {
					quit = true;
				}
				else if (e.key.keysym.sym == SDLK_h && isPause == true){
					gameState = "notRunning";
					isPause = false;
					pauseflag = true;
					runtime = NULL;
					score = 0;
					remove_all();
				}
 			}
			
			if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && isPause == false && gameState == "notRunning")
			{
				//this is a good location to add pigeon in linked list.
				int xMouse, yMouse;
				SDL_GetMouseState(&xMouse, &yMouse);
				if (xMouse > 590 && xMouse < 700 && yMouse > 280 && yMouse <320) {
					gameState = "running";
				} else if (xMouse > 590 && xMouse < 700 && yMouse > 325 && yMouse < 355) {
					gameState = "users";
				}
				else if (xMouse > 590 && xMouse < 700 && yMouse > 360 && yMouse < 400) {
					gameState = "options";
				}
				else if (xMouse > 590 && xMouse < 700 && yMouse > 410 && yMouse < 440) {
					gameState = "credits";
				} 
				 else if (xMouse > 590 && xMouse < 700 && yMouse > 445 && yMouse < 480) {
					quit = true;
				}
			}
		}

		
		SDL_RenderClear(gRenderer);						 //removes everything from renderer
		SDL_RenderCopy(gRenderer, gTexture, NULL, NULL); //Draws background to renderer
		// SDL_RenderCopy(gRenderer, text, NULL, &textRect);

		

		bgSound.playMusic();

		if (120-runtime == 0){
			gamePausedMenu.show(gRenderer);
			writeText("Game End", 24, 340, 375, {5, 240, 252});
			writeText("Youe Total Score is: " + to_string(score), 16, 330, 410, {5, 236, 252});
			writeText("Press 'P' key to Resume", 16, 330, 450, {5, 236, 252});
			writeText("Press 'H' key for Home", 16, 330, 475, {5, 236, 252});
			writeText("Press 'Q' key to Quit", 16, 330, 500, {5, 236, 252});
			spawnBirdSound.playSoundEffect();
			SDL_RenderPresent(gRenderer);
			isPause = true;
			pauseflag = true;
			runtime = NULL;
			score = 0;
			remove_all();
		}
		if (isPause == false && gameState == "running") {
			writeText("Score", 30, 700, 10, {255,255,255,0});
			writeText(to_string(score), 20, 720, 45, {255,255,255,0});
			writeText("Timer", 30, 10, 10, {255,255,255,0});
			writeText(to_string(120 - runtime), 20, 30, 45, {255,255,255,0});

			updateFlare();
			updatePlanes();
			updateBlasts();
			updateBirds();
			drawAllObjects();
			
			Check4Collision();
			SDL_RenderPresent(gRenderer);

		} else if (gameState == "notRunning" && isPause == false) {
			startMenu.show(gRenderer);
			SDL_RenderPresent(gRenderer);
		}
			  //draws all objects
		 //displays the updated renderer
		timer();
		SDL_Delay(100);				  //causes sdl engine to delay for specified miliseconds
	}
}
