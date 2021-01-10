#pragma once

#include "CollisionLayer.h"
#include <array>
#include <vector>






class CollisionLayerManager
{
	std::array<CollisionSet, COLLISION_LAYER_AMOUNT> CollisionData;

public:

	void AddCollisionToLayer(CollisionLayer layerToChange, CollisionLayer LayerToCollideWith)
	{
		if (LayerToCollideWith < COLLISION_LAYER_AMOUNT)
		{
			CollisionData[layerToChange][LayerToCollideWith] = true;
		}
	}
	void AddCollisionToLayer(CollisionLayer layerToChange, std::vector<CollisionLayer> LayerToCollideWith )
	{
		for (CollisionLayer layer : LayerToCollideWith)
		{
			if (layer < COLLISION_LAYER_AMOUNT)
			{
				CollisionData[layerToChange][layer] = true;
			}
		}
		
	}
	void RemoveCollisionFromLayer(CollisionLayer layerToChange, CollisionLayer layerToRemove)
	{
		if (layerToRemove < COLLISION_LAYER_AMOUNT)
		{
			CollisionData[layerToChange][layerToRemove] = false;
		}
	}
	void RemoveCollisionFromLayer(CollisionLayer layerToChange, std::vector<CollisionLayer> layerToRemove)
	{
		for (CollisionLayer layer : layerToRemove)
		{	
			if (layer < COLLISION_LAYER_AMOUNT)
			{
				CollisionData[layerToChange][layer] = false;
			}
		}
		
	}

	const CollisionSet GetCollisionSet(CollisionLayer layerSetToGet)
	{
		return CollisionData[layerSetToGet];
	}

	const std::array<CollisionSet, COLLISION_LAYER_AMOUNT> GetCollisionDataArray()
	{
		return CollisionData;
	}
};






