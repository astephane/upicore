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
#ifndef PIPELINE_INPUT_HPP
#define PIPELINE_INPUT_HPP


#include "cxx/tuple.hpp"
#include "pipeline/port.hpp"

#include <iostream>
#include <memory>


// https://stackoverflow.com/questions/47496358/c-lambdas-how-to-capture-variadic-parameter-pack-from-the-upper-scope
#if 0

template <typename ... Args>
auto f(Args&& ... args){
    return [args = std::make_tuple(std::forward<Args>(args) ...)]()mutable{
        return std::apply([](auto&& ... args){
            // use args
        }, std::move(args));
    };
}

#endif

namespace pipeline
{

  template< typename ... T >
  struct input
  {
    template< std::size_t I >
    auto &
    get() noexcept
    {
      return std::get< I >( data );
    }

    template< typename F >
    auto
    upstream( F && f )
    {
      return
	cxx::tuple::for_each(
	  [ &f ]( auto && p ) {
	    f( p.lock() );
	  },
	  data
	  );
    }

    void
    update_output_information()
    {
      std::cout << typeid( this ).name() << "::upate_output_information()" << std::endl;

      upstream(
	[]( auto && p ) {
	  assert( p );
	  assert( p->source );

	  p->source->update_output_information();
	}
	);
    }

  private:
    using value_type = std::tuple< std::weak_ptr< port< T > > ... >;

    value_type data;
  };

} // end of namespace 'pipeline'.

#endif // PIPELINE_INPUT_HPP
