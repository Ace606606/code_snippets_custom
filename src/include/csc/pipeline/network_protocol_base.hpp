#pragma once
#include <cstdint>
#include "csc/pipeline/net_packet.hpp"

namespace csc::pipeline
{

enum class NetworkProtocolId : uint16_t
{
     Ethernet = 1,
     Arp      = 2,
     Ipv4     = 3
};

template < std::size_t MaxSize >
class NetworkProtocolBase
{
public:
     virtual ~NetworkProtocolBase() = default;

     [[nodiscard]] virtual NetworkProtocolId getId() const noexcept = 0;

     virtual NetPacket< MaxSize > send( NetPacket< MaxSize > packet ) = 0;
};

} // namespace csc::pipeline