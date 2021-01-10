#pragma once
#include "ECS-Types.h"
#include <array>

namespace LightEngine::ECS
{

class ComponentListHead{};

template<typename T>
class ComponentList : public ComponentListHead
{
public:
	
	 void AddComponent(Entity entity, T& component)
	{
		componentArray[entity] = component;
	}

	 T& GetComponent(Entity entity)
	{
		//std::cout<<entity<<std::endl;
		return componentArray[entity];
	}
	 size_t GetAmountOfActiveComponents()
	{
		return currentActiveComponents;
	}
	

private:	
	std::array<T, MAX_ENTITIES> componentArray;
	size_t currentActiveComponents = 0;
};
}



