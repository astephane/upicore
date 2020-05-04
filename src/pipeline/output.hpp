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
#ifndef PIPELINE_OUTPUT_HPP
#define PIPELINE_OUTPUT_HPP


#include "cxx/tuple.hpp"
#include "pipeline/port.hpp"

#include <memory>


namespace pipeline
{

  template< typename ... T >
  struct output
  {
    using source_pointer = port_interface::source_pointer;

    output( source_pointer p ) :
      data( std::make_shared< port< T > >( p ) ...  )
    {}

    ~output()
    {
      cxx::tuple::for_each(
	[]( auto && port ) {
	  assert( port );
	  port->source = nullptr;
	},
	data
	);
    }

    template< std::size_t I >
    auto &
    get() noexcept
    {
      return std::get< I >( data );
    };

    template< typename F >
    auto
    downstream( F && f )
    {
      return
	cxx::tuple::for_each(
	  [ &f ]( auto && port ) {
	    f( port );
	  },
	  data
	  );
    }

  private:
    using value_type = std::tuple< std::shared_ptr< port< T > > ... >;

    value_type data;
  };

} // end of namespace 'pipeline'.

#endif // PIPELINE_OUTPUT_HPP
