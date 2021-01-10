#include "GameManger.h"
#include <memory>
int main(int argc, char* argv[])
{
	
	std::unique_ptr<GameManager> gameManager = std::make_unique<GameManager>();

	gameManager->Setup();
	gameManager->UpdateLoop();
	return 0;
};