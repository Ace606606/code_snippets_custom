#include <cstring>
#include <arpa/inet.h>
#include <span>
#include <algorithm>

#include "csc/traffic_gen/builder/layers/ethernet.hpp"

namespace csc::traffic_gen::layers
{
size_t build_ethernet(
     uint8_t* buf,
     const stack::EthernetConfig& cfg,
     uint16_t ethertype
)
{
     std::span< uint8_t > buffer_view( buf, 14 );

     auto dst_part = buffer_view.subspan( 0, 6 );
     auto src_part = buffer_view.subspan( 6, 6 );
     auto type_part = buffer_view.subspan( 12, 2 );

     std::copy( cfg.dst_mac.cbegin(), cfg.dst_mac.cend(), dst_part.begin() );
     std::copy( cfg.src_mac.cbegin(), cfg.src_mac.cend(), src_part.begin() );

     uint16_t type = htons( ethertype );
     std::memcpy(type_part.data(), &type, sizeof( type ) );

     return 14;
}
} // namespace csc::traffic_gen::layers