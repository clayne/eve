//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/x86/predef.hpp>
#include <compare>
#include <type_traits>
#include <ostream>

namespace eve
{
  template<typename T>
  struct logical;
  struct x86_128_;
  struct x86_256_;
}

namespace eve
{
  template<typename T, typename N, x86_abi ABI>
  consteval auto find_register_type(as<T>, N, ABI)
  {
    constexpr size_t width = sizeof(T) * N::value;

    if constexpr (std::same_as<ABI, x86_128_>)
    {
      if constexpr (width <= 16)
      {
             if constexpr (std::same_as<T, double>) return __m128d{};
        else if constexpr (std::same_as<T, float >) return __m128{};
        else if constexpr (std::is_integral_v<T>  ) return __m128i{};
      }
    }
    else if constexpr (std::same_as<ABI, x86_256_>)
    {
      if constexpr (width <= 32)
      {
             if constexpr (std::same_as<T, double>) return __m256d{};
        else if constexpr (std::same_as<T, float >) return __m256{};
        else if constexpr (std::is_integral_v<T>  ) return __m256i{};
      }
    }
    else if constexpr (std::same_as<ABI, x86_512_>)
    {
      if constexpr (width <= 64)
      {
             if constexpr (std::same_as<T, double>) return __m512d{};
        else if constexpr (std::same_as<T, float >) return __m512{};
        else if constexpr (std::is_integral_v<T>  ) return __m512i{};
      }
    }
  }

  namespace detail
  {
    template<int N> struct as_mask;

    template<int N> struct inner_mask;

    template<> struct inner_mask<8>  { using type = __mmask8;  };
    template<> struct inner_mask<16> { using type = __mmask16; };
    template<> struct inner_mask<32> { using type = __mmask32; };
    template<> struct inner_mask<64> { using type = __mmask64; };

    template<int N>
    struct mask_n
    {
      using type = typename inner_mask<N>::type;
      static constexpr int bits = N;

      explicit constexpr operator type() const { return value; }
      explicit constexpr operator bool() const { return (bool) value; }

      // != and reverse are generated.
      // <=> didn't work for some reason for ==
      friend bool operator== (mask_n m, type n) { return m == mask_n{n}; }
      friend bool operator== (mask_n  , mask_n) = default;
      friend auto operator<=>(mask_n  , mask_n) = default;

      friend constexpr mask_n operator~(mask_n m) { return mask_n{ static_cast<type>(~m.value) }; }

      friend constexpr mask_n& operator&=(mask_n& m, mask_n n) { m.value &= n.value; return m;     }
      friend constexpr mask_n& operator&=(mask_n& m, type   n) { m.value &= n;       return m;     }
      friend constexpr mask_n  operator& (mask_n  m, mask_n n) { mask_n t{m}; return t &= n; }
      friend constexpr mask_n  operator& (mask_n  m, type   n) { mask_n t{n}; return t &= m;       }
      friend constexpr mask_n  operator& (type    m, mask_n n) { mask_n t{m}; return t &= n;       }

      friend constexpr mask_n& operator|=(mask_n& m, mask_n n) { m.value |= n.value; return m;     }
      friend constexpr mask_n& operator|=(mask_n& m, type   n) { m.value |= n;       return m;     }
      friend constexpr mask_n  operator| (mask_n  m, mask_n n) { mask_n t{m}; return t |= n; }
      friend constexpr mask_n  operator| (mask_n  m, type   n) { mask_n t{n}; return t |= m;       }
      friend constexpr mask_n  operator| (type    m, mask_n n) { mask_n t{m}; return t |= n;       }

      friend constexpr mask_n& operator^=(mask_n& m, mask_n n) { m.value ^= n.value; return m;     }
      friend constexpr mask_n& operator^=(mask_n& m, type   n) { m.value ^= n;       return m;     }
      friend constexpr mask_n  operator^ (mask_n  m, mask_n n) { mask_n t{m.value}; return t ^= n; }
      friend constexpr mask_n  operator^ (mask_n  m, type   n) { mask_n t{n}; return t ^= m;       }
      friend constexpr mask_n  operator^ (type    m, mask_n n) { mask_n t{m}; return t ^= n;       }

      friend constexpr mask_n&  operator<<=(mask_n& m, std::ptrdiff_t s) { m.value <<= s; return m; }
      friend constexpr mask_n   operator<< (mask_n  m, std::ptrdiff_t s) { mask_n t{m.value}; return t <<= s; }
      friend constexpr mask_n&  operator>>=(mask_n& m, std::ptrdiff_t s) { m.value >>= s; return m; }
      friend constexpr mask_n   operator>> (mask_n  m, std::ptrdiff_t s) { mask_n t{m}; return t >>= s; }

      friend std::ostream& operator<<(std::ostream& out, const mask_n& m) { return out << m.value; }

      type value;
    };

    using mask8  = mask_n<8>;
    using mask16 = mask_n<16>;
    using mask32 = mask_n<32>;
    using mask64 = mask_n<64>;

    template<> struct as_mask<8>  { using type = mask8; };
    template<> struct as_mask<16> { using type = mask16; };
    template<> struct as_mask<32> { using type = mask32; };
    template<> struct as_mask<64> { using type = mask64; };

    template<int N> using as_mask_t = typename as_mask<std::max(8,N)>::type;
  }

# if defined(SPY_SIMD_IS_X86_AVX512)
  // logical uses different registers in AVX512
  template<typename T, typename N, x86_abi ABI>
  consteval auto find_logical_register_type(as<T>, N, ABI)
  {
    constexpr size_t width = sizeof(T) * N::value;

    if constexpr (std::same_as<ABI, x86_512_> && (width == 64))
    {
      return detail::as_mask_t<64 / sizeof(T)>{};
    }
    else if constexpr (std::same_as<ABI, x86_256_> && (width == 32))
    {
      if constexpr (N::value <= 8 ) return detail::mask8{};
      if constexpr (N::value == 16) return detail::mask16{};
      if constexpr (N::value == 32) return detail::mask32{};
    }
    else if constexpr (std::same_as<ABI, x86_128_> && (width <= 16))
    {
      if constexpr (sizeof(T) == 1) return detail::mask16{};
      else                          return detail::mask8{};
    }
  }
# else
  // logical uses same registers
  template<typename T, typename N>
  consteval auto find_logical_register_type(as<T> t, N n, x86_abi auto a)
  {
    return find_register_type(t, n, a);
  }
# endif
}
