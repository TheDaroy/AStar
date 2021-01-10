#pragma once
#include "EntityManager.h"
#include "ComponentManager.h"
#include <cstdint>

namespace LightEngine::ECS
{
template<typename...Components>
struct View
{
	ComponentManager* compManager;
	EntityManager* entManager;
	ComponentSet set;
	Entity nrToitterateTo;
	
	View( ComponentManager* _compManager,  EntityManager* _entManager)
	{
		compManager = _compManager;
		entManager = _entManager;
		ComponentID compIDs[] = { compManager->GetComponentID<Components>()...};
		for (ComponentID id : compIDs)
		{			
			set.set(id);
		}
		nrToitterateTo = entManager->GetEntityWithHighestValue()+1;
	}

	struct iterator
	{
		EntityManager* entManager;
		Entity entity;
		ComponentSet set;
		Entity nrToitterateTo;
		iterator(EntityManager* _entManager, Entity _entity, ComponentSet _set, Entity highestValueEntity)
		{
			entManager = _entManager;
			entity = _entity;
			set = _set;		
			nrToitterateTo = highestValueEntity;
		}

		auto operator*()const
		{
			return entity;
		}

		bool operator==(const iterator& other) const
		{
			return entity == other.entity || entity == nrToitterateTo;

		}

		bool operator!=(const iterator& other) const
		{
			return entity != other.entity && entity != nrToitterateTo;
		}

		iterator& operator++()
		{
			do
			{
				entity++; 
			} while ((set & entManager->GetEntityComponentSet(entity)) != set && entity < nrToitterateTo);
			
			return *this;
		}
	};


	const iterator begin() const
	{
		std::uint32_t first_index = 0;
		while (first_index < nrToitterateTo && (set & entManager->GetEntityComponentSet(first_index)) != set)
		{
			first_index++;			
		}
		return iterator(entManager, first_index, set, nrToitterateTo);
	}
	const iterator end() const
	{		
		return iterator(entManager, nrToitterateTo, set, nrToitterateTo);
	}
		
	

};
}