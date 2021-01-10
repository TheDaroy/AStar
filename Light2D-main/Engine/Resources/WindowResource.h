#pragma once
#include <SDL_image.h>
#include <SDL.h>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <cassert>
#include <future>
class WindowResource
{
public:
	WindowResource()
	{
		window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}
	~WindowResource()
	{
		SDL_DestroyWindow(window);
	}
	SDL_Window* GetWindow() 
	{
		return window;
	}
	
	SDL_Renderer* GetRenderer()
	{
		return renderer;
	}
	void ClearBackBuffer()
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
	}
	
	void Render()
	{
		SDL_RenderPresent(renderer);
	}

	void PrintBorderFrameCounter(int frames)
	{	
		char buffer[64];
		sprintf_s(buffer, "%s%s%s%d",windowName," | ","FPS: ",frames);		
		SDL_SetWindowTitle(window, buffer);
	}


	void DrawTexture(SDL_Texture* tex, SDL_Rect* rect, float angle, SDL_RendererFlip flip)
	{
		SDL_RenderCopyEx(renderer, tex, NULL, rect, angle, NULL, flip);
		
	}

	/**
	*  \param position1  =  Start point
	*  \param position2  =  End Point
	*  \param color     =  Color of the line	
	*/
	void DrawLine(Vector2 position1, Vector2 position2, SDL_Color color)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLine(renderer, position1.x, position1.y, position2.x, position2.y);
	}


	/**
	*  \param position  =  The center position of the square
	*  \param size      =  The Radius of the square
	*  \param color     =  The Border color of the square	* 
    */
	void DrawSquare(Vector2 position, float size, SDL_Color color)
	{
		SDL_Rect rect = { position.x + size,  position.y - size, size*2, size*2 };
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawRect(renderer,&rect);
	}

	/**
	*  \param position  =  The center position of the square
	*  \param size      =  The Radius of the square
	*  \param color     =  The Color of the square	*
	*/
	void DrawFilledSquare(Vector2 position, float size, SDL_Color color)
	{
		SDL_Rect rect = { position.x + size,  position.y - size, size * 2, size * 2 };
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer,&rect);
	}




	// Loads Texture from asset in designated asset folder with filename. 
	// Also saves texture with given name.
	void LoadNewTexture(std::string fileName, const char* textureName)
	{
		Texturemap[textureName] = LoadTexture(fileName);
	}
	SDL_Texture* GetTexture(const char* textureName)
	{
		assert(Texturemap.find(textureName) != Texturemap.end());
		return Texturemap[textureName];
	}

	float GetScreenHeight()
	{
		return SCREEN_HEIGHT;
	}
	float GetScreenWidth()
	{
		return SCREEN_WIDTH;
	}

	const char* windowName = "Light2D";
	const std::string graphicsFolderPath = "Light2D-main/Assets/Graphics/";

private:

	const std::uint32_t SCREEN_WIDTH = 1280;
	const std::uint32_t SCREEN_HEIGHT = 1000;


	SDL_Texture* LoadTexture(std::string path)
	{
		std::string fullpath = graphicsFolderPath + path;
		SDL_Surface* surface = IMG_Load(fullpath.c_str());

		if (surface == nullptr)
		{
			std::cout << "Error Loading Texture";
		}

		SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		return tex;
	}


	SDL_Renderer* renderer;
	SDL_Window* window;
	std::unordered_map<const char*, SDL_Texture*> Texturemap;
};

