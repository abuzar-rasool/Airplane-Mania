#include "game.hpp"
#include "unit.hpp"
#include <iostream>

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
		gWindow = SDL_CreateWindow("HU Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

void Game::updateEggs()


{
	//check the collision of eggs and nests here
	//If an egg is dropped in a nest, produce a new baby pigeon
	//if the egg is dropped on floor, remove it from list.

	//The implemenation is done by iterating over eggs and nests in a
	// nested fashion if, if the absoulte position if egg an the nest <=20
	//then hatch the egg
	for (Unit *i : eggs)
	{
		Egg *e = (Egg *)i;
		if (e->dropped())
		{
			delete i;
			eggs.remove(i);
		}
		else
		{
			for (Unit *j : nests)
			{
				Nest *n = (Nest *)i;
				if (abs(i->getMover().x - j->getMover().x) <= 20 && abs(i->getMover().y - j->getMover().y) <= 20)
				{
					SDL_Rect currentPosition = {i->getMover().x + 12, i->getMover().y + 12, 12, 16};
					pigeons.push_back(new Pigeon(assets, currentPosition, true));
					delete i;
					eggs.remove(i);
				}
			}
		}
	}
}
void Game::updatePigeons()
{
	//Iterate over the link list of pigeons and generated eggs with 2% probability
	//Remove such pigeons from the list which have laid 4 eggs.
	for (Unit *i : pigeons)
	{
		Pigeon *p = (Pigeon *)i;
		if (p->isAlive())
		{
			//If pigeon is alive then call layegg that will layEgg at 2% probablity.
			SDL_Rect tempmover = {p->getMover().x, p->getMover().y, 12, 16};
			if (p->layEgg())
			{
				eggs.push_back(new Egg(assets, tempmover));
			}
		}
		else
		{
			//If pigeon is not alive delete it from the memory and the array
			delete p;
			pigeons.remove(p);
		}
	}
}


void Game::updateFlare(){
	for(Flare *i: flares){
		if(!i->isAlive()){
			delete i;
			flares.remove(i);
		}
		
	}
}


void Game::spawnBirds()
{
	for (int i = 0; i < no_of_birds; i++)
	{
		//Randomly spawn Bird1, Bird2 and Bir
		int rnd = rand() % 3 + 1;
		if (rnd == 1)
		{
			birds.push_back(new Bird1(assets));
		}
		else if(rnd==2)
		{
			birds.push_back(new Bird2(assets));
		}else{
			birds.push_back(new Bird3(assets));
		}
	}
}



void Game::Check4Collision(){
	for (Unit *i : birds){
		for (Plane *j : planes)
		{
			if (abs(i->getMover().x - j->getMover().x) <= 20 && abs(i->getMover().y - j->getMover().y) <= 20)
			{
				j->crashed();
				birds.remove(i);
				cout << "Thuk Gaya Jhaaz"<<endl;
			}
		}
		for (Flare *k : flares)
		{
			if (abs(i->getMover().x - k->getMover().x) <= 50 && abs(i->getMover().y - k->getMover().y) <= 50)
			{

				birds.remove(i);
				k->collisionhappen();
				cout << "Bird Margai"<<endl;
			}
			if (k->getMover().y<0){
				flares.remove(k);
			}
		}
	}

}

// void Game::Check4Collision(){
// 	SDL_Rect temp, temp1;
// 	bool baby = 0;
// 	for(auto parinda : birds){
// 		temp = parinda->getMover();

// 		for(auto jahaaz: planes){
// 			temp1 = jahaaz->getMover();

// 			if(temp1.x < temp.x && temp.x < temp1.x + temp1.w  && temp.y > temp1.y){
// 				jahaaz->crashed();
// 				cout << "Thuuk gaya" <<endl;
// 				break;
// 			}
// 		}
// 	}
// }



void Game::spawnPlanes()
{
	for (int i = 0; i < no_of_planes; i++)
	{
		planes.push_back(new Plane_flying(assets));
	}
}

void Game::drawAllObjects()
{
	Check4Collision();
	for (Unit *i : birds)
	{
		i->childDraw(gRenderer);
	}
	for (Unit *i : flares)
	{
		i->childDraw(gRenderer);
	}
	for (Unit *i : planes)
	{
		i->childDraw(gRenderer);
	}
}

void Game::run()
{

	SDL_RenderClear(gRenderer);
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;
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

			if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				//this is a good location to add pigeon in linked list.
				int xMouse, yMouse;
				SDL_GetMouseState(&xMouse, &yMouse);

				if (yMouse < 400 && xMouse > 400)
				{
					// Create a new Pigeon
					//SDL_Rect currentPosition = {xMouse, yMouse, 50, 50};
					// pigeons.push_back(new Pigeon(assets, currentPosition, false));
					spawnBirds();
					no_of_total_birds+=1;
					//Check4Collision();
				}
				else if(yMouse < 400){
					spawnPlanes();
				}
				else
				{
					//launch flare in sky
					SDL_Rect currentPosition = {xMouse, yMouse, 15, 15};
					flares.push_back(new Flare(assets, currentPosition));
				}
			}
		}

		SDL_RenderClear(gRenderer);						 //removes everything from renderer
		SDL_RenderCopy(gRenderer, gTexture, NULL, NULL); //Draws background to renderer

		updateFlare();
		drawAllObjects();			  //draws all objects
		SDL_RenderPresent(gRenderer); //displays the updated renderer
		SDL_Delay(200);				  //causes sdl engine to delay for specified miliseconds
	}
}
