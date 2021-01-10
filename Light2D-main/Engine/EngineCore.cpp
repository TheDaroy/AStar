//#include "EngineCore.h"
//#include "Components/Components.h"
//
//
//
//
//LightEngine::EngineCore::EngineCore()
//{
//	
//
//	MakePointers();
//	RegisterComponents();
//	SetCollisionLayers();
//}
//
//
//
//void LightEngine::EngineCore::Test()
//{
//	std::cout<<"hello";
//}
//
//void LightEngine::EngineCore::MakePointers()
//{
//	EntityManager = std::make_unique<ECS::EntityManager>();
//	ComponentManager = std::make_unique<ECS::ComponentManager>();
//
//	collisionLayerManager = std::make_unique<CollisionLayerManager>();
//	Timer = std::make_unique<Resource::Timer>();
//	Input = std::make_unique<Resource::InputResource>();
//	windowResource = std::make_unique<WindowResource>();
//}
//
//void LightEngine::EngineCore::RegisterComponents()
//{
//	ComponentManager->AddNewComponentType<GraphicsComponent>();
//	ComponentManager->AddNewComponentType<TransformComponent>();
//	ComponentManager->AddNewComponentType<BoxCollider>();
//	ComponentManager->AddNewComponentType<PlayerComponent>();
//	ComponentManager->AddNewComponentType<ProjectileComponent>();
//
//	
//}
//
//
//
//void LightEngine::EngineCore::SetCollisionLayers()
//{
//	collisionLayerManager->AddCollisionToLayer(0, { 1,2,3 });
//	collisionLayerManager->AddCollisionToLayer(1, { 0,2,3 });
//	collisionLayerManager->AddCollisionToLayer(2, { 0,1,3 });
//	collisionLayerManager->AddCollisionToLayer(3, { 0,1,2 });
//}









