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
#ifndef PIPELINE_IN_PROCESS_HPP
#define PIPELINE_IN_PROCESS_HPP


#include "output.hpp"
#include "cxx/trace.hpp"


namespace pipeline
{

#define IN_PROCESS_UPDATE_OUTPUT( name )	\
  void						\
  update_output_##name() override		\
  {						\
    TRACE_THIS_FUN();				\
						\
    /* No upstream forwarding. */		\
						\
    /* Downstream tail-recursion. */		\
    generate_output_##name();			\
  }


  template< typename Out >
  struct in_process : public in_process_interface
  {
    in_process() : out( this ) {}

    IN_PROCESS_UPDATE_OUTPUT( info );
    IN_PROCESS_UPDATE_OUTPUT( data );

    Out out;
  };

} // end of pipeline.

#endif // PIPELINE_IN_PROCESS_HPP
