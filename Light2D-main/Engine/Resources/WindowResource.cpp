//#include "WindowResource.h"
//#include <iostream>
//WindowResource::WindowResource()
//{
//	window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//}
//
//
//WindowResource::~WindowResource()
//{
//	SDL_DestroyWindow(window);
//	
//}
//
//SDL_Window* WindowResource::GetWindow()
//{
//	return window;
//}
//
//SDL_Renderer* WindowResource::GetRenderer()
//{
//	return renderer;
//}
//
//void WindowResource::ClearBackBuffer()
//{
//	SDL_SetRenderDrawColor(renderer,0,0,0,0);
//	SDL_RenderClear(renderer);
//}
//
//void WindowResource::Render()
//{
//	
//	SDL_RenderPresent(renderer);
//}
//
//void WindowResource::DrawTexture(SDL_Texture* texture, SDL_Rect* clip, SDL_Rect* rect, float angle, SDL_RendererFlip flip)
//{
//	
//	SDL_RenderCopyEx(renderer, texture, NULL, rect, angle,NULL ,flip);
//	//SDL_RenderDrawLine(renderer, rect.x, rend, endX, endY);
//}
//
//
//SDL_Texture* WindowResource::LoadTexture(std::string path)
//{	
//	std::string fullpath = graphicsFolderPath + path;
//	SDL_Surface* surface = IMG_Load(fullpath.c_str());
//
//	if (surface == nullptr)
//	{
//		std::cout<<"Error Loading Texture";
//	}
//
//	SDL_Texture*  tex = SDL_CreateTextureFromSurface(renderer, surface);
//	SDL_FreeSurface(surface);
//
//	return tex;
//}
//
//void WindowResource::LoadNewTexture(std::string fileName, const char* textureName)
//{
//	Texturemap[textureName] = LoadTexture(fileName);
//	
//}
//
//SDL_Texture* WindowResource::GetTexture(const char* textureName)
//{
//	assert(Texturemap.find(textureName) != Texturemap.end());
//	return Texturemap[textureName];
//}
