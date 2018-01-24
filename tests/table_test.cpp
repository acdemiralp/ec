#include "catch.hpp"

#include <ec/entity.hpp>
#include <ec/table.hpp>

TEST_CASE("Table test.", "[table]")
{
  using entity = ec::entity<int, long, float, double>;

  ec::table<entity> table;
  auto entity_1     = table.create_entity();
  auto entity_2     = table.create_entity();
  auto entities     = table.entities     ();
  auto entities_int = table.entities<int>();
  table.delete_entity(entity_2);
}