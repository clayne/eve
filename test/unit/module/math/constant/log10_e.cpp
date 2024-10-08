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
#include <iomanip>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of log10_e", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::log10_e(as<T>()), T);
  TTS_EXPR_IS(eve::log10_e(as<v_t>()), v_t);
};
//==================================================================================================
// log10_e  tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of log10_e on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::lower;
  using eve::upper;

  using elt_t = eve::element_type_t<T>;
  if constexpr( sizeof(long double) > sizeof(elt_t) )
  {
    TTS_EXPECT(eve::log10_e[eve::lower](as<elt_t>()) < std::log10(std::exp(1.0l)));
    TTS_EXPECT(eve::log10_e[eve::upper](as<elt_t>()) > std::log10(std::exp(1.0l)));
  }
  TTS_IEEE_EQUAL(eve::log10_e(as<T>()), T(std::log10(std::exp(1.0l))));
};

//==================================================================================================
// log10_e  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of log10_e on scalar", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::lower;
  using eve::upper;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::next(eve::log10_e[eve::lower](as<T>())), eve::log10_e[eve::upper](as<T>()))));
};


//==================================================================================================
// simd Tests for masked log10_e
//==================================================================================================
TTS_CASE_WITH("Check behavior of log10_e[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::log10_e[mask](eve::as(a0)), eve::if_else(mask, eve::log10_e(eve::as(a0)), eve::zero));
};
