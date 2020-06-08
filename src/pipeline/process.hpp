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
#include "cxx/trace.hpp"
#include "pipeline/in_process.hpp"
#include "pipeline/out_process.hpp"


namespace pipeline
{

#define PROCESS_UPDATE_OUTPUT( name )				\
  void update_output_##name() override				\
  {								\
    TRACE_THIS_FUN();						\
								\
    /* Upstream recursion. */					\
    this->out_process< In >::update_output_##name();		\
								\
    /* Downstream tail-recursion. */				\
    this->in_process< Out >::update_output_##name();		\
  }

/*
#define PROCESS_GENERATE_OUTPUT( name )					\
  void generate_output_##name() override				\
  {									\
    TRACE_THIS_FUN();							\
									\
    auto primary_input = this->in.primary().lock();			\
									\
    assert( primary_input );						\
									\
    this->out.downstream(						\
      [ &primary_input ]( auto && port ) {				\
									\
	std::cout << "out_process::generate_output_" << #name << "()"	\
		  << std::endl;						\
									\
	assert( port );							\
									\
	port->data = primary_input;					\
      }									\
      );								\
  }
*/

  template< typename In,
	    typename Out >
  struct process : public in_process< Out >,
		   public out_process< In >
  {
    PROCESS_UPDATE_OUTPUT( info );
    PROCESS_UPDATE_OUTPUT( data );

  private:
    void
    generate_output_info() override
    {
      TRACE_THIS_FUN();

      auto primary_input = this->in.primary().lock();

      assert( primary_input );

      this->out.downstream(
	[ &primary_input ]( auto && port ) {
	  // TRACE_FUN();

	  std::cout << "process::generate_output_info()" << std::endl;

	  assert( port );

	  port->data.set_info( primary_input->data.info() );
	}
	);
    }

    void
    generate_output_data() override
    {
      TRACE_THIS_FUN();

      this->out.bar(
	[]( auto && out_port, auto const & in_port ) {
	  auto ip = in_port.lock();

	  out_port->data =
	    ip->data;
	},
	this->in
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
