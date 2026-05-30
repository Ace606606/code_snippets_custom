#pragma once
#include <functional>
#include <array>
#include <cstdint>

namespace csc::patterns
{

struct Arp
{

};

template < typename T >
class Packet
{
public:
     explicit Packet( T data ) : data( data ) {}
private:
     T data;
};

// using CCallback = void ( * )( const Packet&, void* );

// struct CStrategy
// {
//      CCallback callback;
//      void* user_data;

//      void execute( const Packet& packet ) const
//      {
//           if ( callback != nullptr )
//           {
//                callback( packet, user_data );
//           }
//      }
// };

// struct StdFunctionStrategy
// {
//      std::function< void( const Packet& ) > callback;

//      void execute( const Packet& packet ) const
//      {
//           if ( callback != nullptr )
//           {
//                callback( packet );
//           }
//      }
// };

// struct ProcessingResult
// {
//      uint64_t checksum = 0;
//      bool status = false;
// };

// inline ProcessingResult process_with_nrvo( const Packet& packet, bool branch_condition )
// {
//      ProcessingResult res;

//      if ( branch_condition )
//      {
//           res.checksum += packet.data[0] + 42;
//           res.status = true;
//      }
//      else
//      {
//           res.checksum += packet.data[63] + 13;
//           res.status = false;
//      }

//      return res;
// }

template< typename F >
class ProcessSend
{
     ProcessSend() = default;

     void setProvider( F f ) noexcept
     {
          provider_ = f;
     }

     Packet executeSend( Packet packet )
     {

     }
private:
     F provider_;
};

} // namespace csc::patterns