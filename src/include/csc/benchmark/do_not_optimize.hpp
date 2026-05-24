#pragma once

namespace csc::benchmark
{

// ( "код" : выходные : входные : разрушаемые_регистры )
template <typename Tp>
inline void DoNotOptimize( Tp const& value ) {
     asm volatile("" : : "r,m"(value) : "memory");
}

}