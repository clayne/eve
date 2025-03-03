//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> is_less_(EVE_REQUIRES(sve_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    if constexpr (O::contains(definitely)) return is_less.behavior(cpu_{}, opts, a, b);
    else                                   return svcmplt(sve_true<T>(), a, b);
  }
}
