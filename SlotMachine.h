#ifndef SLOT_MACHINE_H
#define SLOT_MACHINE_H
#include "defines.h"
#include "Reel.h"

class SlotMachine
{
	const int _reels_number = 5;
	Uint32 _min_spin_time = 4000;
	
	std::vector<Reel> _reels;
	std::shared_ptr<Texture> _texture;
	
	int _pos_x;
	int _pos_y;
public:
	
	SlotMachine();
	SlotMachine(const std::vector<std::shared_ptr<Texture>>& textures, int pos_x, int pos_y, std::shared_ptr<Texture> slot_texture, std::shared_ptr<Texture> reel_texture);
	~SlotMachine();

	void handleEvent(const SDL_Event& event);
	void render(SDL_Renderer* renderer);
	void startSpinning();
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	bool isSpinning();
};


#endif // !SLOT_MACHINE_H


