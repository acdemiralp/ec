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
  
  std::vector<entity_type*> append       (const scene& that)
  {
    std::vector<entity_type*> entities;
    for (auto& entry : that.table_)
      entities.push_back(const_cast<entity_type*>(&table_.emplace(entity_type(next_id_++, this, entry.first.bitset()), entry.second).first->first));
    return entities;
  }
  void                      clear        ()
  {
    table_.clear();
  }
 
  entity_type*              add_entity   ()
  {
    return const_cast<entity_type*>(&table_.emplace(entity_type(next_id_++, this), components_type()).first->first);
  }
  entity_type*              copy_entity  (const entity_type* entity)
  {
    return const_cast<entity_type*>(&table_.emplace(entity_type(next_id_++, this, entity->bitset()), entity->scene()->table_.at(*entity)).first->first);
  }
  void                      remove_entity(const entity_type* entity)
  {
    table_.erase(*entity);
  }
   
  std::vector<entity_type*> entities     () const
  {
    std::vector<entity_type*> entities;
    std::transform(table_.begin(), table_.end(), std::back_inserter(entities), [ ] (const auto& iteratee)
    {
      return const_cast<entity_type*>(&iteratee.first);
    });
    return entities;
  }
  template<typename... required_types>
  std::vector<entity_type*> entities     () const
  {
    std::vector<entity_type*> entities;
    std::for_each(table_.begin(), table_.end(), [&entities] (const auto& iteratee)
    {
      if(iteratee.first.has_components<required_types...>())
        entities.push_back(const_cast<entity_type*>(&iteratee.first));
    });
    return entities;
  }
  
protected:
  friend entity<types...>;

  std::unordered_map<entity_type, components_type> table_   ;
  std::size_t                                      next_id_ = 0;
};
}

#endif