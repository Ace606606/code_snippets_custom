#include <string>

#include "csc/containers/lru_cache.hpp"
#include "csc/utils/logger.hpp"

namespace csc::examples
{

namespace log = csc::utils::logger;
using LruCache = csc::containers::LruCache< uint64_t, std::string >;

void run_examples_containers()
{
     LruCache lru{ 5 };
     log::info( "{}", lru.capacity() );
     log::info( "Contains 1: {}", lru.contains( 1 ) );
     // lru.put( 1, "0x1" );
     // lru.put( 0x2, "0x2" );
     // lru.put( 0x3, "0x3" );
     // lru.put( 0x4, "0x4" );
     // lru.put( 0x5, "0x5" );
     // lru.put( 0x6, "0x6" );
     // lru.put( 0x2, "0x2" );
     // lru.put( 0x7, "0x7" );
     log::info( "Size {}", lru.size() );


}

} // namespace csc::examples

int main()
{
     csc::examples::run_examples_containers();
     return 0;
}