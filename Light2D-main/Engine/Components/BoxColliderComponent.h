#pragma once
#include <vector>
#include "ECS/ECS-Types.h"
#include "CollisionData.h"



struct BoxCollider
{
	Vector2 size{ 10.f, 10.f};	
	uint32_t layer = 0;

	bool hit = false;
	std::vector<CollisionData> collisionData; 
	
	
};

