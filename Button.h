#ifndef BUTTON_H
#define BUTTON_H
#include <memory>
#include "Texture.h"
#include "defines.h"
#include "Timer.h"
class Button
{
	bool _is_pressed;
	std::shared_ptr<Texture> _button_texture;
	std::shared_ptr<Texture> _button_text;
	Timer _color_change_timer;
	int _pos_x;
	int _pos_y;
public:
	Button(std::shared_ptr<Texture> texture, std::shared_ptr<Texture> text, int x, int y);
	~Button();
	bool getPressed();
	void handleEvent(const SDL_Event& event);
	void unpress();
	void press();
	void render(SDL_Renderer* renderer);
};

#endif // !BUTTON_H

