//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <cmath>

#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of round", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::round(T()), T);
  TTS_EXPR_IS(eve::round(v_t()), v_t);
  TTS_EXPR_IS(eve::round[eve::upward](T()), T);
  TTS_EXPR_IS(eve::round[eve::downward](T()), T);
  TTS_EXPR_IS(eve::round[eve::toward_zero](T()), T);
  TTS_EXPR_IS(eve::round[eve::to_nearest](T()), T);
};

//==================================================================================================
// round(simd)  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of round(wide)", eve::test::simd::all_types)
  <typename T>(tts::type<T>)
{
  TTS_EQUAL(eve::round[eve::upward](T(1.7)), eve::ceil(T(1.7)));
  TTS_EQUAL(eve::round[eve::downward](T(1.7)), eve::floor(T(1.7)));
  TTS_EQUAL(eve::round[eve::toward_zero](T(1.7)), eve::trunc(T(1.7)));
  TTS_EQUAL(eve::round[eve::to_nearest](T(1.7)), eve::nearest(T(1.7)));
  TTS_EQUAL(eve::round(T(1.7)), eve::nearest(T(1.7)));

  TTS_EQUAL(eve::round[eve::upward](T(1.3)), eve::ceil(T(1.3)));
  TTS_EQUAL(eve::round[eve::downward](T(1.3)), eve::floor(T(1.3)));
  TTS_EQUAL(eve::round[eve::toward_zero](T(1.3)), eve::trunc(T(1.3)));
  TTS_EQUAL(eve::round[eve::to_nearest](T(1.3)), eve::nearest(T(1.3)));
  TTS_EQUAL(eve::round(T(1.3)), eve::nearest(T(1.3)));
};


//==================================================================================================
// Tests for masked round
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked round(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::round[mask](a0),
            eve::if_else(mask, eve::round(a0), a0));
};
