#ifndef EC_TABLE_HPP_
#define EC_TABLE_HPP_

#include <bitset>
#include <cstddef>
#include <optional>
#include <tuple>
#include <unordered_map>

namespace ec
{
template <typename... component_types>
class table
{
public:
  struct entity
  {
    std::size_t                             id;
    std::bitset<sizeof...(component_types)> component_bitset;
  };

  template <typename... argument_types>
  void add_entity   (argument_types&&... arguments)
  {
    return entities_.emplace({next_id_++, 0}, {}).first;
  }
  void remove_entity()
  {
    
  }
  void get_entity   ()
  {
    
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
  std::size_t                                                                    next_id_ = 0;
  std::unordered_map<std::size_t, std::tuple<std::optional<component_types>...>> entities_;
};
}

#endif
