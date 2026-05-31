#include <string>
#include <vector>
#include <cstdint>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <condition_variable>

#include "csc/utils/logger.hpp"


namespace csc::examples::demo
{

namespace log = csc::utils::logger;

struct PacketBuffer
{
     std::string data;
};

struct RingDescriptor
{
     PacketBuffer* packet_buffer_address{};
     uint32_t packet_length{};
     std::atomic< bool > hw_ownership;
};

constexpr uint64_t RING_SIZE{ 4 };
constexpr uint64_t RING_MASK{ RING_SIZE - 1 };
constexpr uint64_t PACKETS{ 100 };
constexpr std::chrono::milliseconds CPU_SLEEP( 150 );

std::vector< RingDescriptor > rx_ring{ RING_SIZE };
std::vector< PacketBuffer > rx_buffers{ RING_SIZE };
bool is_running{ true };

std::mutex interrupt_mutex;
std::condition_variable interrupt_cv;
bool interrupt_raised{ false };
bool interrupts_enabled{ true };
std::atomic< bool > napi_in_polling{ false };

void network_card_emulation()
{
     log::info( "Run network_card_emulation" );
     uint64_t packet_counter{ 1 };
     uint64_t write_index{ 0 };

     while( packet_counter <= PACKETS )
     {
          if( rx_ring[ write_index ].hw_ownership.load( std::memory_order_acquire ) )
          {
               auto* buffer = rx_ring[ write_index ].packet_buffer_address;
               buffer->data = "RAW_DATA_OF_PACKET_" + std::to_string( packet_counter );
               rx_ring[ write_index ].packet_length = static_cast< uint32_t >( buffer->data.size() );

               
               log::info(
                    "[NIC] Packet {}, written to slot {} via DMA",
                    packet_counter, write_index
               );

               rx_ring[ write_index ].hw_ownership.store( false, std::memory_order_release );
               write_index = ( write_index + 1 ) & RING_MASK;

               {
                    std::lock_guard< std::mutex > lock( interrupt_mutex );
                    if( interrupts_enabled && !napi_in_polling.load( std::memory_order_relaxed ) )
                    {
                         log::debug( "[NIC] Hard intterrupt raised for packet {}", packet_counter );
                         interrupt_raised = true;
                         interrupt_cv.notify_one();
                    }
                    else
                    {
                         log::debug( "[NIC] Packet placed silntly (NAPI is polling)", packet_counter );
                    }
               }

               ++packet_counter;
          }
          else
          {
               log::warn(
                    "[NIC] The ring is full! Packet {} DROPPED",
                    packet_counter
               );
          }

          if ( packet_counter % 6 == 0 )
          {
               std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
          }
          else
          {
               std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
          }
     }

     std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
     is_running = false;
     std::lock_guard< std::mutex > lock( interrupt_mutex );
     interrupt_raised = true;
     interrupt_cv.notify_one();
}

void cpu_processing()
{
     log::info( "Run cpu_processong (Polling mode/NAPI mode)" );
     uint64_t read_index{ 0 };

     while( is_running )
     {
          if( !napi_in_polling.load( std::memory_order_acquire ) )
          {
               std::unique_lock< std::mutex > lock( interrupt_mutex );
               interrupt_cv.wait( lock, [] { return interrupt_raised || !is_running; } );

               if( !is_running )
               {
                    break;
               }

               log::info( "[CPU] Context switch: interrupt received! Switch to NAPI polling mode..." );

               interrupt_raised = false;
               interrupts_enabled = false;
               napi_in_polling.store( true, std::memory_order_relaxed );
          }

          log::info( "[NAPI] Starting poll cycle..." );

          uint32_t packet_processed{ 0 };
          constexpr uint32_t NAPI_WEIGHT{ 2 };

          while( packet_processed < NAPI_WEIGHT )
          {
               if( !rx_ring[ read_index ].hw_ownership.load( std::memory_order_acquire ) )
               {
                    auto* buffer = rx_ring[ read_index ].packet_buffer_address;

                    log::info(
                         "[CPU] [NAPI pool] Processing slot {} (Len: {} Data: {})",
                         read_index,
                         rx_ring[ read_index ].packet_length,
                         buffer->data
                    );

                    std::this_thread::sleep_for( CPU_SLEEP );

                    buffer->data.clear();
                    rx_ring[ read_index ].packet_length = 0;
                    rx_ring[ read_index ].hw_ownership.store( true, std::memory_order_release );
                    read_index = ( read_index + 1 ) & RING_MASK;
                    ++packet_processed;
               }
               else
               {
                    break;
               }
          }

          log::info( "[NAPI] Pool cycly finished. Processed {} packets", packet_processed );

          if( packet_processed < NAPI_WEIGHT )
          {
               log::info( "[CPU] Ring is empty. Switching back to interrupt mode" );
               std::lock_guard< std::mutex > lock( interrupt_mutex );
               interrupts_enabled = true;
               napi_in_polling.store( false, std::memory_order_relaxed );
          }
          else
          {
               std::this_thread::yield();
          }
     }
}

} // namespace csc::examples::demo

namespace demo = csc::examples::demo;

int main()
{
     demo::log::init_logger( demo::log::LogLevel::debug );

     for( uint64_t i{ 0 }; i < demo::RING_SIZE; ++i )
     {
          demo::rx_ring[ i ].packet_buffer_address = &demo::rx_buffers[ i ];
          demo::rx_ring[ i ].packet_length = 0;
          demo::rx_ring[ i ].hw_ownership.store( true );
     }

     std::thread nic_thread( demo::network_card_emulation );
     std::thread cpu_thread( demo::cpu_processing );

     nic_thread.join();
     cpu_thread.join();

     return 0;
}