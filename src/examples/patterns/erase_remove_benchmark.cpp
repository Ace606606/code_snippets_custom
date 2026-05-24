#include <deque>
#include <list>
#include <random>
#include <vector>

#include "csc/utils/timer.hpp"

/*
     Сравнение (N = 1,000,000):

     1) erase внутри цикла:
        - Vector:  ~5.8 s  (O(n^2)
        - Deque:   ~8.9 s  (O(n^2)
        - List:    ~9 ms   (O(n)

     2) erase-remove idiom:
        - Vector/Deque: ~8-9 ms (O(n)
        - List (BAD):   ~20 ms  (O(n)

     3) Специализированные методы и C++20:
        - list::remove():    ~13 ms (O(n) - встроенный метод
        - std::erase (C++20): ~8-14 ms    - Универсальный

     ИТОГ:
     - Для Vector/Deque std::erase (C++20) или erase-remove.
     - Для List std::erase (C++20) или метод .remove().
     - Ручной цикл с .erase() допустим ТОЛЬКО для List.
*/

static std::vector< int > generate_data( const std::size_t size )
{
     constexpr int seed = 42;
     std::vector< int > data;
     data.reserve( size );

     std::mt19937 rng( seed ); // NOLINT
     std::uniform_int_distribution< int > dist( 0, 9 );

     for( std::size_t i{ 0 }; i < size; ++i )
     {
          data.push_back( dist( rng ) );
     }

     return data;
}

static std::list< int > generate_list_data( const std::size_t size )
{
     auto vec = generate_data( size );
     return { vec.begin(), vec.end() };
}

static std::deque< int > generate_deque_data( const std::size_t size )
{
     auto vec = generate_data( size );
     return { vec.begin(), vec.end() };
}

int main()
{
     constexpr std::size_t N = 1'000'000;
     constexpr int dvalue = 5;

     {
          auto data = generate_data( N );

          csc::utils::timer::Timer timer( "Vector: erase in loop" );

          for( auto it = data.begin(); it != data.end(); )
          {
               if( *it == dvalue )
               {
                    it = data.erase( it );
               }
               else
               {
                    ++it;
               }
          }
     }

     {
          auto data = generate_data( N );

          csc::utils::timer::Timer timer( "Vector: erase-remove idiom" );

          auto new_end = std::remove( data.begin(), data.end(), dvalue );
          data.erase( new_end, data.end() );
     }

     {
          auto data = generate_data( N );

          csc::utils::timer::Timer timer( "Vector: std::erase (C++20)" );

          std::erase( data, dvalue );
     }

     {
          auto data = generate_list_data( N );
          csc::utils::timer::Timer timer( "List: erase in loop" );

          for( auto it = data.begin(); it != data.end(); )
          {
               if( *it == dvalue )
               {
                    it = data.erase( it );
               }
               else
               {
                    ++it;
               }
          }
     }

     {
          auto data = generate_list_data( N );
          csc::utils::timer::Timer timer( "List: data.remove()" );
          data.remove( dvalue );
     }

     {
          auto data = generate_list_data( N );
          csc::utils::timer::Timer timer( "List: erase-remove idiom (BAD)" );
          auto new_end = std::remove( data.begin(), data.end(), dvalue );
          data.erase( new_end, data.end() );
     }

     {
          auto data = generate_list_data( N );
          csc::utils::timer::Timer timer( "List: std::erase (C++20)" );
          std::erase( data, dvalue );
     }

     {
          auto data = generate_deque_data( N );
          csc::utils::timer::Timer timer( "Deque: erase in loop" );

          for( auto it = data.begin(); it != data.end(); )
          {
               if( *it == dvalue )
               {
                    it = data.erase( it ); // Инвалидирует все итераторы, но возвращает новый валидный
               }
               else
               {
                    ++it;
               }
          }
     }

     {
          auto data = generate_deque_data( N );
          csc::utils::timer::Timer timer( "Deque: erase-remove idiom" );

          auto new_end = std::remove( data.begin(), data.end(), dvalue );
          data.erase( new_end, data.end() );
     }

     {
          auto data = generate_deque_data( N );
          csc::utils::timer::Timer timer( "Deque: std::erase (C++20)" );
          std::erase( data, dvalue );
     }

     return 0;
}
