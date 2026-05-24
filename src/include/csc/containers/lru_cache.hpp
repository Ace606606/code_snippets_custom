#include <list>
#include <unordered_map>
#include <cstdint>
#include <optional>

namespace csc::containers
{

template< typename Key, typename Value >
class LruCache
{
public:
     explicit LruCache( uint64_t capacity ) : capacity_( capacity )
     {
          key_.reserve( capacity );
     }

     std::optional< Value > get( Key key )
     {
          if( key_.contains( key ) )
          {
               auto it = key_[ key ];
               cache_.splice( cache_.begin(), cache_, it );
               return it.second;
          }
          return std::nullopt;
     }

     void put( Key key, Value value )
     {
          if( key_.contains( value ) )
          {
               auto it = key_[ key ];
               cache_.splice( cache_.begin(), cache_, it );
               key_[ key ] = cache_.begin();
               return;
          }

          if( size() <= capacity() )
          {
               cache_.push_front( { key, value } );
               key_[ key ] = cache_.front();
               return;
          }

          auto pair = cache_.back();
          cache_.pop_back();
          key_.erase( pair.first );
          cache_.push_front( { key, value } );
          key_[ key ] = cache_.begin();
     }

     uint64_t capacity() const noexcept
     {
          return capacity_;
     }
     
     uint64_t size() const noexcept
     {
          return key_.size();
     }
     
     void clear() noexcept
     {
          key_.clear();
          cache_.clear();
     }

     bool empty() const noexcept
     {
          return key_.empty();
     }

     void erase( Key key )
     {
          if( key_.contains( key ) )
          {
               auto it = key_[ key ];
               key_.erase( key );
               cache_.erase( it );
          }
     }
     bool contains( const Key& key )
     {
          return key_.contains( key );
     }


private:
     uint64_t capacity_{};
     using CacheList = std::list< std::pair< Key, Value > >;
     CacheList cache_;
     std::unordered_map< Key, typename CacheList::iterator > key_;
};

} // namespace csc::containers