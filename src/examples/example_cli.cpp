#include <string>
#include <iostream>
#include <vector>

#include "CLI/CLI.hpp"
#include "csc/utils/base_cli.hpp"

using BaseCli = csc::utils::cli::BaseCli;

class FullExampleCli : public BaseCli
{
public:
     explicit FullExampleCli( const std::string& app_name = "", const std::string& description = "" ) : BaseCli(app_name, description)
     {
          auto& cli_app = get_app();
          
          // Настройка самого приложения
          cli_app.require_subcommand( 0, 1 );
          cli_app.footer( "Example footer: usage hints or license info" );
          // Группировка основных параметров
          auto* main_group = cli_app.add_option_group( "Main", "Primary settings" );

          main_group->add_option( "-i,--int", int_val, "An integer" )->default_val( 999 );
          // Перечисления (Enums / Sets)
          main_group->add_option( "-p,--priority", priority, "Task priority" )
                    ->check( CLI::IsMember( {"low", "medium", "high" } ) );
          // Работа с файлами и путями + Валидаторы
          cli_app.add_option( "-f,--file", path, "Config file" )
                    ->check( CLI::ExistingFile )
                    ->group( "Files" );
          // Продвинутые типы: Pairs (например, для маппинга портов 80:8080)
          cli_app.add_option( "--port-map", port_map, "Map host port to container port" )
                    ->type_name( "UINT:UINT" );
          // Логические зависимости (Exclude / Needs)
          auto* secret_opt = cli_app.add_option( "--secret", secret_key, "Secret key for encryption" );
          auto* token_opt = cli_app.add_option( "--token", token, "Auth token" );
          secret_opt->excludes( token_opt ); // Нельзя использовать и секрет, и токен сразу
          // Подкоманда (Subcommand)
          auto* sub = cli_app.add_subcommand( "send", "Send data to server" );
          sub->add_option( "-t,--target", target_url, "Destination url" )->required();
          sub->add_flag( "--retry", retry, "Retry on failure" );
          // Callback подкоманды: выполнится только если ввели "send"
          sub->callback( [this](){
               std::cout << ">>> Subcommand 'send' triggered to: " << target_url << '\n';
          } );
          cli_app.add_option( "--even", even_num, "An even number" )
                    ->check( []( const std::string &input ){
                         int n = std::stoi( input );
                         if ( n % 2 != 0 ) 
                         {
                              return std::string( "Numbrer must be even" );
                         }
                         return std::string();
                    } );

          

          auto* group = cli_app.add_option_group( "Advanced", "Expert settings" );
          group->add_option( "--ratio", ratio, "Float ratio" )->check( CLI::Range( 0.0, 1.0 ) );
     }

     FullExampleCli( const FullExampleCli& ) = delete;
     FullExampleCli& operator=( const FullExampleCli& ) = delete;
     FullExampleCli( FullExampleCli&& ) = default;
     FullExampleCli& operator=( FullExampleCli&& ) = default;

     ~FullExampleCli() override = default;

     void print_info() const
     {
          std::cout << "--- Global Settings ---\n";
          std::cout << "Int: " << int_val << "\nPath: " << path << "\nPriority: " << priority << "\n";
          if ( port_map.size() >= 2 ) {
               std::cout << "Port Map: " << port_map[0] << " -> " << port_map[1] << "\n";
          }
          if ( is_verbose() )
          {
               std::cout << "Verbose mode: ON\n";
          }
     }

private:
     int int_val{};
     std::string path;
     std::string priority{ "low" };
     std::vector< int > port_map;
     std::string secret_key, token;

     std::string target_url;
     bool retry{false};
     int even_num{};
     float ratio{};
};

int main( int argc, char** argv )
{
     FullExampleCli cli( "example", "example_cli" );
     if ( cli.parse( argc, argv ) )
     {
          cli.print_info();
     }
     return 0;
}