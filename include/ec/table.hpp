#ifndef EC_TABLE_HPP_
#define EC_TABLE_HPP_

#include <optional>
#include <unordered_map>
#include <utility>

#include <boost/mp11.hpp>

#include <ec/entity.hpp>

namespace ec
{
template <typename... types>
class table
{
public:
  using component_types   = boost::mp11::mp_list<types...>;
  using component_count   = boost::mp11::mp_size<component_types>;
  using component_storage = std::tuple<std::optional<types>...>;
  using entity_type       = entity<table<types...>>;

  entity_type              create_entity()
  {
    return entities_.emplace(entity_type(this), component_storage{1, std::nullopt, std::nullopt, std::nullopt}).first->first;
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
    using required_component_types   = boost::mp11::mp_list<required_types...>;
    using required_component_size    = boost::mp11::mp_size<required_component_types>;
    using required_component_indices = boost::mp11::mp_iota_c<required_component_size::value>;

    std::vector<entity_type> entities;
    std::for_each(entities_.begin(), entities_.end(), [&entities] (const auto& iteratee)
    {
      auto valid = true;

      boost::mp11::mp_for_each<required_component_indices>([&] (auto index)
      {
        using component_index = boost::mp11::mp_find<component_types, boost::mp11::mp_nth_element_c<required_component_types, index, std::less>>;
        if (!iteratee.first.components_bitset()[component_index::value])
          valid = false;
      });

      if(valid)
        entities.push_back(iteratee.first);
    });
    return entities;
  }

  /*
  - Entity
    - Has Component  (entity)
    - Has Components (entity)
    - Get Scene      (entity)
                     
  - Component        
    - Create         (entity)
    - Delete         (entity)
    - Get            (entity)
  */

protected:
  std::unordered_map<entity_type, component_storage> entities_;
};
}

#endif