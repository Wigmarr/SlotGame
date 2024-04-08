#include "Reel.h"

Reel::Reel(Uint32 spin_time, Uint32 wait_time, int pos_x, int pos_y, const std::vector<std::shared_ptr<Texture>>& textures, std::shared_ptr<Texture> reel_texture)
	: _spin_timer(spin_time), _wait_timer(wait_time)
{
	srand(time(NULL));
	_reel_texture = reel_texture;
	_reel_pos_x = pos_x;
	_reel_pos_y = pos_y;
	_is_spinning = false;
	_reel_content = textures;
	_middle_value = rand() % _reel_content.size();
}

Reel::~Reel()
{
	//std::cout << "~Reel" << std::endl;
}

void Reel::startSpin()
{
	_is_spinning = true;
	_spin_timer.start();
	_wait_timer.start();
}

void Reel::stopSpin()
{
	_is_spinning = false;
	_spin_timer.stop();
	_wait_timer.stop();
}

bool Reel::isSpinning()
{
	return _is_spinning;
}

void Reel::render(SDL_Renderer* renderer)
{
	//render reel
	_reel_texture->render(renderer, _reel_pos_x, _reel_pos_y);
	// calc prev and next value;
	int prev_value = _middle_value - 1;
	int next_value = (_middle_value + 1) % _reel_content.size();

	if (prev_value < 0) { 
		prev_value = _reel_content.size() - 1;
	}
	int center_x = _reel_pos_x + _reel_texture->getWidth() / 2;
	int margin_y = 10;
	
	int next_x = center_x - _reel_content[next_value]->getWidth() / 2;
	int prev_x = center_x - _reel_content[prev_value]->getWidth() / 2;
	int middle_x = center_x - _reel_content[_middle_value]->getWidth() / 2;

	int next_y = _reel_pos_y + _reel_texture->getHeight() / 3 - _reel_content[next_value]->getHeight();
	int prev_y = _reel_pos_y + _reel_texture->getHeight() - _reel_content[prev_value]->getHeight()  - margin_y;
	int middle_y = _reel_pos_y + _reel_texture->getHeight() / 2 - _reel_content[next_value]->getHeight() / 2;
	
	//render 3 values
	_reel_content[prev_value]->render(renderer, prev_x, prev_y);
	_reel_content[_middle_value]->render(renderer, middle_x, middle_y);
	_reel_content[next_value]->render(renderer, next_x , next_y);
	
	//render next values if timer timeout
	if (_is_spinning) {
		if (_spin_timer.isTimedOut()) {
			stopSpin();
		}
		else {
			if (_wait_timer.isTimedOut()) {
				_wait_timer.start();
				_middle_value = (_middle_value + 1) % _reel_content.size();
			}
		}
	}
}
