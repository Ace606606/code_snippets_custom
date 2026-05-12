#include <deque>

#include "csc/utils/logger.hpp"

namespace custom
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

} // namespace custom

int main()
{
     custom::log::info( "{:=^{}}", " Custom ", 50 );
     custom::foo();
     return 0;
}