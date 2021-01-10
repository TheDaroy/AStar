#pragma once
#include <cstdint>
#include <bitset>

using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 10000;


using SystemID = std::uint16_t;
static SystemID nrOfSystemTypes = 0;

using ComponentID = std::uint16_t;
const ComponentID MAX_COMPONENTS = 32;
static ComponentID nrOfComponentTypes = 0;

using ComponentSet = std::bitset<MAX_COMPONENTS>;