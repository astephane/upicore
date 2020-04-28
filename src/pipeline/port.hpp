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
#ifndef PIPELINE_PORT_HPP
#define PIPELINE_PORT_HPP

#include "cxx/memory.hpp"


#include <cassert>
#include <stdexcept>


namespace pipeline
{

  class process;


  template< typename Data >
  struct port
  {
    using value_type = Data;

    using source_pointer_type = cxx::raw_ptr< process >;

    port( source_pointer_type s ) :
      source( s )
    {
      assert( source );

      if( !source )
	throw std::invalid_argument( "unexpected nullptr source." );
    }

    void
    update()
    {
      assert( source );

      // source->update_output_information();
      // source->propagate_requested_region();
      // source->update_output_data();
    }

    source_pointer_type source;
    Data data;
  };

} // end of namespace 'pipeline'.

#endif // PIPELINE_PORT_HPP
