#ifndef EC_ENTITY_HPP_
#define EC_ENTITY_HPP_

#include <cstddef>
#include <functional>

#include <boost/dynamic_bitset.hpp>
#include <boost/functional/hash.hpp>

namespace ec
{
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
  friend std::hash<ec::entity>;

  std::size_t              id_               ;
  boost::dynamic_bitset<>  components_bitset_;
};
}

namespace std
{
template<>
struct hash<ec::entity>
{
  size_t operator() (const ec::entity& that) const
  {
    size_t seed = 0;
    boost::hash_combine(seed, boost::hash_value(that.id_));
    boost::hash_combine(seed, boost::hash_value(that.components_bitset_));
    return seed;
  }
};
}

#endif
