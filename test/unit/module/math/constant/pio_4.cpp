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
TTS_CASE_TPL("Check return types of pio_4", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::pio_4(as<T>()), T);
  TTS_EXPR_IS(eve::pio_4(as<v_t>()), v_t);
};
//==================================================================================================
// pio_4  tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of pio_4 on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::lower;
  using eve::upper;

  using elt_t = eve::element_type_t<T>;
  if constexpr( sizeof(long double) > sizeof(elt_t) )
  {
    TTS_EXPECT(eve::pio_4[eve::lower](as<elt_t>()) < std::atan(1.0l));
    TTS_EXPECT(eve::pio_4[eve::upper](as<elt_t>()) > std::atan(1.0l));
  }
  TTS_EQUAL(eve::pio_4(as<T>()), T(std::atan(1.0l)));
};

//==================================================================================================
// pio_4  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of pio_4 on scalar", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::lower;
  using eve::upper;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::next(eve::pio_4[eve::lower](as<T>())), eve::pio_4[eve::upper](as<T>()))));
};


//==================================================================================================
// simd Tests for masked pio_4
//==================================================================================================
TTS_CASE_WITH("Check behavior of pio_4[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::pio_4[mask](eve::as(a0)), eve::if_else(mask, eve::pio_4(eve::as(a0)), eve::zero));
};
