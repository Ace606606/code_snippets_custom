#pragma once
#include <utility>
#include "csc/pipeline/net_packet.hpp"
#include "csc/pipeline/network_protocol_container.hpp"

namespace csc::pipeline
{

template < std::size_t MaxSize >
class TxQueueMock
{
public:
     void push( [[maybe_unused]] NetPacket<MaxSize> packet ) {}
};

template < std::size_t MaxSize = 1518 >
class Pipeline {
public:
     explicit Pipeline( NetworkProtocolContainer< MaxSize > container ) : container_( std::move( container ) ) {}

     // Точка входа для отправки пакета из приложения/генератора
     void executeSend( NetPacket<MaxSize> packet )
     {
          if (packet.length == 0)
          {
               [[unlikely]] return;
          }

          auto* link_layer = container_.template resolveById< NetworkProtocolBase< MaxSize > >( NetworkProtocolId::Ethernet );

          if ( link_layer )
          {
               auto final_packet = link_layer->send( std::move( packet ) );
               tx_queue_.push(std::move( final_packet ) );
          }
     }

     void receive() noexcept {}

     const NetworkProtocolContainer<MaxSize>& getContainer() const noexcept
     {
          return container_;
     }

private:
     NetworkProtocolContainer<MaxSize> container_;
     TxQueueMock< MaxSize > tx_queue_;
};

} // namespace csc::pipeline