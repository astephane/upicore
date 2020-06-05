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
  struct process_interface
  {
    virtual ~process_interface() = default;

    // virtual void update() = 0;

    virtual void update_output_information() = 0;
    virtual void update_output_data() = 0;
  };


  struct in_process_interface : public virtual process_interface
  {
   protected:
    virtual void generate_output_information() = 0;
  };


  struct out_process_interface : public virtual process_interface
  {
  };


  namespace port_interface
  {
    using source_pointer = cxx::raw_ptr< in_process_interface >;
  }


  template< typename Data >
  struct port
  {
    using value_type = Data;

    using source_pointer = port_interface::source_pointer;

    port( source_pointer s ) :
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

      source->update_output_information();
      // source->propagate_requested_region();

#if 1
      // source->update_output_data( data );
#else
      source->update_output_data();
#endif
    }

    source_pointer source;
    Data data;
  };

} // end of namespace 'pipeline'.

#endif // PIPELINE_PORT_HPP
