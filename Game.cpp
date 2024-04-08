#include "Game.h"
Game::Game(int width, int height) : _window_width(width), _window_height(height)
{
	init();

	initSlotMachine();
	initUI();
	
	
}

void Game::init()
{
	//init SLD
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Error! Couldn't Init SDL Video. SDL_ERROR = " << SDL_GetError() << std::endl;
		exit(1);
	}
	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
	}
	//init window
	_window = SDL_CreateWindow("Slot Machine Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _window_width, _window_height, SDL_WINDOW_SHOWN);
	if (_window == NULL) {
		std::cerr << "Error! Couldn't create window. SDL_ERROR = " << SDL_GetError() << std::endl;
		exit(1);
	}
	//init renderer
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == NULL) {
		std::cerr << "Error! Couldn't create renderer. SDL_ERROR = " << SDL_GetError() << std::endl;
		exit(1);
	}
	SDL_SetRenderDrawColor(_renderer, 0xff, 0xff, 0xff, 0xff);
	//init SDL_image
	int img_flags = IMG_INIT_PNG;
	if ((IMG_Init(img_flags) & img_flags) == 0) {
		std::cerr << "Error! Couldn't init SDL_image. SDL_image error = " << IMG_GetError() << std::endl;
		exit(1);
	}
	//init SDL_ttf
	if (TTF_Init() == -1) {
		std::cerr << "Error! Couldn't init SDL_ttf. SDL_ttf error = " << TTF_GetError() << std::endl;
		exit(1);
	}
	
	

}

void Game::start()
{


	_is_running = true;
	//fps calculation init
	std::stringstream fps_string;
	Texture fps_texture;
	Timer fps_timer(0); //don't care about time out, we need only time
	int counted_frames = 0;
	fps_timer.start();
	while (_is_running) {
		//update button if stopped spinning
		if (!_slot_machine->isSpinning()) {
			_button->unpress();
		}

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			//proccess events
			if (event.type == SDL_QUIT) {
				_is_running = false;
			}
			_button->handleEvent(event);
			_slot_machine->handleEvent(event); //doesn't do anything for now
		}

		
		//react to proccessed events;
		if (_button->getPressed() && !_slot_machine->isSpinning()) {
			_slot_machine->startSpinning();
		}
		//Clear screen
		SDL_SetRenderDrawColor(_renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(_renderer);
		//calculating fps

		float avg_fps = counted_frames / (fps_timer.getTicks() / 1000.f); 
		
		//render slotmachine
		_slot_machine->render(_renderer);
		//render spin button
		_button->render(_renderer);

		//render fps as text in lower right corner
		fps_string.str("");
		fps_string << avg_fps;
		fps_texture.loadFromText(fps_string.str().c_str(), { 0,0,0 }, _renderer);
		fps_texture.render(_renderer, _window_width - fps_texture.getWidth(), _window_height - fps_texture.getHeight());
		//render new frame
		SDL_RenderPresent(_renderer);
		counted_frames++;
	}
	close();
}

Game::~Game()
{
	//std::cout << "~Game" << std::endl;
	close();
}

void Game::close()
{

	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	_renderer = NULL;
	_window = NULL;

	IMG_Quit();
	SDL_Quit();
}

void Game::loadTextures()
{
	std::shared_ptr<Texture> bell_texture = std::make_shared<Texture>();
	bell_texture->loadFromFile("./Resources/Sprites/bell.png", _renderer);
	std::shared_ptr<Texture> cherry_texture = std::make_shared<Texture>();
	cherry_texture->loadFromFile("./Resources/Sprites/cherries.png", _renderer);
	std::shared_ptr<Texture> clover_texture = std::make_shared<Texture>();
	clover_texture->loadFromFile("./Resources/Sprites/clover.png", _renderer);
	std::shared_ptr<Texture> heart_texture = std::make_shared<Texture>();
	heart_texture->loadFromFile("./Resources/Sprites/heart.png", _renderer);
	std::shared_ptr<Texture> horseshoe_texture = std::make_shared<Texture>();
	horseshoe_texture->loadFromFile("./Resources/Sprites/horseshoe.png", _renderer);
	std::shared_ptr<Texture> Lucky7_texture = std::make_shared<Texture>();
	Lucky7_texture->loadFromFile("./Resources/Sprites/Lucky7.png", _renderer);
	std::shared_ptr<Texture> lemon_texture = std::make_shared<Texture>();
	lemon_texture->loadFromFile("./Resources/Sprites/lemon.png", _renderer);
	std::shared_ptr<Texture> melon_texture = std::make_shared<Texture>();
	melon_texture->loadFromFile("./Resources/Sprites/melon.png", _renderer);

	if (bell_texture != NULL) {
		_textures.push_back(bell_texture);
	}
	if (cherry_texture != NULL) {
		_textures.push_back(cherry_texture);
	}
	if (clover_texture != NULL) {
		_textures.push_back(clover_texture);
	}
	if (heart_texture != NULL) {
		_textures.push_back(heart_texture);
	}
	if (horseshoe_texture != NULL) {
		_textures.push_back(horseshoe_texture);
	}
	if (Lucky7_texture != NULL) {
		_textures.push_back(Lucky7_texture);
	}
	if (lemon_texture != NULL) {
		_textures.push_back(lemon_texture);
	} 
	if (melon_texture != NULL) {
		_textures.push_back(melon_texture);
	}
}

void Game::initSlotMachine()
{
	loadTextures();

	std::shared_ptr<Texture> slot_texture = std::make_shared<Texture>();
	slot_texture->loadFromFile("./Resources/Sprites/slotMachine.png", _renderer);

	std::shared_ptr<Texture> reel_texture = std::make_shared<Texture>();
	reel_texture->loadFromFile("./Resources/Sprites/reel.png", _renderer);
	//center of a screen
	_slot_machine = std::make_unique<SlotMachine>(_textures, _window_width / 2 - slot_texture->getWidth() / 2, _window_height / 2 - slot_texture->getHeight() / 2, slot_texture, reel_texture);
}

void Game::initUI()
{
	//button sprite
	std::shared_ptr<Texture> button_texture = std::make_shared<Texture>();
	button_texture->loadFromFile("./Resources/Sprites/button.png", _renderer);
	//button text
	std::shared_ptr<Texture> button_text = std::make_shared<Texture>();
	button_text->loadFromText("Spin", {0,0,0}, _renderer);
	//center above slotmachine
	int button_x = _slot_machine->getX() + _slot_machine->getWidth() / 2 - button_texture->getWidth() / 2;
	int button_y = _slot_machine->getY() - button_texture->getHeight() - 20;
	_button = std::make_unique<Button>(button_texture, button_text, button_x, button_y);
}
