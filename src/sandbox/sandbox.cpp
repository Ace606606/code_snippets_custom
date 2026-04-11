#include "csc/utils/logger.hpp"

#include "csc/sandbox/foo/foo.hpp"

namespace Foo = csc::sandbox::foo;

int main()
{
     namespace log = csc::utils::logger;
     log::init_logger();

     Foo::Foo< int, float > foo{ 1, 2.0F };

     return 0;
}