#ifndef EC_TABLE_HPP_
#define EC_TABLE_HPP_

#include <tuple>
#include <vector>

namespace ec
{
template<typename... types>
class table
{
public:
  std::size_t rows() const
  {
    return entities_.size();
  }

protected:
  std::vector<std::tuple<types...>> entities_;
};
}

#endif