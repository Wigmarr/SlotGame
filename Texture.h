#ifndef TEXTURE_H
#define TEXTURE_H
#include "defines.h"
#include <string>
#include <iostream>
class Texture
{
	SDL_Texture* _texture;
	int _width;
	int _height;
	TTF_Font* _font;
public:
	Texture();
	~Texture(); //free texture on destruction
	bool loadFromFile(std::string path, SDL_Renderer* renderer);//
	bool loadFromText(std::string text, SDL_Color text_color, SDL_Renderer* renderer); //create Texture from text
	void render(SDL_Renderer* renderer,int x, int y);
	void setColor(Uint8 red, Uint8 green, Uint8 blue); //change color of texture
	int getWidth();
	int getHeight();
private:
	void free();//free SDL texture
};
#endif // !TEXTURE_H


