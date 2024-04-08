#include "Game.h"
int main(int argc, char* args[]) {
	Game game(1920, 1080);//init SDL with set screen resolution
	game.start(); //start main loop
	return 0;
}