//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/elliptic.hpp>

#include <numeric>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of agm", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::agm(T(), T()), T);
  TTS_EXPR_IS(eve::agm(v_t(), v_t()), v_t);
};

//==================================================================================================
//== agm tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of agm(wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(1, 10), tts::randoms(1, 10)))
<typename T>(T const& a0, T const& a1)
{
  using eve::agm;
  TTS_RELATIVE_EQUAL(agm(a0, a1),
                     ((a0 + a1) / eve::ellint_1((a0 - a1) / (a0 + a1))) * eve::pio_4(eve::as(a0)),
                     0.5);
};

//==================================================================================================
//==  conditional agm tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of  agm[cond](wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0, 10), tts::randoms(0, 10), tts::randoms(0, 10)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::agm;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(agm[a2 > T(64)](a0, a1),
                tts::map([](auto e, auto f, auto g) { return g > v_t(64) ? agm(e, f) : e; }, a0, a1, a2),
                5);
};


//==================================================================================================
// Tests for masked agm
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::agm)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         T const& a1,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::agm[mask](a0, a1),
            eve::if_else(mask, eve::agm(a0, a1), a0));
};
