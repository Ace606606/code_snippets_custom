#pragma once

#ifdef USE_SPDLOG
     #include <spdlog/spdlog.h>
#endif

#include <fmt/format.h> 
#include <utility>

namespace ext::sys::utils::logger
{

template< typename... Args >
using format_str_t = fmt::format_string< Args... >;

inline void init_logger()
{
#ifdef USE_SPDLOG

     spdlog::set_pattern( "[%Y-%m-%d %H:%M:%S] [%^%l%$] %v" );
     spdlog::set_level( spdlog::level::debug );

#endif
}

template< typename... Args >
inline void debug( format_str_t< Args... > fmt_str, Args&&... args )
{
#ifdef USE_SPDLOG
     spdlog::debug( fmt_str, std::forward< Args >( args )... );
#else
     fmt::print(stdout, "[DEBUG] {}\n", fmt::format(fmt_str, std::forward<Args>(args)...));
     fflush(stdout);
#endif
}

template< typename... Args >
inline void info( format_str_t< Args... > fmt_str, Args&&... args )
{
#ifdef USE_SPDLOG
     spdlog::info( fmt_str, std::forward< Args >( args )... );
#else
     fmt::print(stdout, "[INFO] {}\n", fmt::format(fmt_str, std::forward<Args>(args)...));
     fflush(stdout);
#endif
}

template< typename... Args >
inline void error( format_str_t< Args... > fmt_str, Args&&... args )
{
#ifdef USE_SPDLOG
     spdlog::error( fmt_str, std::forward< Args >( args )... );
#else
     fmt::print(stdout, "[ERROR] {}\n", fmt::format(fmt_str, std::forward<Args>(args)...));
     fflush(stdout);
#endif
}

} // namespace ext::sys::utils::logger
