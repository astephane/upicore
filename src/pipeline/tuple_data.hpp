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
#ifndef PIPELINE_TUPLE_DATA_HPP
#define PIPELINE_TUPLE_DATA_HPP


#include "cxx/tuple.hpp"
#include "pipeline/port.hpp"

#include <memory>


namespace pipeline
{
  template< template< typename > typename Pointer,
	    typename ... T >
  struct tuple_data
  {
    template< std::size_t I >
    auto &
    get() noexcept
    {
      return std::get< I >( data );
    };

    template< std::size_t I >
    auto const &
    get() const noexcept
    {
      return std::get< I >( data );
    };

    auto const &
    primary() const noexcept
    {
      return get< 0 >();
    }

    tuple_data() = default;

  protected:
    tuple_data( Pointer< port < T > > && ... e ) noexcept :
      data( e ... )
    {}

    using value_type = std::tuple< Pointer< port< T > > ... >;

    value_type data;
  };

} // end of namespace 'pipeline'.

#endif // PIPELINE_TUPLE_DATA_HPP
