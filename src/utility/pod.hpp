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
#include <tuple>
#include <utility>


namespace utility
{


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


#define DECLARE_ENUM_CLASS_UNARY_EVALUATOR( enum_class, evaluator_name ) \
  									\
  template< enum_class E,						\
	    typename UnaryOp >						\
  constexpr								\
  auto									\
  eval( UnaryOp unary_op ) noexcept					\
  {									\
    using underlying_type_t = std::underlying_type_t< position >;	\
									\
    return								\
      static_cast< E >(							\
  	unary_op(							\
  	  static_cast< underlying_type_t >( P )				\
  	  )								\
  	);								\
  }


#define DECLARE_ENUM_CLASS_NEXT( enum_class )	\
						\
  template< enum_class E >			\
  constexpr					\
  auto						\
  next() noexcept				\
  {						\
    return details::eval< E >(			\
      []( auto p ) { return p + 1; }		\
      );					\
  }


#define DECLARE_ENUM_CLASS_PREV( enum_class )	\
						\
  template< enum_class E >			\
  constexpr					\
  auto						\
  prev() noexcept				\
  {						\
    return details::eval< E >(			\
      []( auto p ) { return p - 1; }		\
      );					\
  }


  template< typename Enum >
  constexpr std::size_t size() noexcept
  {
    return static_cast< std::size_t >( Enum::count );
  }


  namespace detail
  {
    template< typename Enum,
	      template< Enum > typename Traits,
	      std::size_t ... I >
    struct pod
    {
      constexpr pod( std::index_sequence< I ... > = std::index_sequence< I ... >{} ) noexcept
      {
      }

      using value_type = std::tuple< typename Traits< static_cast< Enum >( I ) >::element_type ... >;

      // value_type data;
    };

  } // namespace detail


  template< typename Enum,
	    template< Enum > typename Traits >
  struct pod // : public detail::pod< Enum, Traits >
  {
    static_assert( std::is_enum_v< Enum > );
    // static_assert( std::is_pod_v< pod< Enum, Traits > > );

    using value_type = typename detail::pod< Enum, Traits >::value_type;

    pod() noexcept // : detail::pod< Enum, Traits >( std::make_index_sequence< size< Enum >() >() )
    {
    }

#if 0
    template< Enum E >
    auto const &
    get() const
    {
      return
	std::get< static_cast< std::underlying_type_t< Enum > >( E ) >( this->data );
    }
#endif

    value_type data;
  };

} // namespace utility


namespace sample_pod
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


} // namespace sample_pod


#endif // UTILITY_POD_HPP
