#include "Engine/EngineCore.h"
#include <SDL_events.h>
#include <array>
class GameManager : public LightEngine::EngineCore
{
public:
   
	void Setup();


	void UpdateLoop();
	void EarlyUpdate();
	void Update();
	void LateUpdate();


	private:
	SDL_Event mEvents;
	bool quit = false;
	
	
	void CreateBoard();
	void CreateAI();
	std::array<std::array<Entity, 75>,75> *Board = new std::array<std::array<Entity, 75>, 75>;
	
};






