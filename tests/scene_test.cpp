#include "catch.hpp"

#include <ec/entity.hpp>
#include <ec/scene.hpp>

TEST_CASE("Scene test.", "[scene]")
{
  ec::scene<ec::entity<int, long, float, double>> scene;
  auto entity_1     = scene.add_entity   ();
  auto entity_2     = scene.add_entity   ();
  auto entities     = scene.entities     ();
  auto entities_int = scene.entities<int>();
  scene.remove_entity(entity_2); // Find a way to invalidate existing handles.
}