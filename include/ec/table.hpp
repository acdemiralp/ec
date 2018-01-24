#ifndef EC_TABLE_HPP_
#define EC_TABLE_HPP_

#include <optional>
#include <unordered_map>
#include <utility>

#include <ec/entity.hpp>

namespace ec
{
template <typename... component_types>
class table
{
public:
  static const std::size_t component_count = sizeof...(component_types);

  using entity         = entity<component_count>;
  using components     = std::tuple<std::optional<component_types>...>;
  using iterator       = typename std::unordered_map<entity, components>::iterator;
  using const_iterator = typename std::unordered_map<entity, components>::const_iterator;

  entity create_entity()
  {
    return entities_.emplace().first->first;
  }
  void   delete_entity(const entity& entity)
  {
    entities_.erase(entity);
  }

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
  std::unordered_map<entity, components> entities_;
};
}

#endif