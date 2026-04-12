#include "csc/utils/logger.hpp"

#define SANDBOX_FOO 1
#define SANDBOX_SHARED_HEAP 1

#define OVERLOAD_STRING_OPERATOR 0

constexpr size_t kSizeOut = 50;

#if SANDBOX_FOO
#include "csc/sandbox/foo/foo.hpp"
#endif

#if SANDBOX_SHARED_HEAP
#include "csc/sandbox/shared_heap/shared_heap.hpp"
#endif

#if OVERLOAD_STRING_OPERATOR
#include <string>
namespace
{
std::string operator*( const std::string& str, const size_t n )
{
     std::string out;
     out.reserve( str.size() * n );
     for( size_t i{}; i < n; ++i )
     {
          out += str;
     }
     return out;
}
} // namespace
#endif

int main()
{
     namespace log = csc::utils::logger;
     log::init_logger();
#if OVERLOAD_STRING_OPERATOR
     {
          log::info( "{}", std::string( "=" ) * kSizeOut );
          log::info( "RUN SANDBOX" );
          log::info( "{}", std::string( "=" ) * kSizeOut );
     }
#else
     log::info( "{:=^{}}", " RUN SANDBOX ", kSizeOut );
#endif

#if SANDBOX_FOO
     {
          log::info( "{:-^{}}", " RUN FOO ", kSizeOut );
          namespace foo = csc::sandbox::foo;
          foo::Foo< int, float > cfoo{ 1, 2.0F };
     }
#endif

#if SANDBOX_SHARED_HEAP
     {
          log::info( "{:-^{}}", " SANDBOX_SHARED_HEAP ", kSizeOut );
          namespace shared_heap = csc::sandbox::shared_heap;
          shared_heap::WrapperHeap< int > wptr( static_cast< int* >( new int ) );
     }
#endif

     return 0;
}