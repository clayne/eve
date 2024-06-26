//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
  template<typename Options>
  struct ceil_t : strict_elementwise_callable<ceil_t, Options, almost_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  noexcept
    {
      //     static_assert( valid_tolerance<T, Options>::value, "[eve::ceil] simd tolerance requires simd parameter." );
      return EVE_DISPATCH_CALL(v);
    }

    template<eve::value T, only_if<signed,unsigned>  U>
    constexpr EVE_FORCEINLINE  as_integer_t<T, U> operator()(T v,  as<U> const & target) const noexcept
    {
//      static_assert( valid_tolerance<T, Options>::value, "[eve::ceil] simd tolerance requires simd parameter." );
      return EVE_DISPATCH_CALL(v, target);
    }

    EVE_CALLABLE_OBJECT(ceil_t, ceil_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var ceil
//!   @brief Computes the smallest integer not less than the input.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::value T >
//!      T ceil(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::value) argument.
//!
//!   **Return value**
//!
//!     The smallest integer not less than `x`.
//!
//!     The standard proposes 4 rounding modes namely: `FE_TONEAREST`, `FE_DOWNWARD`, `FE_UPWARD`,
//!     `FE_TOWARDZERO`. This function object implements the `FE_UPWARD` version.
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/ceil.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::ceil[mask](x)` provides a masked version of `eve::ceil` which is
//!     equivalent to `if_else (mask, ceil(x), x)`.
//!
//!   * eve::almost
//!
//!     The expression `ceil[almost = tol](x)` computes a tolerant ceil value for `x`,
//!     where `x` must be a floating value and tol a scalar value.
//!
//!      * If `tol` is a floating value, computes the floor with a tolerance `tol`
//!        using Hagerty's FL5 function.
//!      * If `tol` is an integral value n, computes the floor of the next nth
//!        representable value in the `x` type.
//!      * ceil[almost](x) is equivalent to `ceil[tolerance = 3*eve::eps(eve::as (x))(x)`).
//!
//! @}
//================================================================================================
inline constexpr auto ceil = functor<ceil_t>;
}

#include <eve/module/core/regular/impl/ceil.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/ceil.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/ceil.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/ceil.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/ceil.hpp>
#endif
