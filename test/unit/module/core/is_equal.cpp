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
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::is_equal(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::is_equal(T(), T()), logical<T>);
  TTS_EXPR_IS(eve::is_equal(v_t(), v_t()), logical<v_t>);
  TTS_EXPR_IS(eve::is_equal(T(), v_t()), logical<T>);
  TTS_EXPR_IS(eve::is_equal(v_t(), T()), logical<T>);
  TTS_EXPR_IS(eve::is_equal(logical<T>(), logical<T>()), logical<T>);
  TTS_EXPR_IS(eve::is_equal(logical<v_t>(), logical<v_t>()), logical<v_t>);

  if constexpr( eve::floating_value<T> )
  {
    TTS_EXPR_IS(eve::is_equal[eve::numeric](T(), T()), logical<T>);
    TTS_EXPR_IS(eve::is_equal[eve::numeric](v_t(), v_t()), logical<v_t>);
    TTS_EXPR_IS(eve::is_equal[eve::numeric](T(), v_t()), logical<T>);
    TTS_EXPR_IS(eve::is_equal[eve::numeric](v_t(), T()), logical<T>);
    TTS_EXPR_IS(eve::is_equal[eve::almost](T(), T()), logical<T>);
    TTS_EXPR_IS(eve::is_equal[eve::almost](v_t(), v_t()), logical<v_t>);
    TTS_EXPR_IS(eve::is_equal[eve::almost](T(), v_t()), logical<T>);
    TTS_EXPR_IS(eve::is_equal[eve::almost](v_t(), T()), logical<T>);
  }
};

//==================================================================================================
//== Tests for eve::is_equal
//==================================================================================================
TTS_CASE_WITH(
    "Check behavior of eve::is_equal(simd)",
    eve::test::simd::all_types,
    tts::generate(tts::ramp(0), tts::reverse_ramp(4, 2), tts::logicals(0, 3), tts::logicals(1, 2)))
<typename T, typename M>(T const& a0, T const& a1, M const& l0, M const& l1)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_equal(a0, a1),
            tts::map([](auto e, auto f) -> eve::logical<v_t> { return e == f; }, a0, a1));
  TTS_EQUAL(eve::is_equal(a0, a0),
            tts::map([](auto e, auto f) -> eve::logical<v_t> { return e == f; }, a0, a0));
  TTS_EQUAL(eve::is_equal(a0, v_t(1)),
            tts::map([](auto e) -> eve::logical<v_t> { return e == v_t(1); }, a0));
  TTS_EQUAL(eve::is_equal(v_t(14), a1),
            tts::map([](auto e) -> eve::logical<v_t> { return e == v_t(14); }, a1));
  TTS_EQUAL(eve::is_equal(l0, l1),
            tts::map([](auto e, auto f) -> eve::logical<v_t> { return e == f; }, l0, l1));
  TTS_EQUAL(eve::is_equal[l0](a0, a1),
            eve::if_else(l0, eve::is_equal(a0, a1), eve::false_(eve::as(a0))));
};

//==================================================================================================
//== Tests for eve::is_equal corner cases for floating
//==================================================================================================
TTS_CASE_TPL("Check behavior of eve::is_equal(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T> const& tgt)
{
  using eve::as;
  using v_t  = eve::element_type_t<T>;
  using ui_t = eve::as_integer_t<v_t, unsigned>;

  auto cases = tts::limits(tgt);
  TTS_EQUAL(eve::is_equal(cases.nan, cases.nan), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_equal[eve::numeric](cases.nan, cases.nan), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost](T(1 + eve::eps(as<T>())), T(1)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost =  eve::eps(as<v_t>())](T(1 + eve::eps(as<T>())), T(1)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost =  eve::eps(as<v_t>())](T(1 + 2 * eve::eps(as<T>())), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost =  eve::eps(as<v_t>())](T(1 + eve::eps(as<T>())), v_t(1)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost =  eve::eps(as<v_t>())](T(3), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost =  eve::eps(as<v_t>())](T(3), v_t(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost = ui_t(3)](T(1), T(1)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost = ui_t(3)](T(1), v_t(1)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost = ui_t(3)](T(3), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost = ui_t(3)](T(3), v_t(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost = ui_t(3)](eve::next(T(0)), T(0)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost = ui_t(3)](eve::next(T(0), 3), T(0)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost = ui_t(3)](eve::next(T(0), 4), T(0)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost = ui_t(3)](v_t(1), v_t(1)), eve::true_(eve::as<v_t>()));
  TTS_EQUAL(eve::is_equal[eve::almost = ui_t(3)](v_t(3), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost = ui_t(3)](v_t(3), v_t(1)), eve::false_(eve::as<v_t>()));
};
