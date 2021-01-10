#include "InputResource.h"


LightEngine::Resource::InputResource::InputResource()
{
	keyboardStates = SDL_GetKeyboardState(NULL);
}
bool LightEngine::Resource::InputResource::KeyDown(SDL_Scancode scanCode)
{
	
	return keyboardStates[scanCode];
}

void LightEngine::Resource::InputResource::Update()
{
	//std::cout << "hi" << std::endl;
	 keyboardStates = SDL_GetKeyboardState(NULL);
}

//InputResource::InputResource()
//{
//	mKeyStates = SDL_GetKeyboardState(&mKeyLength);
//	mPrevKeyState = new Uint8[mKeyLength];
//	memcpy(mPrevKeyState, mKeyStates, mKeyLength);
//}
//
//bool InputResource::KeyDown(SDL_Scancode scanCode)
//{
//	return mKeyStates[scanCode];
//}
//bool InputResource::KeyPressed(SDL_Scancode scanCode)
//{
//	return !mPrevKeyState[scanCode] && mKeyStates[scanCode];
//}
//bool InputResource::KeyReleased(SDL_Scancode scanCode)
//{
//	return mPrevKeyState[scanCode] && !mKeyStates[scanCode];
//}
//
//bool InputResource::MouseButtonDown(MOUSE_BUTTON button)
//{
//	Uint32 mask = 0;
//
//	switch (button)
//	{
//	case InputResource::left:
//		mask = SDL_BUTTON_LMASK;
//		break;
//	case InputResource::right:
//		mask = SDL_BUTTON_RMASK;
//		break;
//	case InputResource::middle:
//		mask = SDL_BUTTON_MMASK;
//		break;
//	case InputResource::back:
//		mask = SDL_BUTTON_X1MASK;
//		break;
//	case InputResource::forward:
//		mask = SDL_BUTTON_X2MASK;
//		break;
//
//	}
//	return (mMouseState & mask);
//}
//
//bool InputResource::MouseButtonPressed(MOUSE_BUTTON button)
//{
//	Uint32 mask = 0;
//
//	switch (button)
//	{
//	case InputResource::left:
//		mask = SDL_BUTTON_LMASK;
//		break;
//	case InputResource::right:
//		mask = SDL_BUTTON_RMASK;
//		break;
//	case InputResource::middle:
//		mask = SDL_BUTTON_MMASK;
//		break;
//	case InputResource::back:
//		mask = SDL_BUTTON_X1MASK;
//		break;
//	case InputResource::forward:
//		mask = SDL_BUTTON_X2MASK;
//		break;
//
//	}
//	return !(mPrevMouseState & mask) && (mMouseState & mask);
//}
//
//bool InputResource::MouseButtonReleased(MOUSE_BUTTON button)
//{
//	Uint32 mask = 0;
//
//	switch (button)
//	{
//	case InputResource::left:
//		mask = SDL_BUTTON_LMASK;
//		break;
//	case InputResource::right:
//		mask = SDL_BUTTON_RMASK;
//		break;
//	case InputResource::middle:
//		mask = SDL_BUTTON_MMASK;
//		break;
//	case InputResource::back:
//		mask = SDL_BUTTON_X1MASK;
//		break;
//	case InputResource::forward:
//		mask = SDL_BUTTON_X2MASK;
//		break;
//
//	}
//	return (mPrevMouseState & mask) && !(mMouseState & mask);
//}
//
//
//Vector2 InputResource::MousePos()
//{
//	return Vector2((float)mMouseXPos, (float)mMouseYPos);
//}
//
//void InputResource::Update()
//{
//	mMouseState = SDL_GetMouseState(&mMouseXPos, &mMouseYPos);
//}
//
//void InputResource::UpdatePrevInput()
//{
//	memcpy(mPrevKeyState, mKeyStates, mKeyLength);
//	mPrevMouseState = mMouseState;
//}