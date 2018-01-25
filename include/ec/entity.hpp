#ifndef EC_ENTITY_HPP_
#define EC_ENTITY_HPP_

#include <cstddef>
#include <bitset>
#include <functional>
#include <stdexcept>
#include <tuple>

#include <boost/functional/hash.hpp>
#include <boost/mp11.hpp>

#include <ec/scene.hpp>

namespace ec
{
template<typename... types>
class entity
{
public:
  using component_types = boost::mp11::mp_list<types...>;
  using component_count = boost::mp11::mp_size<component_types>;
  using bitset_type     = std::bitset<component_count::value>;
  using scene_type      = scene<entity<types...>>;

  explicit entity   (scene_type* scene) : scene_(scene)
  {
    if (!scene) throw std::runtime_error("Scene cannot be null.");

    static std::size_t next_id = 0;
    id_ = next_id++;
  }
  entity            (const entity&  that) = delete ;
  entity            (      entity&& temp) = default;
  virtual ~entity   ()                    = default;
  entity& operator= (const entity&  that) = delete ;
  entity& operator= (      entity&& temp) = default;
  bool    operator==(const entity&  that) const
  {
    return scene_ == that.scene_ && id_ == that.id_;
  }
  bool    operator!=(const entity&  that) const
  {
    return scene_ != that.scene_ || id_ != that.id_;
  }

  scene_type*                    scene           () const
  {
    return scene_;
  }
  const std::size_t&             id              () const
  {
    return id_;
  }
  const bitset_type&             bitset          () const
  {
    return bitset_;
  }
  
  template<typename... required_types>
  bool                           has_components  () const
  {
    using required_component_types   = boost::mp11::mp_list<required_types...>;
    using required_component_size    = boost::mp11::mp_size<required_component_types>;
    using required_component_indices = boost::mp11::mp_iota_c<required_component_size::value>;

    auto valid = true;
    boost::mp11::mp_for_each<required_component_indices>([&](const auto index)
    {
      using component_index = boost::mp11::mp_find<component_types, boost::mp11::mp_at_c<required_component_types, index>>;
      if (!bitset_[component_index::value])
        valid = false;
    });
    return valid;
  }
  template<typename type, typename... argument_types>
  type*                          add_component   (argument_types&&... arguments)
  {
    bitset_[boost::mp11::mp_find<component_types, type>::value] = true;
    auto& component = std::get<std::optional<type>>(scene_->table_.at(*this));
    component.emplace(arguments...);
    return &component.value();
  }
  template<typename type>
  void                           remove_component()
  {
    bitset_[boost::mp11::mp_find<component_types, type>::value] = false;
    std::get<std::optional<type>>(scene_->table_.at(*this)).reset();
  }
  template<typename type>
  type*                          component       () const
  {
    return bitset_[boost::mp11::mp_find<component_types, type>::value] ? &std::get<std::optional<type>>(scene_->table_.at(*this)).value() : nullptr;
  }
  template<typename... required_types>
  std::tuple<required_types*...> components      () const
  {
    using required_component_types   = boost::mp11::mp_list<required_types...>;
    using required_component_size    = boost::mp11::mp_size<required_component_types>;
    using required_component_indices = boost::mp11::mp_iota_c<required_component_size::value>;
    
    std::tuple<required_types*...> components;
    boost::mp11::mp_for_each<required_component_indices>([&] (const auto index)
    {
      using component_index = boost::mp11::mp_find<component_types, boost::mp11::mp_at_c<required_component_types, index>>;
      std::get<index>(components) = bitset_[component_index::value] ? &std::get<component_index::value>(scene_->table_.at(*this)).value() : nullptr;
    });
    return components;
  }

protected:
  scene_type* scene_ ;
  std::size_t id_    ;
  bitset_type bitset_;
};
}

namespace std
{
template<typename... types>
struct hash<ec::entity<types...>>
{
  size_t operator() (const ec::entity<types...>& that) const
  {
    size_t seed;
    boost::hash_combine(seed, hash<typename ec::entity<types...>::scene_type*>{}(that.scene ()));
    boost::hash_combine(seed, hash<size_t>                                    {}(that.id    ()));
    return seed;
  }
};
}

#endif