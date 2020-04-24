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
// #include <iostream>
// #include <memory>
#include <stdexcept>
// #include <tuple>
// #include <type_traits>



namespace pipeline
{

  class process;

// template< typename T >
// struct port
// {
//   using value_type = T;

//   process * source;
//   T data;

// protected:
//   port() : source( nullptr ) {}

//   port( process * p ) noexcept :
//     source( p )
//     {
//       assert( p );

//       if( !p )
// 	throw std::invalid_argument( "Unexpected nullptr process instance." );
//     }
// };


  // template< typename T >
  // struct in_port
  // {
  //   using value_type = T;

  //   // using pointer_type = std::weak_ptr< process >;

  //   process * source;
  //   T data;
  // };



  // template< typename In > class  out_process;
  // template< typename Out > class in_proces;
  // template< typename In, typename Out > class filter;


  namespace details
  {
    template< typename Data >
    struct out_port
    {
      using value_type = Data;

      // using source_pointer_type = std::weak_ptr< process >;
      using source_pointer_type = cxx::raw_ptr< process >;

      out_port( source_pointer_type s ) :
	source( s )
      {
	assert( source );

	if( !source )
	  throw std::invalid_argument( "unexpected nullptr source." );
      }

      source_pointer_type source;
      Data data;

      // private:
      //   struct data
      //   {
      // 	data( std::weak_ptr< out_port > op ) {}

      // 	source_pointer_type source;
      // 	Data data;
      //   };
    };
  } // end of details.


  template< typename Data >
  using port = details::out_port< Data >;


  // template< typename Data >
  // using port_pointer_type = std::shared_ptr< port< Data > >;

} // end of namespace 'pipeline'.

#endif // PORT_HPP
