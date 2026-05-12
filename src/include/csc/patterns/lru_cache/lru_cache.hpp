#include <list>
#include <unordered_map>
#include <cstdint>

namespace csc::patterns
{

class LruCache
{
public:
     explicit LruCache( uint64_t capacity );

     uint64_t getCapacity() const noexcept
     {
          return capacity_;
     }

private:
     uint64_t capacity_{};
};

} // namespace csc::patterns