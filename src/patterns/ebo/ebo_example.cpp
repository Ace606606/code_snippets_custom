#include "csc/utils/logger.hpp"

/*
     Empty base optimization (EBO)

     Пустой базовый класс не занимает памяти,
     если используется как base class.
*/

struct Empty
{};

struct WithoutEBO
{
     int value;
     Empty e;
};

struct WithEBO : Empty
{
     int value;
};

struct Derived : Empty
{
     Empty e; // EBO won't work!
     int value;
};

struct Modern
{
     int value;
     [[no_unique_address]] Empty e; // feature -std=c++20
};

namespace logger = csc::utils::logger;

int main()
{
     logger::init_logger();

     logger::info( "sizeof(Empty)      {}", sizeof( Empty ) );
     logger::info( "sizeof(WithoutEBO) {}", sizeof( WithoutEBO ) );
     logger::info( "sizeof(WithEBO)    {}", sizeof( WithEBO ) );

     logger::info( "sizeof(Derived)    {}", sizeof( Derived ) );
     logger::info( "sizeof(Modern)     {}", sizeof( WithEBO ) );
     return 0;
}
