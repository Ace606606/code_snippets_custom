#pragma once

#include "csc/utils/logger.hpp"

namespace csc::sandbox::foo
{

namespace log = csc::utils::logger;

template < typename T >
class Value
{
     T value_;
public:
     explicit Value( T value): value_(value)
     {
          log::info( "Calling the consturctor 'Value' with value {}", value_ );
     }

     ~Value()
     {
          log::info( "Calling the destructor 'Value' with value {}", value_ );
     }
};

template < typename T, typename  U >
class Foo
{
     Value< T > value1_;
     Value< U > value2_;

public:
     Foo( T value1, U value2 ) : value1_( value1 ), value2_( value2 )
     {
          log::info( "Calling the consturctor 'Foo'" );
     }
     ~Foo()
     {
          log::info( "Calling the destrucotr 'Foo'" );
     }
};

} // namespace csc::sandbox::foo