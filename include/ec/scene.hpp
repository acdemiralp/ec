#ifndef EC_SCENE_HPP_
#define EC_SCENE_HPP_

#include <algorithm>
#include <optional>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace ec
{
template<typename... types>
class entity;

template<typename type>
class scene;
template<typename... types>
class scene<entity<types...>>
{
public:
  using entity_type     = entity<types...>;
  using components_type = std::tuple<std::optional<types>...>;

  entity_type              add_entity   ()
  {
    return entities_.emplace(entity_type(this), components_type()).first->first;
  }
  void                     remove_entity(const entity_type& entity)
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
  std::unordered_map<entity_type, components_type> entities_;
};
}

#endif
