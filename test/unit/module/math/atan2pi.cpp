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
TTS_CASE_TPL("Check return types of atan2pi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::atan2pi(T(), T()), T);
  TTS_EXPR_IS(eve::atan2pi(v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::atan2pi(T(), v_t()), T);
  TTS_EXPR_IS(eve::atan2pi(v_t(), T()), T);
};

//==================================================================================================
// atan2pi  tests
//==================================================================================================
auto mini = tts::constant([](auto tgt) { return eve::next(eve::mindenormal(tgt)); });
auto maxi = tts::constant([](auto tgt) { return eve::valmax(tgt) / 2; });

TTS_CASE_WITH("Check behavior of atan2pi on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(mini, maxi),
                            tts::randoms(mini, maxi),
                            tts::randoms(-1.0, 1.0),
                            tts::randoms(-1.0, 1.0)))
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::atan2pi(a0, a1),
                tts::map([](auto e, auto f) -> v_t { return eve::radinpi(std::atan2(e, f)); }, a0, a1),
                2);
  TTS_ULP_EQUAL(eve::atan2pi(a2, a3),
                tts::map([](auto e, auto f) -> v_t { return eve::radinpi(std::atan2(e, f)); }, a2, a3),
                2);
};


//==================================================================================================
// Tests for masked atan2pi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::atan2pi)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         T const& a1,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::atan2pi[mask](a0, a1),
            eve::if_else(mask, eve::atan2pi(a0, a1), a0));
};
