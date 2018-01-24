#ifndef EC_ENTITY_HPP_
#define EC_ENTITY_HPP_

#include <cstddef>
#include <bitset>
#include <functional>

#include <boost/functional/hash.hpp>

namespace ec
{
template<typename table_type>
class entity
{
public:
  explicit entity   (table_type* table) : table_(table)
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

  const std::size_t&                                     id               () const
  {
    return id_;
  }
  const std::bitset<table_type::component_count::value>& components_bitset() const
  {
    return components_bitset_;
  }

protected:
  friend std::hash<entity<table_type>>;

  table_type*                                     table_            ;
  std::size_t                                     id_               ;
  std::bitset<table_type::component_count::value> components_bitset_;
};
}

namespace std
{
template<typename table_type>
struct hash<ec::entity<table_type>>
{
  size_t operator() (const ec::entity<table_type>& that) const
  {
    size_t seed = 0;
    boost::hash_combine(seed, hash<size_t>                                    {}(that.id_));
    boost::hash_combine(seed, hash<bitset<table_type::component_count::value>>{}(that.components_bitset_));
    return seed;
  }
};
}

#endif