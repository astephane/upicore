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
  } // end of namespace 'tuple'.

} // end of namespace 'cxx'.

#endif // PIPELINE_HPP
