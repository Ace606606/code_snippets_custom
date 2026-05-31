#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "csc/pipeline/network_protocol_base.hpp"

namespace csc::pipeline
{

template < std::size_t MaxSize >
class NetworkProtocolContainer {
public:
     NetworkProtocolContainer() = default;

     void registerProtocol( std::unique_ptr<NetworkProtocolBase<MaxSize>> protocol )
     {
          if ( protocol )
          {
               protocols_.push_back( std::move( protocol ) );
          }
     }

     template < typename TProto >
     TProto* resolveById( NetworkProtocolId id ) const
     {
          auto it = std::find_if( protocols_.begin(), protocols_.end(),
               [ id ]( const auto& proto ) { return proto->getId() == id; } );

          if ( it != protocols_.end() )
          {
               return static_cast<TProto*>(it->get());
          }
          return nullptr;
     }

private:
     std::vector< std::unique_ptr< NetworkProtocolBase< MaxSize > > > protocols_;
};

} // namespace csc::pipeline