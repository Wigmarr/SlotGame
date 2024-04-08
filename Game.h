#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include "SlotMachine.h"
#include "Texture.h"
#include "defines.h"
#include "Button.h"
class Game
{
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	const int _window_width;
	const int _window_height;
	bool _is_running;

	std::vector<std::shared_ptr<Texture>> _textures; //textures of reels content
	std::unique_ptr<SlotMachine> _slot_machine; 
	std::unique_ptr<Button> _button; //button to start spinning
public:
	Game(int, int);
	void start();
	~Game();
private:
	void loadTextures(); //load textures for reels content
	void close();
	void init(); //init SDL libs
	void initSlotMachine(); 
	void initUI();
};
#endif


