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
#include <tuple>

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

  // using pointer_type = std::weak_ptr< process >;

  process * source;
  T data;
};


template< typename Data >
struct out_port
{
  using value_type = Data;

  out_port( process * p ) : source( p ) {}

  process * source;
  Data data;
};


template< typename Data >
using port = out_port< Data >;


// template< typename ... T >
// using output = std::tuple< port< T > ... >;


template< typename ... T >
struct output
{
  output( process * p ) : data( out_port< T >( p ) ...  ) {}

  using value_type = std::tuple< out_port< T > ... >;

  value_type data;
};


template< typename ... T >
using input = std::tuple< port< T > * ... >;

// template< typename ... T >
// struct input
// {
//     std::tuple< T ... > data;
// };


template< typename Out >
struct in_process : public virtual process
{
  in_process() : out( this ) {}

  template< std::size_t I >
  auto &
  output() noexcept
    {
      return std::get< I >( out.data );
    }

  Out out;
};


template< typename In >
struct out_process : public virtual process
{
  template< std::size_t I >
  auto &
  input() noexcept
    {
      return std::get< I >( in );
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


struct image : public data
{
};


struct image_file_reader : public reader< image >
{
};


struct image_file_writer : public writer< image >
{
};


struct ndvi_filter : public filter< input< image >,
				    output< image > >
{
};


struct point_cloud : public data
{
};


struct las_file_reader : public reader< point_cloud >
{
};


struct las_file_writer : public writer< point_cloud >
{
};


struct point_cloud_algorithm : public filter< input< point_cloud >,
					      output< point_cloud > >
{
};


#endif // PIPELINE_HPP
