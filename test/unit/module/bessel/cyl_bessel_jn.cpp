//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/bessel.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of cyl_bessel_jn", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;
  TTS_EXPR_IS(eve::cyl_bessel_jn(T(), T()), T);
  TTS_EXPR_IS(eve::cyl_bessel_jn(v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::cyl_bessel_jn(i_t(), T()), T);
  TTS_EXPR_IS(eve::cyl_bessel_jn(I_t(), T()), T);
  TTS_EXPR_IS(eve::cyl_bessel_jn(i_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::cyl_bessel_jn(I_t(), v_t()), T);
};

//==================================================================================================
//== integral orders
//==================================================================================================
TTS_CASE_WITH("Check behavior of cyl_bessel_jn on wide with integral order",
              eve::test::simd::ieee_reals,
              tts::generate(tts::ramp(0), tts::randoms(0.0, 1000.0)))
<typename T>([[maybe_unused]] T n, [[maybe_unused]] T a0)
{
  using v_t               = eve::element_type_t<T>;
  using i_t               = eve::as_integer_t<v_t>;
  using I_t               = eve::wide<i_t, eve::cardinal_t<T>>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve::cyl_bessel_jn(0, eve::minf(eve::as<v_t>())), eve::zero(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_jn(2, eve::inf(eve::as<v_t>())), v_t(0), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_jn(3, eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);

    TTS_ULP_EQUAL(eve::cyl_bessel_jn(0, eve::minf(eve::as<T>())), eve::zero(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_jn(2, eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_jn(3, eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);

    TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(0), eve::minf(eve::as<T>())), eve::zero(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(2), eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(3), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);

    TTS_ULP_EQUAL(eve::cyl_bessel_jn(I_t(0), eve::minf(eve::as<T>())), eve::zero(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_jn(I_t(2), eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_jn(I_t(3), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

#if defined(__cpp_lib_math_special_functions)
  auto std_cyl_bessel_jn  = [](auto nn, auto xx) -> v_t { return std::cyl_bessel_j(double(nn), double(xx)); };
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(3, v_t(1000)), std_cyl_bessel_jn(3, v_t(1000)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(2, v_t(500)), std_cyl_bessel_jn(2, v_t(500)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(2, v_t(10)), std_cyl_bessel_jn(2, v_t(10)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(3, v_t(5)), std_cyl_bessel_jn(3, v_t(5)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(2, v_t(0.1)), std_cyl_bessel_jn(2, v_t(0.1)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(3, v_t(0.2)), std_cyl_bessel_jn(3, v_t(0.2)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(10, v_t(8)), std_cyl_bessel_jn(10, v_t(8)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(10, v_t(8)), std_cyl_bessel_jn(10, v_t(8)), 20000.0);

  TTS_ULP_EQUAL(eve::cyl_bessel_jn(3, T(1000)), T(std_cyl_bessel_jn(3, v_t(1000))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(2, T(500)), T(std_cyl_bessel_jn(2, v_t(500))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(2, T(10)), T(std_cyl_bessel_jn(2, v_t(10))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(3, T(5)), T(std_cyl_bessel_jn(3, v_t(5))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(2, T(0.1)), T(std_cyl_bessel_jn(2, v_t(0.1))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(3, T(0.2)), T(std_cyl_bessel_jn(3, v_t(0.2))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(10, T(8)), T(std_cyl_bessel_jn(10, v_t(8))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(10, T(8)), T(std_cyl_bessel_jn(10, v_t(8))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(3), T(1000)), T(std_cyl_bessel_jn(3, v_t(1000))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(2), T(500)), T(std_cyl_bessel_jn(2, v_t(500))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(2), T(10)), T(std_cyl_bessel_jn(2, v_t(10))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(3), T(5)), T(std_cyl_bessel_jn(3, v_t(5))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(2), T(0.1)), T(std_cyl_bessel_jn(2, v_t(0.1))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(3), T(0.2)), T(std_cyl_bessel_jn(3, v_t(0.2))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(10), T(8)), T(std_cyl_bessel_jn(10, v_t(8))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(10), T(8)), T(std_cyl_bessel_jn(10, v_t(8))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(I_t(3), T(1000)), T(std_cyl_bessel_jn(3, v_t(1000))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(I_t(2), T(500)), T(std_cyl_bessel_jn(2, v_t(500))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(I_t(2), T(10)), T(std_cyl_bessel_jn(2, v_t(10))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(I_t(3), T(5)), T(std_cyl_bessel_jn(3, v_t(5))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(I_t(2), T(0.1)), T(std_cyl_bessel_jn(2, v_t(0.1))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(I_t(3), T(0.2)), T(std_cyl_bessel_jn(3, v_t(0.2))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(I_t(10), T(8)), T(std_cyl_bessel_jn(10, v_t(8))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(I_t(10), T(8)), T(std_cyl_bessel_jn(10, v_t(8))), 20000.0);

  TTS_RELATIVE_EQUAL(eve::cyl_bessel_jn(n, a0), tts::map(std_cyl_bessel_jn, n, a0), 0.0025);
#else
  TTS_PASS("No support for std::cyl_bessel_j");
#endif
};

//==================================================================================================
//== non integral orders
//==================================================================================================
TTS_CASE_WITH("Check behavior of cyl_bessel_jn on wide with non integral order",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, 10.0), tts::randoms(0.0, 1000.0)))
<typename T>([[maybe_unused]] T n, [[maybe_unused]] T a0)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(0.5), eve::minf(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(2.5), eve::inf(eve::as<v_t>())), v_t(0), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(3.5), eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(0.5), eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(2.5), eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(3.5), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(0.5), eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(2.5), eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(3.5), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

#if defined(__cpp_lib_math_special_functions)
  auto std_cyl_bessel_jn = [](auto nn, auto xx) -> v_t { return std::cyl_bessel_j(double(nn), double(xx)); };
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(3.5), v_t(1000)), std_cyl_bessel_jn(v_t(3.5), v_t(1000)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(2.5), v_t(500)), std_cyl_bessel_jn(v_t(2.5), v_t(500)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(2.5), v_t(10)), std_cyl_bessel_jn(v_t(2.5), v_t(10)), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(3.5), v_t(5)), std_cyl_bessel_jn(v_t(3.5), v_t(5)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(2.5), v_t(0.1)), std_cyl_bessel_jn(v_t(2.5), v_t(0.1)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(3.5), v_t(0.2)), std_cyl_bessel_jn(v_t(3.5), v_t(0.2)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(10.5), v_t(8)), std_cyl_bessel_jn(v_t(10.5), v_t(8)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(10.5), v_t(8)), std_cyl_bessel_jn(v_t(10.5), v_t(8)), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(3.5), T(1000)), T(std_cyl_bessel_jn(v_t(3.5), v_t(1000))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(2.5), T(500)), T(std_cyl_bessel_jn(v_t(2.5), v_t(500))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(2.5), T(10)), T(std_cyl_bessel_jn(v_t(2.5), v_t(10))), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(3.5), T(5)), T(std_cyl_bessel_jn(v_t(3.5), v_t(5))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(2.5), T(0.1)), T(std_cyl_bessel_jn(v_t(2.5), v_t(0.1))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(3.5), T(0.2)), T(std_cyl_bessel_jn(v_t(3.5), v_t(0.2))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(10.5), T(8)), T(std_cyl_bessel_jn(v_t(10.5), v_t(8))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(v_t(10.5), T(8)), T(std_cyl_bessel_jn(v_t(10.5), v_t(8))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(3.5), T(1000)), T(std_cyl_bessel_jn(v_t(3.5), v_t(1000))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(2.5), T(500)), T(std_cyl_bessel_jn(v_t(2.5), v_t(500))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(2.5), T(10)), T(std_cyl_bessel_jn(v_t(2.5), v_t(10))), 5.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(3.5), T(5)), T(std_cyl_bessel_jn(v_t(3.5), v_t(5))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(2.5), T(0.1)), T(std_cyl_bessel_jn(v_t(2.5), v_t(0.1))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(3.5), T(0.2)), T(std_cyl_bessel_jn(v_t(3.5), v_t(0.2))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(10.5), T(8)), T(std_cyl_bessel_jn(v_t(10.5), v_t(8))), 20000.0);
  TTS_ULP_EQUAL(eve::cyl_bessel_jn(T(10.5), T(8)), T(std_cyl_bessel_jn(v_t(10.5), v_t(8))), 20000.0);

  TTS_RELATIVE_EQUAL(eve::cyl_bessel_jn(n, a0),   tts::map(std_cyl_bessel_jn, n, a0)   , 0.001);
#else
  TTS_PASS("No support for std::cyl_bessel_j");
#endif
};
