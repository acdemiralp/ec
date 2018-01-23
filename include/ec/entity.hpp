#ifndef EC_ENTITY_HPP_
#define EC_ENTITY_HPP_

#include <cstddef>
#include <bitset>
#include <functional>

#include <boost/functional/hash.hpp>

namespace ec
{
template<std::size_t component_count>
class entity
{
public:
  entity            ()
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

protected:
  friend std::hash<entity<component_count>>;

  std::size_t                  id_               ;
  std::bitset<component_count> components_bitset_;
};
}

namespace std
{
template<std::size_t component_count>
struct hash<ec::entity<component_count>>
{
  size_t operator() (const ec::entity<component_count>& that) const
  {
    size_t seed = 0;
    boost::hash_combine(seed, std::hash<std::size_t>{}(that.id_));
    boost::hash_combine(seed, that.components_bitset_.hash());
    return seed;
  }
};
}

#endif