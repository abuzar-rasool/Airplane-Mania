#include "game.hpp"

// main function
int main(int argc, char *argv[]){
    // creating game object
    Game game;
    srand(time(NULL));
    if( !game.init() ){
		printf( "Failed to initialize!\n" );
        return 0;
	}
		//Load media
    if( !game.loadMedia() ){
        printf( "Failed to load media!\n" );
        return 0;
    }

    // running game
    game.run();
    // closing game
    game.close();

    return 0;
}