#ifndef EC_TABLE_HPP_
#define EC_TABLE_HPP_

#include <cstddef>
#include <optional>
#include <unordered_map>

#include <ec/entity.hpp>

namespace ec
{
template <typename... component_types>
class table
{
public:
  /*
  - Insert or remove an entity (row).
  - Insert or remove a component to or from an entity.
  - Iterate through all entities (rows).
  - Iterate through all entities (rows) containing one or more component types (columns).
  - Query an entity's components        (select row  , given row index).
  - Query an entity's component by type (select entry, given row index and column type).
  - Query a component's entity          (select row  , given entry).
  */

protected:
  std::size_t                                                                                           next_id_ = 0;
  std::unordered_map<entity<sizeof...(component_types)>, std::tuple<std::optional<component_types>...>> entities_;
};
}

#endif