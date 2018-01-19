#include "catch.hpp"

#include <ec/table.hpp>

TEST_CASE("Table test.", "[table]")
{
  ec::table<int, long, float, double> table;
  REQUIRE(table.rows() == 0);
}