//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/arch/arm/sve/sve_true.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> floor_(EVE_REQUIRES(sve_),
                              O          const& opts,
                              wide<T, N> const& v) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    return floor_(adl_helper_t{}, sve_{}, ignore_none, opts, v);
  }

  template<conditional_expr C,floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> floor_(EVE_REQUIRES(sve_),
                              C          const& cond,
                              O          const& opts,
                              wide<T, N> const& v) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    auto alt = alternative(cond, v, as(v));

    if      constexpr(C::is_complete && !C::is_inverted) return alt;
    else if constexpr(!O::contains(almost))             return svrintm_m(alt, cond.mask(as(v)), v);
    else                                                 return floor[opts][cond].retarget(cpu_{}, v);
  }
}
