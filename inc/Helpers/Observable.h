#include <functional>  // for std::function
#include <utility>     // for std::forward and std::move
#include <map>
#include <vector>

template <typename Event>
class Observable
{
public:

  template <typename Observer>
  void registerObserver( const Event& event, Observer&& observer )
  {
    observers_[event].push_back( std::forward<Observer>( observer ) );
  }

  template <typename Observer>
  void registerObserver( Event&& event, Observer&& observer )
  {
    observers_[std::move( event )].push_back( std::forward<Observer>( observer ) );
  }

  void notify( const Event& event ) const
  {
    for( const auto& obs : observers_.at( event ) ) obs( );
  }

private:
  std::map<Event, std::vector<std::function<void( )>>> observers_;
};