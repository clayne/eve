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
// epso_2 Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of epso_2", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::epso_2(as<T>()), T);
  TTS_EXPR_IS(eve::epso_2(as<v_t>()), v_t);
};
//==================================================================================================
// epso_2 tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of epso_2 on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::epso_2[eve::lower](eve::as<T>()) <= eve::eps(eve::as<T>())/2);
    TTS_EXPECT(eve::epso_2[eve::upper](eve::as<T>()) >= eve::eps(eve::as<T>())/2); 
  }
  TTS_EQUAL(eve::epso_2(eve::as<T>()), T(eve::eps(eve::as<T>())/2));
};

//==================================================================================================
// epso_2  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of epso_2 on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::epso_2[eve::lower](as<T>()), eve::epso_2[eve::upper](as<T>()))));
};


//==================================================================================================
// simd Tests for masked epso_2
//==================================================================================================
TTS_CASE_WITH("Check behavior of epso_2[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::epso_2[mask](eve::as(a0)), eve::if_else(mask, eve::epso_2(eve::as(a0)), eve::zero));
};
