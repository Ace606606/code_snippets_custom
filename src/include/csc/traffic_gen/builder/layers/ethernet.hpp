#pragma once
#include <cstddef>
#include <cstdint>

#include "csc/traffic_gen/stack/config.hpp"

namespace csc::traffic_gen::layers
{
size_t build_ethernet(
     uint8_t* buf,
     const stack::EthernetConfig& cfg,
     uint16_t ethertype
);
} // namespace csc::traffic_gen::layers