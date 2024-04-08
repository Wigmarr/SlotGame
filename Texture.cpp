#include "Texture.h"

Texture::Texture()
{
	_width = 0;
	_height = 0;
	_texture = NULL;
	_font = NULL;
}

Texture::~Texture()
{
	
	//std::cout << "~Texture" << std::endl;
	free();
}

bool Texture::loadFromText(std::string text, SDL_Color text_color, SDL_Renderer* renderer)
{
    //Get rid of preexisting texture
    free();
	//hardcoded font for now
	_font = TTF_OpenFont("./Resources/Fonts/lazy.ttf", 60);
	if (_font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}
    //Render text surface
    SDL_Surface* text_surface = TTF_RenderText_Solid(_font, text.c_str(), text_color);
    if (text_surface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        _texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        if (_texture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            _width = text_surface->w;
            _height = text_surface->h;
        }

        SDL_FreeSurface(text_surface);
    }

    return _texture != NULL;
}

bool Texture::loadFromFile(std::string path, SDL_Renderer* renderer)
{
	free();
	_texture = NULL;
	SDL_Surface* loaded_surface = IMG_Load(path.c_str());
	if (loaded_surface == NULL) {
		std::cout << "Couldn't load image " << path << ". SDL_image error: " << IMG_GetError() << std::endl;
		return false;
	}
	_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
	_width = loaded_surface->w;
	_height = loaded_surface->h;
	SDL_FreeSurface(loaded_surface);
	return true;
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(_texture, red, green, blue);
}


void Texture::render(SDL_Renderer* renderer, int x, int y)
{
	SDL_Rect render_rect = { x,y,_width, _height };
	SDL_Rect source_rect = { 0, 0, _width, _height };
	SDL_RenderCopy(renderer, _texture, &source_rect, &render_rect);
}

int Texture::getWidth()
{
	return _width;
}

int Texture::getHeight()
{
	return _height;
}

void Texture::free()
{
	if (_texture != NULL) {
		SDL_DestroyTexture(_texture);
	}
	if (_font != NULL) {
		TTF_CloseFont(_font);

	}
}
