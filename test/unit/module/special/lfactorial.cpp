//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/math.hpp>
#include <eve/module/special.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::lfactorial", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using d_t = eve::wide<double, eve::cardinal_t<T>>;
  using v_t = eve::element_type_t<T>;
  if constexpr( eve::integral_value<T> )
  {
    TTS_EXPR_IS(eve::lfactorial(T()), d_t);
    TTS_EXPR_IS(eve::lfactorial(v_t()), double);
  }
  else
  {
    TTS_EXPR_IS(eve::lfactorial(T()), T);
    TTS_EXPR_IS(eve::lfactorial(v_t()), v_t);
  }
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::lfactorial on wide", eve::test::simd::all_types

)
<typename T>(tts::type<T>)
{
  using eve::as;
  using d_t = eve::wide<double, eve::cardinal_t<T>>;
  if constexpr( eve::integral_value<T> )
  {
    using v_t = eve::element_type_t<T>;
    TTS_ULP_EQUAL(eve::lfactorial(T(10)), eve::log(d_t(3628800)), 1.0);
    TTS_ULP_EQUAL(eve::lfactorial(T(5)), eve::log(d_t(120)), 1.0);
    TTS_ULP_EQUAL(eve::lfactorial(T(0)), eve::log(d_t(1)), 1.0);
    TTS_ULP_EQUAL(eve::lfactorial(T(1)), eve::log(d_t(1)), 1.0);
    if constexpr( sizeof(v_t) > 1 ) TTS_ULP_EQUAL(eve::lfactorial(T(200)), eve::log_abs_gamma(d_t(201)), 1.0);
  }
  else
  {
    TTS_ULP_EQUAL(eve::lfactorial(T(10)), eve::log(T(3628800)), 1.0);
    TTS_ULP_EQUAL(eve::lfactorial(T(5)), eve::log(T(120)), 1.0);
    TTS_ULP_EQUAL(eve::lfactorial(T(0)), eve::log(T(1)), 1.0);
    TTS_ULP_EQUAL(eve::lfactorial(T(1)), eve::log(T(1)), 1.0);
    TTS_ULP_EQUAL(eve::lfactorial(T(200)), eve::log_abs_gamma(T(201)), 1.0);
  }
};
