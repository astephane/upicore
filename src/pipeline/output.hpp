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


#include "pipeline/tuple_data.hpp"

#include <memory>


namespace pipeline
{

  template< typename ... T >
  struct output : public tuple_data< std::shared_ptr, T ... >
  {
    using source_pointer = port_interface::source_pointer;

    output( source_pointer p ) :
      tuple_data< std::shared_ptr, T ... >( std::make_shared< port< T > >( p ) ... )
    {}

    ~output()
    {
      cxx::tuple::for_each(
	[]( auto && port ) {
	  assert( port );
	  port->source = nullptr;
	},
	this->data
	);
    }

    template< typename F >
    auto
    downstream( F && f )
    {
      return
	cxx::tuple::for_each(
	  [ &f ]( auto && port ) {
	    f( port );
	  },
	  this->data
	  );
    }
  };

} // end of namespace 'pipeline'.

#endif // PIPELINE_OUTPUT_HPP
