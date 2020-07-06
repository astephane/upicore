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
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with upicore.	If not, see <https://www.gnu.org/licenses/>.
//
#ifndef UTILITY_POD_HPP
#define UTILITY_POD_HPP


#include <type_traits>
#include <stdexcept>


namespace utility
{

  enum class vector : int
  {
    x = 0,
    y,
    z,
    //
    count,
    //
    first = x,
    last = z,
  };


  enum class color : int
  {
    r = 0,
    g,
    b,
    a,
    //
    count,
    //
    first = r,
    last = a,
  };


  enum class vertex : int
  {
    v,
    n,
    c,
    //
    count,
    //
    first = v,
    last = c,
  };


#define DECLARE_ENUM_CLASS_TRAITS( enum_class, enum_class_traits )	\
									\
  template< enum_class E >						\
  struct enum_class_traits						\
  {									\
    using value_type = enum_class;					\
									\
    using element_type = void;						\
									\
    static constexpr char const * name()				\
    {									\
      throw std::domain_error( "unexpected '" #enum_class "' enum-class value." ); \
    }									\
  };


#define DEFINE_ENUM_CLASS_TRAIT( enum_class_traits,	\
				 enum_class,		\
				 enum_value,		\
				 elt_name,		\
				 elt_type )		\
							\
  template<>						\
  struct enum_class_traits< enum_value >		\
  {							\
    using value_type = enum_class;			\
							\
    static_assert( std::is_enum_v< enum_class > );	\
							\
    using element_type = elt_type;			\
							\
    static constexpr char const * name() noexcept	\
    {							\
      return elt_name;					\
    }							\
  };


#define DEFINE_VECTOR_TRAIT( enum_value, elt_name, elt_type )		\
  DEFINE_ENUM_CLASS_TRAIT( vector_traits, vector, enum_value, elt_name, elt_type )

#define DEFINE_COLOR_TRAIT( enum_value, elt_name, elt_type )		\
  DEFINE_ENUM_CLASS_TRAIT( color_traits, color, enum_value, elt_name, elt_type )

#define DEFINE_VERTEX_TRAIT( enum_value, elt_name, elt_type )		\
  DEFINE_ENUM_CLASS_TRAIT( vertex_traits, vertex, enum_value, elt_name, elt_type )


  DECLARE_ENUM_CLASS_TRAITS( vector, vector_traits );

  DEFINE_VECTOR_TRAIT( vector::x, "x", double );
  DEFINE_VECTOR_TRAIT( vector::y, "y", double );
  DEFINE_VECTOR_TRAIT( vector::z, "z", double );


  DECLARE_ENUM_CLASS_TRAITS( color, color_traits );

  DEFINE_COLOR_TRAIT( color::r, "r", std::uint8_t );
  DEFINE_COLOR_TRAIT( color::g, "g", std::uint8_t );
  DEFINE_COLOR_TRAIT( color::b, "b", std::uint8_t );
  DEFINE_COLOR_TRAIT( color::a, "a", std::uint8_t );


  DECLARE_ENUM_CLASS_TRAITS( vertex, vertex_traits );

  DEFINE_VERTEX_TRAIT( vertex::v, "v", vector );
  DEFINE_VERTEX_TRAIT( vertex::n, "n", vector );
  DEFINE_VERTEX_TRAIT( vertex::c, "c", color );


  template< typename T >
  struct pod
  {
    static_assert( std::is_enum_v< T > );
    static_assert( std::is_pod_v< pod< T > > );
  };

} // namespace utility

#endif // UTILITY_POD_HPP
