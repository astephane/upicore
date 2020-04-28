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
#ifndef PIPELINE_PROCESS_HPP
#define PIPELINE_PROCESS_HPP


// #include "cxx.hpp"
#include "input.hpp"
#include "output.hpp"

// #include <cassert>
// #include <iostream>
// #include <memory>
// #include <stdexcept>
// #include <tuple>
// #include <type_traits>


namespace pipeline
{

  struct process
  {
    virtual ~process() = default;

    virtual void update_output_information() = 0;
    // virtual void update() = 0;
  };


  template< typename Out >
  struct in_process : public virtual process
  {
    in_process() : out( this ) {}

    void update_output_information() override
    {
      std::cout
	<< "0x" << std::hex << this
	<< typeid( this ).name() << "::upate_output_information()" << std::endl;

      // No upstream forwarding.

      out.downstream(
	[]( auto && port ) {
	  assert( port );
	  // port->data.set_info( in.get_primary().info() );
	}
	);
    }

    Out out;
  };


  template< typename In >
  struct out_process : public virtual process
  {
    void update_output_information() override
    {
      std::cout << typeid( this ).name() << "::upate_output_information()" << std::endl;

      in.upstream(
      	[]( auto && port) {
      	  assert( port );
      	  assert( port->source );

      	  port->source->update_output_information();
      	}
      	);

      // in.update_output_information();


    }

    In in;
  };


  template< typename In,
	    typename Out >
  struct filter : public in_process< Out >,
		  public out_process< In >
  {
    void update_output_information() override
    {
      std::cout << typeid( this ).name() << "::upate_output_information()" << std::endl;

      this->out_process< In >::update_output_information();
      this->in_process< Out >::update_output_information();
    }
  };


  template< typename ... Outputs >
  struct reader : public in_process< output< Outputs ... > >
  {
  };


  template< typename ... Inputs >
  struct writer : public out_process< input< Inputs ... > >
  {
  };

} // end of pipeline.

#endif // PIPELINE_PROCESS_HPP
