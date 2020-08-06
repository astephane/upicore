#include "pod.hpp"

#define TEST_MAKE_TUPLE 1

namespace detail
{

#if !TEST_MAKE_TUPLE

  /** */
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

#endif // !TEST_MAKE_TUPLE


  /** */
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


#if !TEST_MAKE_TUPLE

/** */
template< typename Enum,
	  template< Enum > typename Traits,
	  typename Indices = std::make_index_sequence< utility::count< Enum >() > >
constexpr
auto
make_pod()
{
  return detail::make_pod< Enum, Traits >( Indices{} );
}

#endif // !TEST_MAKE_TUPLE


/** */
template< typename Enum,
	  template< Enum > typename Traits,
	  typename Indices = std::make_index_sequence< utility::count< Enum >() >,
	  typename ... Args >
constexpr
auto
make_pod( Args && ... args )
{
  return detail::make_pod< Enum, Traits >( Indices{}, args ... );
}


/** */
template< typename Enum,
	  template< Enum > typename Traits,
	  typename Indices = std::make_index_sequence< utility::count< Enum >() > >
struct make
{
  static
  auto
  pod() noexcept
  {
    return detail::make_pod< Enum, Traits >( Indices{} );
  }

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

  namespace
  {

  auto foo_1 = make_pod< vector, vector_traits >( 0.0, 0.0, 0.0 );
  auto bar_1 = make_pod< vector, vector_traits >();

  auto foo_2 = make< vector, vector_traits >::pod( 0.0, 0.0, 0.0 );
  auto bar_2 = make< vector, vector_traits >::pod();

  } // namespace

} // namespace sample_pod
