#pragma once

#include <memory>

#include "csc/utils/logger.hpp"

namespace csc::sandbox::shared_heap
{

namespace log = csc::utils::logger;

template < typename T >
class WrapperHeap
{
public:
     explicit WrapperHeap( T* rptr ) : sptr_( rptr ) 
     {
          log::info( "Calling the consturctor 'WrapperHeap' with value {}", static_cast< void* >( rptr ) );
     }

     T* Get() const
     {
          return sptr_.get();
     }
     
     ~WrapperHeap()
     {
          log::info( "Calling the destructor 'WrapperHeap' with value {}", static_cast< void* >( sptr_.get() ) );
     }

private:
     mutable std::shared_ptr< T > sptr_;
};

} // namespace csc::sandbox::shared_heap