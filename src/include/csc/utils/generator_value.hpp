#pragma once
#include <type_traits>
#include <cstdint>
#include <memory>
#include <limits>
#include <cassert>
#include <string_view>
#include <random>

namespace csc::utils::random
{

template < typename T >
class GeneratorBase
{
static_assert( std::is_arithmetic_v< T >, "GeneratorLCG can only be used with numeric types" );
public:
     explicit GeneratorBase( uint64_t seed ) : state_( seed == 0 ? 0xACE1ULL : seed ) {
          if constexpr ( std::is_floating_point_v< T >  )
          {
               max_ = 1;
          }
     }
     virtual ~GeneratorBase() = default;
     virtual T next() = 0;
     virtual std::string_view getName() const = 0;


     void setRange( uint64_t min, uint64_t max )
     {
          assert(min <= max && "Min must be less or equal to Max");
          min_ = min;
          max_ = max;
     }


protected:

     T transform( uint64_t state )
     {
          uint64_t kMax = std::numeric_limits< uint64_t >::max();

          if constexpr ( std::is_integral_v< T > )
          {
               if( max_ == kMax && min_ == 0 )
               {
                    return static_cast< T >( state );
               }
               uint64_t range = ( max_ - min_ + 1 );
               state = ( state % range ) + min_;
               return static_cast< T >( state );
          }
          else if constexpr( std::is_floating_point_v< T> )
          {
               T normalized = static_cast< T >( state ) / static_cast< T >( kMax );
               return static_cast< T >( normalized * ( max_ - min_ ) +  min_ );
          }
     }

     uint64_t state_;
     uint64_t min_{ 0 };
     uint64_t max_{ std::numeric_limits< uint64_t >::max() };
};

template < typename T >
class GeneratorLCG final : public GeneratorBase< T >
{
public:
     using  GeneratorBase< T >::GeneratorBase;

     T next() override
     {
          this->state_ = this->state_ * kMultiplier_ + kIncrement_;
          return this->transform( this->state_ );
     }

     std::string_view getName() const override
     {
          return kNameGenerator;
     }

private:
     /// LCG (Linear Congruential Generator)
     static constexpr uint64_t kMultiplier_ = 6364136223846793005ULL;
     static constexpr uint64_t kIncrement_ = 1442695040888963407ULL;
     static constexpr const char* kNameGenerator = "GeneratorLCG"; 
};

template < typename T >
class GeneratorXor final : public GeneratorBase< T >
{
public:
     using GeneratorBase< T >::GeneratorBase;

     T next() override
     {
          uint64_t x = this->state_;
          x ^= x << 13;
          x ^= x << 7;
          x ^= x << 17;
          this->state_ = x;

          return this->transform( x );
     }

     std::string_view getName() const override
     {
          return kNameGenerator;
     }
private:
     static constexpr const char* kNameGenerator = "GeneratorXor"; 
};

template < typename T >
class GeneratorSTD final : public GeneratorBase< T >
{
public:
     explicit GeneratorSTD( uint64_t seed ): GeneratorBase< T >( seed ), engine_( static_cast< unsigned int >( this->state_ ) ) {}

     T next() override
     {
          return this->transform( engine_() );
     }

     std::string_view getName() const override
     {
          return kNameGenerator;
     }

private:
     std::mt19937_64 engine_; // 64-битный Вихрь Мерсенна
     static constexpr const char* kNameGenerator = "GeneratorStd (MT19937)";
};

template < typename T, typename GenType = GeneratorLCG< T > >
std::unique_ptr< GeneratorBase< T > > make_generator_base( uint64_t seed )
{
     return std::make_unique<GenType>( seed );
}

template < typename GenType >
std::unique_ptr< GenType > make_generator( uint64_t seed )
{
     return std::make_unique<GenType>( seed );
}

} // namespace csc::utils::random