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

void TextureManager::draw(TextureRegion textRegion, int x, int y) {
	drawResized(textRegion, x, y, textRegion.getRect().w, textRegion.getRect().h, 0, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::draw(TextureRegion textRegion, int x, int y, double degrees, int rotatex, int rotatey) {
	drawResized(textRegion, x, y, textRegion.getRect().w, textRegion.getRect().h, degrees, rotatex, rotatey, SDL_FLIP_NONE);
}

void TextureManager::draw(TextureRegion textRegion, int x, int y, double degrees, int rotatex, int rotatey, SDL_RendererFlip flip) {
	drawResized(textRegion, x, y, textRegion.getRect().w, textRegion.getRect().h, degrees, rotatex, rotatey, flip);
}

void TextureManager::drawResized(TextureRegion textRegion, int x, int y, int w, int h) {
	drawResized(textRegion, x, y, w, h, 0, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::drawResized(TextureRegion textRegion, int x, int y, int w, int h, double degrees, int rotatex, int rotatey) {
	drawResized(textRegion, x, y, w, h, degrees, rotatex, rotatey, SDL_FLIP_NONE);
}

void TextureManager::drawResized(TextureRegion textRegion, int x, int y, int w, int h, double degrees, int rotatex, int rotatey, SDL_RendererFlip flip) {
	SDL_Rect dest = { x - Game::camera.pos.x, y - Game::camera.pos.y, w, h };
	SDL_Point point = { rotatex, rotatey };
	SDL_RenderCopyEx(Game::renderer, textRegion.getTexture(), &textRegion.getRect(), &dest, degrees, &point, flip);
}

void TextureManager::drawResizedStatic(TextureRegion textRegion, int x, int y, int w, int h, double degrees, int rotatex, int rotatey, SDL_RendererFlip flip) {
	SDL_Rect dest = { x, y, w, h };
	SDL_Point point = { rotatex, rotatey };
	SDL_RenderCopyEx(Game::renderer, textRegion.getTexture(), &textRegion.getRect(), &dest, degrees, &point, flip);
}