#include <deque>

#include "csc/utils/logger.hpp"

namespace custom
{

     namespace log= csc::utils::logger;

}

int main()
{
     custom::log::info( "{:=^{}}", " Custom ", 50 );
     return 0;
}