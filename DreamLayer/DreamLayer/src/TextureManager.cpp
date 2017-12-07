#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(const char* file) {

	SDL_Surface* temp = IMG_Load(file);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, temp);
	SDL_FreeSurface(temp);

	return texture;
}

void TextureManager::draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}

void TextureManager::drawSurface(SDL_Surface* surface, int x, int y) {
	SDL_Rect dest = { x, y, 0, 0 };
}