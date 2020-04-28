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

  struct process_interface
  {
    virtual ~process_interface() = default;

    virtual void update_output_information() = 0;
    // virtual void update() = 0;
  };


  template< typename Out >
  struct in_process : public virtual process_interface
  {
    in_process() : out( this ) {}

    void
    update_output_information() override
    {
      std::cout
	<< "I- 0x" << std::hex << this << " "
	<< typeid( this ).name() << "::upate_output_information()" << std::endl;

      // No upstream forwarding.

      // Downstream tail-recursion.
      generate_output_information();
    }

    Out out;

  private:
    virtual void generate_output_information() = 0;
  };


  template< typename In >
  struct out_process : public virtual process_interface
  {
    void
    update_output_information() override
    {
      std::cout
	<< "-O 0x" << std::hex << this << " "
	<< typeid( this ).name() << "::upate_output_information()" << std::endl;

      in.upstream(
      	[]( auto && port) {
	  std::cout << "out_process::uoi()" << std::endl;

      	  assert( port );
      	  assert( port->source );

      	  port->source->update_output_information();
      	}
      	);
    }

    In in;
  };


  template< typename In,
	    typename Out >
  struct process : public in_process< Out >,
		   public out_process< In >
  {
    void update_output_information() override
    {
      std::cout
      	<< "IO 0x" << std::hex << this << " "
      	<< typeid( this ).name() << "::upate_output_information()" << std::endl;

      // Upstream recursion.
      this->out_process< In >::update_output_information();

      // Downstream tail-recursion.
      this->in_process< Out >::update_output_information();
    }

  private:
    void
    generate_output_information() override
    {
      std::cout
	<< "0x" << std::hex << this << " "
	<< typeid( this ).name() << "::generate_output_information()" << std::endl;

      auto primary_input = this->in.primary().lock();

      assert( primary_input );

      this->out.downstream(
	[ &primary_input ]( auto && port ) {
	  std::cout << "out_process::goi()" << std::endl;
	  assert( port );

	  port->data.set_information( primary_input->data.information() );
	}
	);
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
