#pragma once
#include "../Math/Vector2.h"
#include <SDL.h>
#include <string.h>
#include <map>
#include <iostream>
namespace LightEngine::Resource
{

class InputResource
{
public:
    InputResource();
//	enum MOUSE_BUTTON { left = 0, right, middle, back, forward };
	bool KeyDown(SDL_Scancode scanCode);
	/*bool KeyPressed(SDL_Scancode scanCode);
	bool KeyReleased(SDL_Scancode scanCode);

	bool MouseButtonDown(MOUSE_BUTTON button);
	bool MouseButtonPressed(MOUSE_BUTTON button);
	bool MouseButtonReleased(MOUSE_BUTTON button);*/

//	Vector2 MousePos();

	void Update();
//	void UpdatePrevInput();

private:

	const Uint8* keyboardStates;
	Uint8* mPrevKeyState;
	int mKeyLength;

	Uint32 mPrevMouseState;
	Uint32 mMouseState;

	int mMouseXPos;
	int mMouseYPos;

};
}


