#include "pod.hpp"


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
    return utility::detail::make_pod_tuple< Enum, Traits >( Indices{} );
  }

  template< typename ... Args >
  static
  auto
  pod( Args && ... args )
  {
    return utility::detail::make_pod_tuple< Enum, Traits >( Indices{}, args ... );
  }
};


namespace sample_pod
{

  namespace
  {

    auto foo_1 = utility::make_pod_tuple< vector, vector_traits >( 0.0, 0.0, 0.0 );
    auto bar_1 = utility::make_pod_tuple< vector, vector_traits >();

    auto foo_2 = make< vector, vector_traits >::pod( 0.0, 0.0, 0.0 );
    auto bar_2 = make< vector, vector_traits >::pod();

  } // namespace

} // namespace sample_pod
