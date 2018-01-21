#ifndef EC_TABLE_HPP_
#define EC_TABLE_HPP_

#include <bitset>
#include <cstddef>
#include <optional>
#include <tuple>
#include <unordered_map>

namespace ec
{
template<typename... component_types>
class table
{
public:
  struct entity
  {
    std::size_t                             id              ;
    std::bitset<sizeof...(component_types)> component_bitset;
  };

  template<typename... argument_types>
  void add_row   (argument_types&&... arguments)
  {
    entities_.emplace(next_id_++, {});
  }
  void remove_row()
  {
    
  }

protected:
  std::size_t                                                                    next_id_ = 0;
  std::unordered_map<std::size_t, std::tuple<std::optional<component_types>...>> entities_;
};
}

#endif