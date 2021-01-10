#pragma once
#include <cstdint>
#include <bitset>
using CollisionLayer = std::uint8_t;
const CollisionLayer COLLISION_LAYER_AMOUNT = 4;

using CollisionSet = std::array<bool,COLLISION_LAYER_AMOUNT>;


// Work in progress