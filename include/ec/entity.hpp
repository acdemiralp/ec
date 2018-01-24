#ifndef EC_ENTITY_HPP_
#define EC_ENTITY_HPP_

#include <cstddef>
#include <bitset>
#include <functional>

#include <boost/functional/hash.hpp>
#include <boost/mp11.hpp>

#include <ec/table.hpp>

namespace ec
{
template<typename... types>
class entity
{
public:
  using component_types = boost::mp11::mp_list<types...>;
  using component_count = boost::mp11::mp_size<component_types>;

  explicit entity   (table<entity<types...>>* table) : table_(table)
  {
    static std::size_t next_id = 0;
    id_ = next_id++;
  }
  entity            (const entity&  that) = default;
  entity            (      entity&& temp) = default;
  virtual ~entity   ()                    = default;
  entity& operator= (const entity&  that) = default;
  entity& operator= (      entity&& temp) = default;
  bool    operator==(const entity&  that) const
  {
    return id_ == that.id_;
  }
  bool    operator!=(const entity&  that) const
  {
    return id_ != that.id_;
  }

  table<entity<types...>>*                                table            () const
  {
    return table_;
  }
  const std::size_t&                         id               () const
  {
    return id_;
  }
  const std::bitset<component_count::value>& components_bitset() const
  {
    return components_bitset_;
  }

  template<typename... required_types>
  bool has_components() const
  {
    using required_component_types   = boost::mp11::mp_list<required_types...>;
    using required_component_size    = boost::mp11::mp_size<required_component_types>;
    using required_component_indices = boost::mp11::mp_iota_c<required_component_size::value>;

    auto valid = true;
    boost::mp11::mp_for_each<required_component_indices>([&](const auto index)
    {
      using component_index = boost::mp11::mp_find<component_types, boost::mp11::mp_at_c<required_component_types, index>>;
      if (!components_bitset_[component_index::value])
        valid = false;
    });

    return valid;
  }

  /*
  - Entity
  - Has Component  (entity)
  - Has Components (entity)

  - Component
  - Create         (entity)
  - Delete         (entity)
  - Get            (entity)
  */

protected:
  friend std::hash<entity<types...>>;

  using entity_type = entity<types...>;

  ec::table<float>*            table_            ;
  std::size_t                         id_               ;
  std::bitset<component_count::value> components_bitset_;
};
}

namespace std
{
template<typename... types>
struct hash<ec::entity<types...>>
{
  size_t operator() (const ec::entity<types...>& that) const
  {
    size_t seed = 0;
    boost::hash_combine(seed, hash<size_t>                                              {}(that.id_));
    boost::hash_combine(seed, hash<bitset<ec::entity<types...>::component_count::value>>{}(that.components_bitset_));
    return seed;
  }
};
}

#endif