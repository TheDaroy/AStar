#pragma once
#include "ECS-Types.h"
#include <cstdint>
#include <memory>
#include <vector>
namespace LightEngine::ECS
{

class EntityManager
{
public:
	EntityManager()
	{
		
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			availableEntites.push_back(entity);
		}
		std::reverse(availableEntites.begin(),availableEntites.end());


	}
	
	 Entity GetNewEntity()
	{
		Entity newEntity = availableEntites.back();
		availableEntites.pop_back();
		currentEntityAmount++;
		if (newEntity > highestActiveEntity)
		{
		 highestActiveEntity = newEntity;
		}
		return newEntity;
	}
	 void DestroyEntity(Entity entity)
	{
		availableEntites.push_back(entity);
		componentsOnEntityArray[entity].reset();
		currentEntityAmount--;
	}
	 void AddComponentToEntity(ComponentID compID, Entity entity)
	{		
		componentsOnEntityArray[entity].set(compID);

	}
	 void RemoveComponentFromEntity(ComponentID compID, Entity entity)
	{
		componentsOnEntityArray[entity].set(compID,false);
	}
	 ComponentSet GetEntityComponentSet(Entity entity)
	{
		//std::cout << entity << std::endl;
		return componentsOnEntityArray[entity];
	}
	 std::uint32_t GetCurrentEntitieAmount()
	{
		return currentEntityAmount;
	}
	
	 Entity GetEntityWithHighestValue()
	{
		return highestActiveEntity;
	}
private:

	std::unique_ptr<ComponentSet[]> componentsOnEntityArray = std::make_unique<ComponentSet[]>(MAX_ENTITIES);
	
	std::vector<Entity> availableEntites;
	std::uint32_t currentEntityAmount = 0;
	Entity highestActiveEntity = 0;
	

};
}


