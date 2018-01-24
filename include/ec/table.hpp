#ifndef EC_TABLE_HPP_
#define EC_TABLE_HPP_

#include <algorithm>
#include <optional>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace ec
{
template <typename entity_type>
class table
{
public:
  entity_type              create_entity()
  {
    return entities_.emplace(entity_type(this), std::tuple<std::optional<typename entity_type::component_types>...>()).first->first;
  }
  void                     delete_entity(const entity_type& entity)
  {
    entities_.erase(entity);
  }
  std::vector<entity_type> entities     () const
  {
    std::vector<entity_type> entities;
    std::transform(entities_.begin(), entities_.end(), std::back_inserter(entities), [ ] (const auto& iteratee)
    {
      return iteratee.first;
    });
    return entities;
  }
  template<typename... required_types>
  std::vector<entity_type> entities     () const
  {
    std::vector<entity_type> entities;
    std::for_each(entities_.begin(), entities_.end(), [&entities] (const auto& iteratee)
    {
      if(iteratee.first.has_components<required_types...>())
        entities.push_back(iteratee.first);
    });
    return entities;
  }

protected:
  std::unordered_map<entity_type, std::tuple<std::optional<typename entity_type::component_types>...>> entities_;
};
}

#endif
