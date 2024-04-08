#ifndef REEL_H
#include <vector>
#include "Texture.h"
#include "Timer.h"
class Reel
{
	std::vector<std::shared_ptr<Texture>> _reel_content;
	std::shared_ptr<Texture> _reel_texture;
	int _middle_value;
	bool _is_spinning;
	Timer _spin_timer;
	Timer _wait_timer;
	int _reel_pos_x;
	int _reel_pos_y;
public:
	Reel(Uint32 spin_time_sec, Uint32 wait_time_sec, int reel_pos_x, int reel_pos_y, const std::vector<std::shared_ptr<Texture>>&, std::shared_ptr<Texture> reel_texture);
	~Reel();
	void startSpin();
	void stopSpin();
	bool isSpinning();
	void render(SDL_Renderer* renderer);

};

#endif // !REEL_H

