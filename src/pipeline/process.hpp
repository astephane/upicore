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

    // virtual void uoi() = 0;
  };


  template< typename Out >
  struct in_process : public virtual process
  {
    in_process() : out( this ) {}

    // template< std::size_t I >
    // auto &
    // output() noexcept
    // {
    //   return std::get< I >( out.data );
    // }

    void uoi()
    {
      cxx::tuple::for_each(
	[]( auto && port ) {

	},
	out
	);
    }

    Out out;
  };


  template< typename In >
  struct out_process : public virtual process
  {
    // template< std::size_t I >
    // auto &
    // input() noexcept
    // {
    //   return std::get< I >( in );
    // }

    void uoi()
    {
      cxx::tuple::for_each(
	[]( auto && port) {
	  assert( port );
	  assert( port->data.source );
	  port->data.source->uoi();
	},
	in
	);
    }

    In in;
  };


  template< typename In,
	    typename Out >
  struct filter : public in_process< Out >,
		  public out_process< In >
  {
  };

// struct information
// {
// };

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
