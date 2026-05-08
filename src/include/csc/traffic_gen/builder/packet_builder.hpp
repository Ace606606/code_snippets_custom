#pragma once
#include <cstdint>
#include <vector>
#include <cstddef>
#include <csc/traffic_gen/stack/config.hpp>

namespace csc::traffic_gen::builder
{

struct PacketOffsets
{
     size_t l3_src_ip{};
     size_t l3_dst_ip{};

     size_t l4_src_port{};
     size_t l4_dst_port{};

     size_t tcp_seq{};
     size_t tcp_ack{};
};

struct PacketTemplate
{
     std::vector< uint8_t > bytes;
     PacketOffsets offsets;
};

class PacketBuilder
{
public:
     static PacketTemplate build( const stack::PacketConfig& cfg );
};

} // namespace csc::traffic_gen::builder