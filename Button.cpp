#include "Button.h"

Button::Button(std::shared_ptr<Texture> texture, std::shared_ptr<Texture> text, int x, int y) : _color_change_timer(200) {
	_button_texture = texture;
	_button_text = text;
	_color_change_timer.start();
	_pos_x = x;
	_pos_y = y;
	srand(time(NULL));

}

Button::~Button()
{
	//std::cout << "~Button" << std::endl;
}

bool Button::getPressed()
{
	return _is_pressed;
}

void Button::handleEvent(const SDL_Event& event)
{
	//handle mouse click;
	if (event.type == SDL_MOUSEBUTTONUP) {
		int mouse_x;
		int mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);

		bool inside = true;
		if (mouse_x < _pos_x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (mouse_x > _pos_x + _button_texture->getWidth())
		{
			inside = false;
		}
		//Mouse above the button
		else if (mouse_y < _pos_y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (mouse_y > _pos_y + _button_texture->getHeight())
		{
			inside = false;
		}
		if (inside) {
			press();
		}
	}
}

void Button::unpress()
{
	_is_pressed = false;
}

void Button::render(SDL_Renderer* renderer)
{
	if (_is_pressed) {
		_button_texture->setColor(0xff, 0xff, 0);
	} else {
		if (_color_change_timer.isTimedOut()) {
			_color_change_timer.start();
			_button_texture->setColor(rand() % (0xff - 100) + 100, rand() % (0xff - 100) + 100, rand() % (0xff - 100) + 100);
		}
	}
	_button_texture->render(renderer, _pos_x, _pos_y);
	_button_text->render(renderer, _pos_x, _pos_y);
}

void Button::press()
{
	_is_pressed = true;
}


