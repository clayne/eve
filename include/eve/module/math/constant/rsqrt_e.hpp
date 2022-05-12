//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup math
  //! @{
  //! @var rsqrt_e
  //!
  //! @brief Callable object computing the constant \f$1/\sqrt{e}\f$.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the aforementioned constant                              |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template < floating_value T > T operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the rsqrt_e constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/rsqrt_e.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(rsqrt_e_, rsqrt_e);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto rsqrt_e_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.368b3p-1);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.368b2fc6f960ap-1);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto rsqrt_e_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.368b3p-1);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.368b2fc6f960ap-1);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.368b2ep-1);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.368b2fc6f9609p-1);
      }
    }
  }
}