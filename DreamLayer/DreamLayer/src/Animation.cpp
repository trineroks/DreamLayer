#include "Animation.h"

Animation::Animation() {

}

void Animation::addFrame(TextureRegion _tex) {
	textures.push_back(_tex);
}

int Animation::getSize() const {
	return textures.size();
}

TextureRegion& Animation::getFrame(int i) {
	return textures[i];
}

