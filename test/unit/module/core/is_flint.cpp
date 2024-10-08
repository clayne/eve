//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::is_flint(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::is_flint(T()), logical<T>);
  TTS_EXPR_IS(eve::is_flint(v_t()), logical<v_t>);
  TTS_EXPR_IS(eve::is_flint[eve::pedantic](T()), logical<T>);
  TTS_EXPR_IS(eve::is_flint[eve::pedantic](v_t()), logical<v_t>);
};

//==================================================================================================
// Tests for eve::is_flint
//==================================================================================================
auto mf2 = tts::constant([]<typename T>(eve::as<T> const& tgt) { return eve::maxflint(tgt) * 4; });

TTS_CASE_WITH("Check behavior of eve::is_flint(simd)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::maxflint, mf2),
                            tts::randoms(eve::maxflint, mf2),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, M const& t)
{
  using v_t = eve::element_type_t<T>;
  auto aa0  = eve::trunc(a0) / 2;
  auto aa1  = eve::trunc(a1) / 2;
  TTS_EQUAL(eve::is_flint(aa0),
            tts::map([](auto e) -> eve::logical<v_t> { return e == std::trunc(e); }, aa0));
  TTS_EQUAL(eve::is_flint[eve::pedantic](aa1),
            tts::map([](auto e) -> eve::logical<v_t>
                { return (e == std::trunc(e)) && (e <= eve::maxflint(eve::as(e))); },
                aa1));
  TTS_EQUAL(eve::is_flint[t](a0), eve::if_else(t, eve::is_flint(a0), eve::false_(eve::as(a0))));
};
