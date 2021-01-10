#pragma once

#include "ECS/View.h"
#include "Components/Components.h"
#include "Resources/WindowResource.h"
#include "Resources/InputResource.h"
#include "CollisionLayer.h"
#include <list>
#include <algorithm>
#include <set>
#include "Engine/Math/MathFunctions.h"
#include <cmath>
#include <memory>
#include <queue>
#include <future>
namespace Systems::Graphics
{
	void Update(LightEngine::ECS::EntityManager* entMgr, LightEngine::ECS::ComponentManager* compMgr, WindowResource* winResource)
	{
		auto view = LightEngine::ECS::View<GraphicsComponent, TransformComponent>(compMgr, entMgr);
		for (auto entity : view)
		{
			GraphicsComponent& comp = compMgr->GetComponent<GraphicsComponent>(entity);
			TransformComponent& transformComp = compMgr->GetComponent<TransformComponent>(entity);
			comp.rect.x = (int)(transformComp.position.x - 200 * 0.5f);
			comp.rect.y = (int)(transformComp.position.y - 200 * 0.5f);
			winResource->DrawTexture(comp.texture,  &comp.rect, 0.f, SDL_FLIP_NONE);
		}		
	}
}



namespace Systems::Collision
{
	namespace 
	{
		bool BoxVsBox(const BoxCollider& rect1, const TransformComponent& pos1, const BoxCollider& rect2, const TransformComponent& pos2)
		{
			return (pos1.position.x < pos2.position.x + rect2.size.x
				&& pos1.position.x + rect1.size.x > pos2.position.x

				&& pos1.position.y < pos2.position.y + rect2.size.y
				&& pos1.position.y + rect1.size.y > pos2.position.y);
		}
	}
	void Update(LightEngine::ECS::EntityManager* entMgr, LightEngine::ECS::ComponentManager* compMgr, const std::array<CollisionSet,COLLISION_LAYER_AMOUNT> collisionDataArray)
	{
		
		auto view = LightEngine::ECS::View<TransformComponent, BoxCollider>(compMgr, entMgr);

		std::vector<Entity> entetiesToRemove;

		for (auto entity : view)
		{
			TransformComponent& transformComp = compMgr->GetComponent<TransformComponent>(entity);
			BoxCollider& colliderComp = compMgr->GetComponent<BoxCollider>(entity);

			colliderComp.collisionData.clear();
			colliderComp.hit = false;

			for (auto otherEntity : view)
			{
				if (otherEntity == entity )
				{
					continue;
				}
				TransformComponent& otherTransformComp = compMgr->GetComponent<TransformComponent>(otherEntity);
				BoxCollider& otherColliderComp = compMgr->GetComponent<BoxCollider>(otherEntity);
				if (collisionDataArray[colliderComp.layer][otherColliderComp.layer] == true)
				{
					if (BoxVsBox(colliderComp, transformComp, otherColliderComp, otherTransformComp))
					{
						colliderComp.hit = true;
						CollisionData newData;
						newData.entityHit = otherEntity;
						colliderComp.collisionData.push_back(newData);													
					}

				}
			}
		}
	}


}




namespace Systems::Player
{
	namespace
	{
		bool OnCollision(BoxCollider& collider)
		{
			if (collider.hit)
			{
				return true;// destroy
			}
			return false;
		}
		void Move(TransformComponent& transform, PlayerComponent& playerComp, LightEngine::Resource::InputResource* input, const float deltaTime)
		{
			if (input->KeyDown(SDL_SCANCODE_W))
			{
				//std::cout << "Right" << std::endl;
				transform.position.y -= playerComp.MoveSpeed * deltaTime;
			}
			if (input->KeyDown(SDL_SCANCODE_S))
			{
				//std::cout << "Left" << std::endl;
				transform.position.y += playerComp.MoveSpeed * deltaTime;
			}
			if (input->KeyDown(SDL_SCANCODE_A))
			{
				//std::cout << "Up" << std::endl;
				transform.position.x -= playerComp.MoveSpeed * deltaTime;
			}
			if (input->KeyDown(SDL_SCANCODE_D))
			{
				//std::cout << "Down" << std::endl;
				transform.position.x += playerComp.MoveSpeed * deltaTime;
			}
		}
		
	}

	void Update( LightEngine::ECS::EntityManager* entMgr, LightEngine::ECS::ComponentManager* compMgr,  LightEngine::Resource::InputResource* input, const float deltaTime)
	{
		auto view = LightEngine::ECS::View<PlayerComponent>(compMgr, entMgr);
		for (auto entity : view)
		{
			BoxCollider& colliderComp = compMgr->GetComponent<BoxCollider>(entity);
			if (OnCollision(colliderComp))
			{
				colliderComp.hit = false;
				colliderComp.collisionData.clear();
				entMgr->DestroyEntity(entity);
				continue;
			}
			TransformComponent& transfComponent = compMgr->GetComponent<TransformComponent>(entity);
			PlayerComponent& playerComp = compMgr->GetComponent<PlayerComponent>(entity);
			

			Move(transfComponent,playerComp, input,deltaTime);
			
		}
	}
}

namespace Systems::AI
{
	namespace AStar
	{

	struct AITileInfo
	{
		std::shared_ptr<AITileInfo> parentTile;
		BoardCoordinates coords;
		uint32_t gCost = 0;
		uint32_t hCost = 0;
		 uint8_t fCost()
		{
			return gCost + hCost;
		}
	};
	struct TileInfoCompare
	{
		bool operator()(std::shared_ptr<AITileInfo> lHS, std::shared_ptr<AITileInfo> rHS)
		{
			return lHS->gCost+lHS->hCost > rHS->gCost+rHS->hCost;
		}
	};

	std::vector<BoardCoordinates> FormPath(const std::shared_ptr<AITileInfo>  targetTile, const std::shared_ptr<AITileInfo>  endTile)
	{
		std::shared_ptr<AITileInfo> currentTile = targetTile;

		std::vector<BoardCoordinates> finalPath;
		while (currentTile != endTile)
		{
			finalPath.push_back(currentTile->coords);	
			currentTile = currentTile->parentTile;	
		}
		return finalPath;
	}

	int32_t GetDistance(const std::shared_ptr<AITileInfo>  tile1, const std::shared_ptr<AITileInfo> targetTile)
	{
		int32_t xDistance = std::abs(tile1->coords.x - targetTile->coords.x);
		int32_t yDistance = std::abs(tile1->coords.y - targetTile->coords.y);
		if (xDistance > yDistance)
		{
			return 14*yDistance + 10 * (xDistance-yDistance);
		}

		return 14 * xDistance + 10 * (yDistance-xDistance);
	}

	std::vector<std::shared_ptr<AITileInfo>> GetNeighbours(std::array<std::array<Entity, 75>, 75>* board, const std::shared_ptr<AITileInfo> tile, LightEngine::ECS::ComponentManager* compMgr)
	{
		std::vector<std::shared_ptr<AITileInfo>> neighbours;
		for (int16_t x = -1; x < 2; x++)
		{
			for (int16_t y = -1; y < 2; y++)
			{
				if (x == 0 && y == 0)
				{
					continue;
				}
				if (x + tile->coords.x >= 0 && x + tile->coords.x < 75 && y + tile->coords.y >= 0 && y + tile->coords.y < 75)
				{
					if (compMgr->GetComponent<TileComponent>((*board)[x + tile->coords.x][y + tile->coords.y]).available)
					{
						std::shared_ptr<AITileInfo> neigbourTile = std::make_shared<AITileInfo>();
						neigbourTile->coords = { x + tile->coords.x, y + tile->coords.y };
						neighbours.push_back(neigbourTile);
					}
				}
			}
		}
		return neighbours;
	}

	std::vector<BoardCoordinates> FindPath(LightEngine::ECS::ComponentManager* compMgr, std::array<std::array<Entity, 75>, 75>* board, BoardCoordinates targetCoords, BoardCoordinates startCoords)
	{
		std::set<BoardCoordinates> visitedTiles;
		std::set<BoardCoordinates> tilesToCheckSet;
		std::priority_queue< std::shared_ptr<AITileInfo>,std::vector<std::shared_ptr<AITileInfo>>,TileInfoCompare> tilesToCheckQueue;

		std::shared_ptr<AITileInfo> targetTile = std::make_shared<AITileInfo>();
		targetTile->coords = targetCoords;
		
		std::shared_ptr<AITileInfo> startTile = std::make_shared<AITileInfo>();
		startTile->coords = startCoords;
		tilesToCheckQueue.push(startTile);
		
		tilesToCheckSet.insert(startTile->coords);
		while (!tilesToCheckQueue.empty())
		{
			std::shared_ptr<AITileInfo> currentTile = tilesToCheckQueue.top();
			tilesToCheckQueue.pop();
			tilesToCheckSet.erase(currentTile->coords);
			visitedTiles.insert(currentTile->coords);
			if (currentTile->coords == targetTile->coords)
			{				
				return FormPath(currentTile, startTile);
			}
			for (std::shared_ptr<AITileInfo> neighbourTile : GetNeighbours(board, currentTile, compMgr))
			{
				if (visitedTiles.contains(neighbourTile->coords) || !compMgr->GetComponent<TileComponent>((*board)[neighbourTile->coords.x][neighbourTile->coords.y]).available)
				{
					continue;
				}
				int32_t movementCostToNeighbour = currentTile->gCost + GetDistance(currentTile, neighbourTile);
				if (movementCostToNeighbour < neighbourTile->gCost || !tilesToCheckSet.contains(neighbourTile->coords))
				{
					neighbourTile->gCost = movementCostToNeighbour;
					neighbourTile->hCost = GetDistance(neighbourTile, targetTile);
					neighbourTile->parentTile = currentTile;			
					 if (!tilesToCheckSet.contains(neighbourTile->coords))
					 {
						 tilesToCheckQueue.push(neighbourTile);
						 tilesToCheckSet.insert(neighbourTile->coords);
					 }
				}
			}
		}

		return {};
	}
	}
	
	BoardCoordinates FindRandAvailTile(LightEngine::ECS::ComponentManager* compMgr, int16_t minTileNr, int16_t maxTileNr, std::array<std::array<Entity, 75>, 75>* board)
	{	
		BoardCoordinates newTarget;
		do 
		{
			newTarget = { Math::RandomRange(minTileNr,maxTileNr), Math::RandomRange(minTileNr,maxTileNr) };
		} while (!compMgr->GetComponent<TileComponent>((*board)[newTarget.x][newTarget.y]).available);
		return newTarget;
	}
	void Move(LightEngine::ECS::ComponentManager* compMgr, WindowResource* winresource, AIComponent& aiComp, std::array<std::array<Entity, 75>, 75>* board)
	{
		compMgr->GetComponent<GraphicsComponent>((*board)[aiComp.currentPosition.x][aiComp.currentPosition.y]).texture = winresource->GetTexture("TileNormal");
		compMgr->GetComponent<TileComponent>((*board)[aiComp.currentPosition.x][aiComp.currentPosition.y]).available = true;
		aiComp.currentPosition = aiComp.path.back();
		compMgr->GetComponent<GraphicsComponent>((*board)[aiComp.currentPosition.x][aiComp.currentPosition.y]).texture = winresource->GetTexture("TileBusy");
		compMgr->GetComponent<TileComponent>((*board)[aiComp.currentPosition.x][aiComp.currentPosition.y]).available = false;
		aiComp.path.pop_back();
	}

	void Update(LightEngine::ECS::EntityManager* entMgr, LightEngine::ECS::ComponentManager* compMgr, const float deltaTime, std::array<std::array<Entity, 75>,75>* board, WindowResource* winresource)
	{
		
		auto view = LightEngine::ECS::View<AIComponent>(compMgr, entMgr);
		for (auto entity : view)
		{
			
			AIComponent& aiComp = compMgr->GetComponent<AIComponent>(entity);
			aiComp.timer += deltaTime;
			if (aiComp.timer >= aiComp.updateTime)
			{
					auto future = (std::async(std::launch::async, AStar::FindPath, compMgr, board, aiComp.targetPosition, aiComp.currentPosition));
					aiComp.path = future.get();
					//aiComp.path = AStar::FindPath(compMgr, board, aiComp.targetPosition, aiComp.currentPosition);
				if (aiComp.currentPosition != aiComp.targetPosition && aiComp.path.size() > 0)
				{	
				
					Move(compMgr, winresource, aiComp, board);
					/*for (BoardCoordinates tile : aiComp.path)
					{
						
						compMgr->GetComponent<GraphicsComponent>((*board)[tile.x][tile.y]).texture = winresource->GetTexture("TilePath");
					}*/					
				}
				else
				{				
					aiComp.targetPosition = FindRandAvailTile(compMgr, 0, 74, board);
					//auto future = (std::async(std::launch::async, AStar::FindPath, compMgr, board, aiComp.targetPosition, aiComp.currentPosition));
					//aiComp.path = future.get();
								
				  // aiComp.path = AStar::FindPath(compMgr, board, aiComp.targetPosition, aiComp.currentPosition);  
					//Move(compMgr, winresource, aiComp, board);
				}
				aiComp.timer = 0;
			}	
		}		
	}
}
