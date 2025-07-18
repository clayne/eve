//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/spy.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/memory/pointer.hpp>

namespace eve::detail
{
  template<typename T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE wide<T, N> load_impl(vmx_, Ptr ptr, as<wide<T, N>> tgt) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    if constexpr( N::value * sizeof(T) >= ppc_::bytes )
    {
      if constexpr( current_api >= eve::vsx )
      {
        if constexpr( std::is_integral_v<T> )
        {
          using type = typename wide<T, N>::storage_type*;
          return vec_vsx_ld(0, type(ptr));
        }
        else
        {
          return vec_vsx_ld(0, ptr);
        }
      }
      else if constexpr( current_api >= eve::vmx )
      {
        if constexpr( sizeof(T) <= 8 )
        {
          return vec_perm(vec_ld(0, ptr), vec_ld(16, ptr), vec_lvsl(0, ptr));
        }
        else
        {
          return load_impl(cpu_{}, ptr, tgt);
        }
      }
    }
    else
    {
      typename wide<T, N>::storage_type that{};
      std::memcpy(&that, ptr, N::value * sizeof(T));
      return that;
    }
  }

  template<typename T, typename U, typename N, typename Lanes>
  EVE_FORCEINLINE wide<T, N> load_impl(vmx_, aligned_ptr<U, Lanes> ptr, as<wide<T, N>> tgt) noexcept
    requires ppc_abi<abi_t<T, N>> && simd_compatible_ptr<aligned_ptr<U, Lanes>, wide<T, N>>
  {
    if constexpr( N::value * sizeof(T) >= ppc_::bytes )
    {
      if constexpr( current_api >= eve::vsx )
      {
        if constexpr( std::is_integral_v<T> )
        {
          using type = typename wide<T, N>::storage_type *;
          return vec_vsx_ld(0, type(ptr.get()));
        }
        else
        {
          return vec_vsx_ld(0, ptr.get());
        }
      }
      else if constexpr( current_api >= eve::vmx )
      {
        if constexpr( sizeof(T) <= 8 )
        {
          if constexpr( aligned_ptr<T, Lanes>::alignment() >= 16 ) return vec_ld(0, ptr.get());
          else                                                     return load_impl(current_api, ptr.get(), tgt);
        }
      }
    }
    else
    {
      typename wide<T, N>::storage_type that{};
      std::memcpy(&that, ptr.get(), N::value * sizeof(T));
      return that;
    }
  }
}
