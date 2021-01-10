#pragma once

#include <SDL_image.h>
#include <cstdint>

struct GraphicsComponent
{
	SDL_Texture* texture;
	SDL_Rect rect;
	std::uint32_t textureWidth;
	std::uint32_t textureHeight;
};