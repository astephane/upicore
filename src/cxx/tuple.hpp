//
// This file is part of upicore.
//
// upicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// upicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with upicore.  If not, see <https://www.gnu.org/licenses/>.
//
#ifndef CXX_TUPLE_HPP
#define CXX_TUPLE_HPP


#include <functional>
#include <tuple>


namespace cxx
{
  template< typename T >
  using raw_ptr = std::add_pointer_t< T >;

  namespace tuple
  {
    template< typename F, typename Tuple >
    constexpr decltype( auto ) for_each( F && f, Tuple && t )
    {
      return
	std::apply(
	  [ &f ]( auto && ... e ) {
	    ( ( f( e ) ),  ... );
	  },
	  t
	  );
    }

    namespace detail
    {
      template< typename F,
		typename LHSTuple,
		typename RHSTuple,
		std::size_t ... I >
      constexpr decltype( auto )
      apply_impl( F && f,
		 LHSTuple && lhs,
		 RHSTuple && rhs,
		 std::index_sequence< I ... > )
      {
	return ( std::invoke(
		   std::forward< F >( f ),
		   std::get< I >( std::forward< LHSTuple >( lhs ) ),
		   std::get< I >( std::forward< RHSTuple >( rhs ) ) ), ... );
      }
    } // end of namespace 'detail'.

    template< typename F,
	      typename LHSTuple,
	      typename RHSTuple >
    constexpr decltype( auto )
    apply( F && f, LHSTuple && lhs, RHSTuple && rhs )
    {
      static_assert(
	std::tuple_size_v< std::remove_reference_t< RHSTuple > >
	>=
	std::tuple_size_v< std::remove_reference_t< LHSTuple > >
	);

      return detail::apply_impl(
	std::forward< F >( f ),
	std::forward< LHSTuple >( lhs ),
	std::forward< RHSTuple >( rhs ),
	std::make_index_sequence< std::tuple_size_v< std::remove_reference_t< LHSTuple > > >{}
	);
    }
  } // end of namespace 'tuple'.

} // end of namespace 'cxx'.

#endif // PIPELINE_HPP
