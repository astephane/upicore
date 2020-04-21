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
#ifndef PIPELINE_HPP
#define PIPELINE_HPP


#include <cassert>
#include <memory>
#include <stdexcept>

struct data
{
};


struct process
{
};


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


template< typename T >
struct in_port
{
  using value_type = T;

  using pointer_type = std::weak_ptr< process >;

  pointer_type source;
};


template< typename T >
struct out_port
{
  using value_type = T;

  out_port( process * p ) : process( p ) {}

  process * source;
  T data;
};


// template< typename ... T >
// using input = std::tuple< in_port< T > ... >;

template< typename ... T >
struct output
{
  // template< typename T >
  // using port_ptr_type = std::shared_ptr< T >;

  output( process * p ) : data( out_port< T >( p ) ...  ) {}

  std::tuple< out_port< T > ... > data;
};


template< typename ... T >
using input = std::tuple< in_port< T > ... >;

// template< typename ... T >
// struct input
// {
//     std::tuple< T ... > data;
// };

template< typename Out >
struct in_process : public virtual process
{
  in_process() : out( this ) {}

  Out out;
};

template< typename In >
struct out_process : public virtual process
{
  In in;
};

template< typename In,
	  typename Out >
struct filter : public in_process< Out >,
		public out_process< In >
{
};

struct information
{
};

template< typename Out >
struct reader : public in_process< Out >
{
};

struct writer
{
};


struct image : public data
{
};


struct image_file_reader : public in_process< output< image > >
{
};


struct image_file_writer : public out_process< input< image > >
{
};


struct ndvi_filter : public filter< input< image >,
				    output< image > >
{
};


#endif // PIPELINE_HPP
