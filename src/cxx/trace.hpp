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
#ifndef CXX_TRACE_HPP
#define CXX_TRACE_HPP


#include <iostream>


#define TRACE_THAT_FUN( p )			\
  std::cout					\
  << ( p )					\
  << " " << __PRETTY_FUNCTION__			\
  << std::endl


#define TRACE_THIS_FUN() TRACE_THAT_FUN( this )


#define TRACE_FUN()				\
  std::cout					\
  << " " << __PRETTY_FUNCTION__			\
  << std::endl


namespace cxx
{
} // end of namespace 'cxx'.

#endif // CXX_TRACE_HPP
