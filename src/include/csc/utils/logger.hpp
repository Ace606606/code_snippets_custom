#pragma once

#include "spdlog/common.h"
#ifdef USE_SPDLOG
#include <spdlog/spdlog.h>
#endif

#include <fmt/format.h>
#include <utility>

namespace csc::utils::logger
{

enum class LogLevel
{
     trace    = 0,
     debug    = 1,
     info     = 2,
     warn     = 3,
     err      = 4,
     critical = 5,
     off      = 6
};

inline LogLevel current_level{ LogLevel::debug };

template< typename... Args >
using format_str_t = fmt::format_string< Args... >;

#ifdef USE_SPDLOG
inline spdlog::level::level_enum to_spdlog_level( LogLevel level )
{
     return static_cast< spdlog::level::level_enum >( level );
}
#endif

inline void init_logger( LogLevel level = LogLevel::debug )
{
     current_level = level;
#ifdef USE_SPDLOG
     spdlog::set_pattern( "[%Y-%m-%d %H:%M:%S] [%^%l%$] %v" );
     spdlog::set_level( to_spdlog_level( level ) );

#endif
}

template< typename... Args >
inline void debug( format_str_t< Args... > fmt_str, Args&&... args )
{
#ifdef USE_SPDLOG
     spdlog::debug( fmt_str, std::forward< Args >( args )... );
#else
     fmt::print( stdout, "[DEBUG] {}\n", fmt::format( fmt_str, std::forward< Args >( args )... ) );
     fflush( stdout );
#endif
}

template< typename... Args >
inline void info( format_str_t< Args... > fmt_str, Args&&... args )
{
#ifdef USE_SPDLOG
     spdlog::info( fmt_str, std::forward< Args >( args )... );
#else
     fmt::print( stdout, "[INFO] {}\n", fmt::format( fmt_str, std::forward< Args >( args )... ) );
     fflush( stdout );
#endif
}

template< typename... Args >
inline void error( format_str_t< Args... > fmt_str, Args&&... args )
{
#ifdef USE_SPDLOG
     spdlog::error( fmt_str, std::forward< Args >( args )... );
#else
     fmt::print( stdout, "[ERROR] {}\n", fmt::format( fmt_str, std::forward< Args >( args )... ) );
     fflush( stdout );
#endif
}

template< typename... Args >
inline void warn( format_str_t< Args... > fmt_str, Args&&... args )
{
#ifdef USE_SPDLOG
     spdlog::warn( fmt_str, std::forward< Args >( args )... );
#else
     fmt::print( stdout, "[WARNING] {}\n", fmt::format( fmt_str, std::forward< Args >( args )... ) );
     fflush( stdout );
#endif
}

} // namespace csc::utils::logger
