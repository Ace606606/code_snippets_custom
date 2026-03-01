#pragma once
#include <array>
#include <cstddef>
#include <cstring>
#include <type_traits>
#include <utility>

class Function
{
     static constexpr std::size_t BufferSize = 32;

     union Data
     {
          alignas( std::max_align_t ) std::array< char, BufferSize > buffer_;
          void* ptr_ = nullptr;
     };

public:
     Function() = default;

     template< typename F >
     explicit Function( F f )
     {
          using T = std::decay_t< F >;

          if constexpr( sizeof( T ) <= BufferSize )
          {
               new( &data_.buffer_ ) T( std::move( f ) );
               invoker_ = []( Data& data ) { ( *reinterpret_cast< T* >( data.buffer_.data() ) )(); };

               destroyer_ = []( Data& data ) { reinterpret_cast< T* >( data.buffer_.data() )->~T(); };
               is_heap_ = false;
          }
          else
          {
               data_.ptr_ = new T( std::move( f ) );
               invoker_ = []( Data& data ) { ( *reinterpret_cast< T* >( data.ptr_ ) )(); };
               destroyer_ = []( Data& data ) { delete reinterpret_cast< T* >( data.ptr_ ); };
               is_heap_ = true;
          }
     }
     Function( const Function& ) = delete;
     Function& operator=( const Function& ) = delete;
     Function( Function&& other ) noexcept { *this = std::move( other ); }
     Function& operator=( Function&& other ) noexcept
     {
          if( this != &other )
          {
               cleanup();
               data_ = other.data_;
               invoker_ = other.invoker_;
               destroyer_ = other.destroyer_;
               is_heap_ = other.is_heap_;

               other.invoker_ = nullptr;
          }
          return *this;
     }

     ~Function() { cleanup(); }

     void operator()()
     {
          if( invoker_ != nullptr )
          {
               invoker_( data_ );
          }
     }

private:
     void cleanup()
     {
          if( invoker_ != nullptr )
          {
               destroyer_( data_ );
               invoker_ = nullptr;
          }
     }

     Data data_;

     void ( *invoker_ )( Data& ) = nullptr;
     void ( *destroyer_ )( Data& ) = nullptr;

     bool is_heap_ = false;
};