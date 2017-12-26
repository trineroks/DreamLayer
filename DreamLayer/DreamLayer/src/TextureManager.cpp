#include "TextureManager.h"
#include "SDL_image.h"
#include "Game.h"

SDL_Texture* TextureManager::loadTexture(const char* file) {

	SDL_Surface* temp = IMG_Load(file);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, temp);
	SDL_FreeSurface(temp);

	return texture;
}

void TextureManager::draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}

void TextureManager::draw(TextureRegion* textRegion, int x, int y) {
	SDL_Rect dest = { x, y, textRegion->getRect().w, textRegion->getRect().h };
	SDL_RenderCopy(Game::renderer, textRegion->getTexture(), &textRegion->getRect(), &dest);
}

void TextureManager::draw(TextureRegion* textRegion, int x, int y, double degrees, int rotatex, int rotatey) {
	SDL_Rect dest = { x, y, textRegion->getRect().w, textRegion->getRect().h };
	SDL_Point point = { rotatex, rotatey };
	SDL_RenderCopyEx(Game::renderer, textRegion->getTexture(), &textRegion->getRect(), &dest, degrees, &point, SDL_FLIP_NONE);
}

void TextureManager::drawResized(TextureRegion* textRegion, int x, int y, int w, int h) {
	SDL_Rect dest = { x, y, w, h };
	SDL_RenderCopy(Game::renderer, textRegion->getTexture(), &textRegion->getRect(), &dest);
}

void TextureManager::drawResized(TextureRegion* textRegion, int x, int y, int w, int h, double degrees, int rotatex, int rotatey) {
	SDL_Rect dest = { x, y, w, h };
	SDL_Point point = { rotatex, rotatey };
	SDL_RenderCopyEx(Game::renderer, textRegion->getTexture(), &textRegion->getRect(), &dest, degrees, &point, SDL_FLIP_NONE);
}

void TextureManager::drawSurface(SDL_Surface* surface, int x, int y) {
	SDL_Rect dest = { x, y, 0, 0 };
}