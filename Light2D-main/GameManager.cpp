#include "GameManger.h"
#include "Engine/GameSystems.h"
#include <iostream>
#include <random>

void GameManager::Setup()
{
	ComponentManager->AddNewComponentType<TileComponent>();
	windowResource->LoadNewTexture("SquareWhite.png","TileNormal");
	windowResource->LoadNewTexture("SquareRed.png", "TileBusy");
	windowResource->LoadNewTexture("SquareGrey.png", "TilePath");
	ComponentManager->AddNewComponentType<AIComponent>();
	CreateBoard();

	for (int i = 0; i < 50; i++)
	{
		CreateAI();
	}



}
void GameManager::UpdateLoop()
{
	
	while (!quit)
	{
		Timer->Update();
		while (SDL_PollEvent(&mEvents)) {

			if (mEvents.type == SDL_QUIT) {

				quit = true;
			}
		}
		Timer->Reset();		
		SuperEarly();
		EarlyUpdate();
		Update();
		LateUpdate();
		Render();
	}
}
void GameManager::EarlyUpdate()
{
	
}


void GameManager::Update()
{
	
	Systems::AI::Update(EntityManager.get(),ComponentManager.get(),Timer->DeltaTime(),Board,windowResource.get());
	Systems::Collision::Update(EntityManager.get(), ComponentManager.get(),collisionLayerManager->GetCollisionDataArray());
}
void GameManager::LateUpdate()
{

	Systems::Graphics::Update(EntityManager.get(),ComponentManager.get(),windowResource.get());
}

void GameManager::CreateBoard()
{
	for (uint32_t x = 0; x < 75; x++)
	{
		for (uint32_t y = 0; y < 75; y++)
		{
			Entity entity = EntityManager->GetNewEntity();
			EntityManager->AddComponentToEntity(ComponentManager->GetComponentID<TileComponent>(),entity);
			EntityManager->AddComponentToEntity(ComponentManager->GetComponentID<GraphicsComponent>(), entity);
			EntityManager->AddComponentToEntity(ComponentManager->GetComponentID<TransformComponent>(), entity);
			TransformComponent& transfComp =  ComponentManager->GetComponent<TransformComponent>(entity);
			transfComp.position.x = x * 15 + 200;
			transfComp.position.y = y * 15 + 100;
			GraphicsComponent& graphicsComponent = ComponentManager->GetComponent<GraphicsComponent>(entity);
			graphicsComponent.texture = windowResource->GetTexture("TileNormal");
			graphicsComponent.rect.h = 14;
			graphicsComponent.rect.w = 14;	

			if (Math::RandomRange(0,15) == 0)
			{
				graphicsComponent.texture = windowResource->GetTexture("TilePath");
				ComponentManager->GetComponent<TileComponent>(entity).available = false;
			}
			else
			{
				graphicsComponent.texture = windowResource->GetTexture("TileNormal");
			}
			(*Board)[x][y] = entity;
		}
	}
}


void GameManager::CreateAI()
{
	Entity entity = EntityManager->GetNewEntity();
	EntityManager->AddComponentToEntity(ComponentManager->GetComponentID<AIComponent>(),entity);
	AIComponent& aiComp = ComponentManager->GetComponent<AIComponent>(entity);
	aiComp.currentPosition = Systems::AI::FindRandAvailTile(ComponentManager.get(), 0, 74, Board);
	ComponentManager->GetComponent<TileComponent>((*Board)[aiComp.currentPosition.x][aiComp.currentPosition.y]).available = false;
	//aiComp.targetPosition = Systems::AI::FindRandAvailTile(ComponentManager.get(),0,74,Board);
	aiComp.targetPosition = {0,0};
	aiComp.path = Systems::AI::AStar::FindPath(ComponentManager.get(),Board,aiComp.targetPosition,aiComp.currentPosition);
}