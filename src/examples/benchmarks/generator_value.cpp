#include <future>
#include <numeric>
#include <string>
#include <thread>
#include <variant>
#include <vector>

#include "csc/utils/generator_value.hpp"
#include "csc/utils/logger.hpp"
#include "csc/utils/timer.hpp"

namespace examples
{

constexpr size_t kSizeElement = 1000000000;
constexpr size_t kRangeMin = 0;
constexpr size_t kRangeMax = 10;

namespace random = csc::utils::random;
namespace log = csc::utils::logger;
using Timer = csc::utils::timer::Timer;

void example_generator()
{

     {
          using Gen32 = std::unique_ptr< random::GeneratorBase< uint32_t > >;
          using Gen64 = std::unique_ptr< random::GeneratorBase< uint64_t > >;
          using AnyGen = std::variant< Gen32, Gen64 >;

          std::vector< AnyGen > gens;
          gens.emplace_back( random::make_generator_base< uint64_t >( 1 ) );
          gens.emplace_back( random::make_generator_base< uint64_t, random::GeneratorXor< uint64_t > >( 1 ) );
          gens.emplace_back( random::make_generator_base< uint64_t, random::GeneratorSTD< uint64_t > >( 1 ) );

          for( auto& generator : gens )
          {
               std::visit(
                    []( auto& gen )
                    {
                         std::string label = "Visit(Base): GeneratorBase < " + std::string( gen->getName() ) + " >";
                         gen->setRange( kRangeMin, kRangeMax );
                         uint64_t accumalate{};
                         {
                              Timer t( label );
                              for( size_t i{}; i < kSizeElement; ++i )
                              {
                                   accumalate += gen->next();
                              }
                         }
                         log::info( "Total: {}", accumalate );
                    },
                    generator );
          }
     }

     {
          auto gen = random::make_generator_base< uint64_t >( 1 );
          gen->setRange( kRangeMin, kRangeMax );
          std::string label = "GeneratorBase < " + std::string( gen->getName() ) + " >";
          uint64_t accumalate{};
          {
               Timer t( label );
               for( size_t i{}; i < kSizeElement; ++i )
               {
                    accumalate += gen->next();
               }
          }
          log::info( "Total: {}", accumalate );
     }

     {
          auto gen = random::make_generator< random::GeneratorLCG< uint64_t > >( 1 );
          gen->setRange( kRangeMin, kRangeMax );
          uint64_t accumalate{};
          {
               Timer t( gen->getName() );
               for( size_t i{}; i < kSizeElement; ++i )
               {
                    accumalate += gen->next();
               }
          }
          log::info( "Total: {}", accumalate );
     }

     {
          auto gen = random::make_generator_base< uint64_t, random::GeneratorXor< uint64_t > >( 1 );
          gen->setRange( kRangeMin, kRangeMax );
          uint64_t accumalate{};
          {
               Timer t( gen->getName() );
               for( size_t i{}; i < kSizeElement; ++i )
               {
                    accumalate += gen->next();
               }
          }
          log::info( "Total: {}", accumalate );
     }

     {
          auto gen = random::make_generator_base< uint64_t, random::GeneratorSTD< uint64_t > >( 1 );
          gen->setRange( kRangeMin, kRangeMax );
          uint64_t accumalate{};
          {
               Timer t( gen->getName() );
               for( size_t i{}; i < kSizeElement; ++i )
               {
                    accumalate += gen->next();
               }
          }
          log::info( "Total: {}", accumalate );
     }
}

void example_multithread()
{
     const size_t num_threads = std::thread::hardware_concurrency();
     const size_t elements_per_thread = kSizeElement / num_threads;

     {
          Timer t( "Multithread LCG" );
          std::vector< std::future< uint64_t > > futures;

          for( size_t i{}; i < num_threads; ++i )
          {
               futures.emplace_back( std::async( std::launch::async,
                    [ elements_per_thread, i ]()
                    {
                         auto gen = random::make_generator< random::GeneratorLCG< uint64_t > >( i + 1 );
                         gen->setRange( kRangeMin, kRangeMax );
                         uint64_t accumalate{};
                         for( size_t j{}; j < elements_per_thread; ++j )
                         {
                              accumalate += gen->next();
                         }
                         return accumalate;
                    } ) );
          }

          uint64_t total_accumalate{ 0 };
          for ( auto& f : futures )
          {
               total_accumalate += f.get();
          }
          log::info( "Total: {}", total_accumalate );
     }
}

} // namespace examples

int main()
{
     using namespace examples;
     //example_generator();
     example_multithread();
     return 0;
}