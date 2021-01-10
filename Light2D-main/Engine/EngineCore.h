#pragma once
#include "ECS/ComponentManager.h"
#include "ECS/EntityManager.h"
#include "ECS/ECS-Types.h"
#include "ECS/View.h"
#include "Resources/Timer.h"
#include "Resources/InputResource.h"
#include "Resources/WindowResource.h"
#include "Math/Vector2.h"
#include <memory>
#include "CollisionSettings.h"
#include "Components/Components.h"
#include "Shapes.h"
#include <iostream>

namespace LightEngine
{
	class EngineCore
	{
	private:
		void MakePointers()
		{
			EntityManager = std::make_unique<ECS::EntityManager>();
			ComponentManager = std::make_unique<ECS::ComponentManager>();

			collisionLayerManager = std::make_unique<CollisionLayerManager>();
			Timer = std::make_unique<Resource::Timer>();
			Input = std::make_unique<Resource::InputResource>();
			windowResource = std::make_unique<WindowResource>();
		}
		void RegisterComponents()
		{
			ComponentManager->AddNewComponentType<GraphicsComponent>();
			ComponentManager->AddNewComponentType<TransformComponent>();
			ComponentManager->AddNewComponentType<BoxCollider>();
			ComponentManager->AddNewComponentType<PlayerComponent>();
			ComponentManager->AddNewComponentType<ProjectileComponent>();
		}
		void SetCollisionLayers()
		{
			collisionLayerManager->AddCollisionToLayer(0, { 1,2,3 });
			collisionLayerManager->AddCollisionToLayer(1, { 0,2,3 });
			collisionLayerManager->AddCollisionToLayer(2, { 0,1,3 });
			collisionLayerManager->AddCollisionToLayer(3, { 0,1,2 });
		}
		int frames = 0;
		float time = 0;
	protected:

		EngineCore()
		{
			MakePointers();
			RegisterComponents();
			SetCollisionLayers();
		}
		void SuperEarly()
		{
			windowResource->ClearBackBuffer();
			Input->Update();
		}
		void Render()
		{
			time += Timer->DeltaTime();
			frames++;
			if (time >= 1)
			{				
				windowResource->PrintBorderFrameCounter(frames);
				frames = 0;
				time = 0;				
			}

			windowResource->Render();			
		}
		
		std::unique_ptr<ECS::EntityManager> EntityManager;
		std::unique_ptr<ECS::ComponentManager> ComponentManager;

		std::unique_ptr<CollisionLayerManager> collisionLayerManager;
		std::unique_ptr<Resource::Timer> Timer;
		std::unique_ptr<Resource::InputResource> Input;
		std::unique_ptr<WindowResource> windowResource;
	
	};
}