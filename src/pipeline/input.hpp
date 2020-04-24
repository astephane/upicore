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


#include "pipeline/port.hpp"

// #include <cassert>
// #include <iostream>
#include <memory>
// #include <stdexcept>
// #include <tuple>
// #include <type_traits>


namespace pipeline
{

  template< typename ... T >
  struct input
  {
    template< std::size_t I >
    auto
    get() noexcept
    {
      return std::get< I >( data );
    }

  private:
    using value_type = std::tuple< std::weak_ptr< port< T > > ... >;

    value_type data;
  };

} // end of namespace 'pipeline'.

#endif // PIPELINE_INPUT_HPP
