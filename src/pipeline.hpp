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
#include <iostream>
#include <memory>
#include <stdexcept>
#include <tuple>
#include <type_traits>


namespace cxx
{
  template< typename T >
  using raw_ptr = std::add_pointer_t< T >;
} // end of namespace cxx.


namespace pipeline
{

  struct data
  {
  };


  struct process
  {
    virtual ~process() = default;
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


  // template< typename T >
  // struct in_port
  // {
  //   using value_type = T;

  //   // using pointer_type = std::weak_ptr< process >;

  //   process * source;
  //   T data;
  // };



  template< typename In > class  out_process;
  template< typename Out > class in_proces;
  template< typename In, typename Out > class filter;


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


// template< typename ... T >
// using output = std::tuple< port< T > ... >;


  template< typename ... T >
  struct output
  {
    using source_pointer_type = typename port< T ... >::source_pointer_type;

    output( source_pointer_type p ) :
      data( std::make_shared< port< T > >( p ) ...  )
    {}

    ~output()
    {
      std::apply(
	[]( auto && ... port ) {
	  ( ( assert( port ),
	      std::cout << port << std::endl,
	      port->source = nullptr ),
	    ... );
	},
	data
	);
    }

    using value_type = std::tuple< std::shared_ptr< port< T > > ... >;

    value_type data;
  };


  template< typename ... T >
  using input = std::tuple< std::weak_ptr< port< T > > ... >;

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

} // end of pipeline.


struct image : public pipeline::data
{
};


struct image_file_reader : public pipeline::reader< image >
{
};


struct image_file_writer : public pipeline::writer< image >
{
};


struct ndvi_filter : public pipeline::filter< pipeline::input< image >,
					      pipeline::output< image > >
{
};


struct point_cloud : public pipeline::data
{
};


struct las_file_reader : public pipeline::reader< point_cloud >
{
};


struct las_file_writer : public pipeline::writer< point_cloud >
{
};


struct point_cloud_algorithm : public pipeline::filter< pipeline::input< point_cloud >,
							pipeline::output< point_cloud > >
{
};


#endif // PIPELINE_HPP
