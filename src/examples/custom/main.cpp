#include <deque>
#include <cstdint>
#include <functional>

#include "csc/utils/logger.hpp"

namespace csc::examples::custom
{

namespace log= csc::utils::logger;
void foo()
{
     std::deque< int > deq{ 1, 2, 3 };

     for ( const auto& item : deq  )
     {
          log::info( "{}", item );
     }
     
     auto item_front =  deq.front();
     log::info( "{}", item_front );
     
     for ( const auto& item : deq  )
     {
          log::info( "{}", item );
     }

     deq.pop_front();

     for ( const auto& item : deq  )
     {
          log::info( "{}", item );
     }
}


class Hello
{
public:
     explicit Hello( uint64_t value ) : value_( value ) {
          log::info( "Call contructor Hello" );
     }
     ~Hello()
     {
          log::info( "Call destructor Hello" );
     }

     void setCallback( std::function< void( uint64_t ) > cb )
     {
          cb_ = std::move( cb ) ;
     }

     void callCallback()
     {
          cb_( value_ );
     }

private:
     uint64_t value_{};
     std::function< void( uint64_t ) > cb_;
};


class Strategy
{
public:
     Strategy()
     {
          log::info( "Call contructor Strategy" );
     }
     ~Strategy()
     {
          log::info( "Call destructor Strategy" );
     }

     void setPtr( Hello* ptr )
     {
          hello_ = ptr;
     }

     void setCallback()
     {
          hello_->setCallback(
               [this]( uint64_t value ) -> void
               {
                    printHello( value );
               }
          );
     }

     void printHello( uint64_t value )
     {
          log::info(
               "Call callback Strategy {}",
               value
          );
     }

private:
     Hello* hello_ = nullptr;
};

} // namespace csc::examples::custom

namespace custom = csc::examples::custom;

int main()
{

     custom::log::info( "{:=^{}}", " Custom ", 50 );
     custom::Hello hello( 1 );

     {
          custom::Strategy strategy;
          strategy.setPtr( &hello );
          strategy.setCallback();
     }

     hello.callCallback(); // ub

     return 0;
}