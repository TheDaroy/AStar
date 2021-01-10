#pragma once
#include <vector>
#include "Engine/Components/Components.h"
#include "Engine/ECS/EntityManager.h"
#include "Engine/ECS/ComponentManager.h"
#include "Engine/ECS/ECS-Types.h"
struct Board
{
	std::vector<std::vector<Entity>> boardvector;
	Board(int32_t boardSizeX, int32_t boardSizeY, LightEngine::ECS::EntityManager* entMngr, LightEngine::ECS::ComponentManager* compMngr)
	{
		
		
	}
};