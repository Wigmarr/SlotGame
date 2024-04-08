#include "SlotMachine.h"


SlotMachine::SlotMachine()
{
	_pos_x = 0;
	_pos_y = 0;
}

SlotMachine::SlotMachine(const std::vector<std::shared_ptr<Texture>>& reel_content_textures, int pos_x, int pos_y, std::shared_ptr<Texture> slot_texture, std::shared_ptr<Texture> reel_texture)
{
	_pos_x = pos_x;
	_pos_y = pos_y;
	_texture = slot_texture;

	for (int i = 0; i < _reels_number; ++i) {
		Uint32 spin_time = _min_spin_time + i * 200;
		Uint32 wait_time = 50 + i * 15; // wait time between next frame in spin animation;
		_reels.push_back(Reel(spin_time, wait_time, _pos_x + i*slot_texture->getWidth()/_reels_number, _pos_y, reel_content_textures, reel_texture));
	}


}

SlotMachine::~SlotMachine()
{
	
	//std::cout << "~SlotMachine" << std::endl;
}

void SlotMachine::handleEvent(const SDL_Event& event)
{

}

void SlotMachine::render(SDL_Renderer* renderer)
{
	_texture->render(renderer, _pos_x, _pos_y);
	for (int i = 0; i < _reels.size(); ++i) {
		_reels[i].render(renderer);
	}
}

void SlotMachine::startSpinning()
{
	for (int i = 0; i < _reels.size(); ++i) {
		_reels[i].startSpin();
	}
}

int SlotMachine::getX()
{
	return _pos_x;
}

int SlotMachine::getY()
{
	return _pos_y;
}

int SlotMachine::getWidth()
{
	return _texture->getWidth();
}

int SlotMachine::getHeight()
{
	return _texture->getHeight();
}

bool SlotMachine::isSpinning()
{
	bool result = false;
	for (int i = 0; i < _reels.size(); ++i) {
		result = result || _reels[i].isSpinning();
	}
	return result;
}
