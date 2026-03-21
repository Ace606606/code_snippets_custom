#pragma once

#include <string>
#include <memory>

#include <CLI/CLI.hpp>

namespace csc::utils::cli
{

class BaseCli
{
public:
     explicit BaseCli( const std::string& app_name, const std::string& description = "" )
          : app( std::make_unique< CLI::App >( description, app_name ) )
     {
          init_config();
          app->add_flag( "-v,--verbose", verbose, "Enable verbose logging" );
     }

     BaseCli( const BaseCli& ) = delete;
     BaseCli& operator=( const BaseCli& ) = delete;
     BaseCli( BaseCli&& ) = default;
     BaseCli& operator=( BaseCli&& ) = default;

     virtual ~BaseCli() = 0;

     bool is_verbose() const
     {
          return verbose;
     }

     bool parse( int argc, char** argv )
     {
          try
          {
               app->parse( argc, argv );
               return true;
          }
          catch ( const CLI::ParseError& e )
          {
               return ( app->exit( e ) == 0 );
          }

     }

protected:
     CLI::App& get_app()
     {
          return *app;
     }

private:
     std::unique_ptr< CLI::App > app;
     bool verbose{ false };

     void init_config()
     {
          app->get_formatter()->column_width( 60 );
     }
};

inline BaseCli::~BaseCli() = default;

} // namespace csc::utils::cli
