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
TTS_CASE_TPL("Check return types of lohi", eve::test::simd::integers)
<typename T>(tts::type<T>)
{
  using elt_t  = eve::element_type_t<T>;
  using sui_t  = eve::as_integer_t<elt_t, unsigned>;
  using sdui_t = eve::downgrade_t<sui_t>;
  using v_t    = eve::as_wide_as_t<sdui_t,T>;
  using vt_t   = eve::result_t<eve::zip,v_t,v_t>;
  using t_t    = eve::result_t<eve::zip,sdui_t,sdui_t>;

  TTS_EXPR_IS(eve::lohi(T{})    , vt_t);
  TTS_EXPR_IS(eve::lohi(elt_t{}), t_t);
};

//==================================================================================================
//== lohi  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of lohi on all types full range", eve::test::simd::integers)
<typename T>(tts::type<T>)
{
  using elt_t = eve::element_type_t<T>;
  using ui_t  = eve::as_integer_t<elt_t, unsigned>;
  using dui_t = eve::downgrade_t<ui_t>;
  if constexpr( sizeof(elt_t) > 1 )
  {
    {
      auto [p0, p1] = eve::lohi(T(1));
      using wui_t   = decltype(p0);
      TTS_EQUAL(p0, wui_t(1));
      TTS_EQUAL(p1, wui_t(0));
    }

    {
      auto [p0, p1] = eve::lohi(T(ui_t(~0)));
      using wui_t   = decltype(p0);
      TTS_EQUAL(p0, wui_t(dui_t(~0)));
      TTS_EQUAL(p1, wui_t(dui_t(~0)));
    }
    {
      auto [p0, p1] = eve::lohi(T(ui_t(~0) >> (sizeof(elt_t) * 4)));
      using wui_t   = decltype(p0);
      TTS_EQUAL(p0, wui_t(dui_t(~0)));
      TTS_EQUAL(p1, wui_t(dui_t(0)));
    }
  }
  else
  {
    {
      auto [p0, p1] = eve::lohi(T(1));
      using wui_t   = decltype(p0);
      TTS_EQUAL(p0, wui_t(1));
      TTS_EQUAL(p1, wui_t(0));
    }

    {
      auto [p0, p1] = eve::lohi(T(ui_t(~0)));
      using wui_t   = decltype(p0);
      TTS_EQUAL(p0, wui_t(dui_t(~0) >> (sizeof(elt_t) * 4)));
      TTS_EQUAL(p1, wui_t(dui_t(~0) >> (sizeof(elt_t) * 4)));
    }
    {
      auto [p0, p1] = eve::lohi(T(ui_t(~0) >> (sizeof(elt_t) * 4)));
      using wui_t   = decltype(p0);
      TTS_EQUAL(p0, wui_t(dui_t(~0) >> (sizeof(elt_t) * 4)));
      TTS_EQUAL(p1, wui_t(dui_t(0)));
    }
  }
};
