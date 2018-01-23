#include "catch.hpp"

#include <ec/table.hpp>

TEST_CASE("Table test.", "[table]")
{
  ec::table<int, long, float, double> table;
  auto e1 = table.create_entity();
  auto e2 = table.create_entity();
}