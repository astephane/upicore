#include "pod.hpp"

namespace detail
{

  template< typename Enum,
	    template< Enum > typename Traits,
	    std::size_t ... I >
  auto make_pod( std::index_sequence< I ... > )
  {
    return
      std::tuple<
	typename Traits<
	  static_cast< Enum >( I )
	  >::element_type ...
      >();
  }

  template< typename Enum,
	    template< Enum > typename Traits,
	    typename ... Args,
	    std::size_t ... I >
  auto make_pod( std::index_sequence< I ... >, Args && ... args )
  {
    return
      std::tuple<
	typename Traits<
	  static_cast< Enum >( I )
	  >::element_type ...
      >( args ... );
  }

} // namespace detail

template< typename Enum,
	  template< Enum > typename Traits,
	  typename Indices = std::make_index_sequence< utility::count< Enum >() > >
auto
make_pod()
{
  return detail::make_pod< Enum, Traits >( Indices{} );
}


template< typename Enum,
	  template< Enum > typename Traits,
	  typename Indices = std::make_index_sequence< utility::count< Enum >() > >
struct make
{
  template< typename ... Args >
  static
  auto
  pod( Args && ... args )
  {
    return detail::make_pod< Enum, Traits >( Indices{}, args ... );
  }
};

namespace sample_pod
{

  auto foo = make< vector, vector_traits >::pod( 0.0, 0.0, 0.0 );
  auto bar = make< vector, vector_traits >::pod();
} // namespace sample_pod
