#include <functional>  // for std::function
#include <utility>     // for std::forward and std::move
#include <map>
#include <vector>
#include <algorithm>

typedef std::pair< std::string, std::function<void( )> > ObserverPair;

template <typename Event>
class Observable
{
public:

  template <typename Observer>
  void registerObserver( const Event& event, Observer&& observer, std::string identifier )
  {
    observers_[event].push_back( std::make_pair( identifier, std::forward<Observer>( observer ) ) );
  }

  template <typename Observer>
  void registerObserver( Event&& event, Observer&& observer, std::string identifier )
  {
    observers_[std::move( event )]
      .push_back( std::make_pair( identifier, std::forward<Observer>( observer ) ) );
  }

  void removeObserver( std::vector< Event > events, std::string identifier )
  {
    for( const Event& event : events )
    {
      observers_[event]
        .erase( std::remove_if( observers_[event].begin( ),
                                observers_[event].end( ),
                                [&]( const ObserverPair obs )
                                { return obs.first == identifier; } ),
                observers_[event].end( ) );
    }
  }

  void notify( const Event& event ) const
  {
    for( const ObserverPair obs : observers_.at( event ) ) obs.second();
  }

private:
  std::map<Event, std::vector< ObserverPair >> observers_;
};