//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of acosh", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::acosh(T()), T);
  TTS_EXPR_IS(eve::acosh(v_t()), v_t);
};

//==================================================================================================
// acosh  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of acosh on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(1.0, eve::valmax), tts::randoms(1.0, 100.0)))
<typename T>(T const& a0, T const& a1)
{
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::acosh(a0), tts::map([](auto e) -> v_t { return std::acosh(e); }, a0), 2);
  TTS_ULP_EQUAL(eve::acosh(a1), tts::map([](auto e) -> v_t { return std::acosh(e); }, a1), 2);
};


//==================================================================================================
// Tests for masked acosh
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::acosh)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::acosh[mask](a0),
            eve::if_else(mask, eve::acosh(a0), a0));
};
