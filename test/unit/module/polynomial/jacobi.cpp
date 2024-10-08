//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/polynomial.hpp>

#if __has_include(<boost/math/special_functions/jacobi.hpp>)
#include <boost/math/special_functions/jacobi.hpp>
#define EVE_HAS_BOOST
#endif

#if defined(EVE_HAS_BOOST)
//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::jacobi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t  = eve::as_integer_t<v_t>;
  TTS_EXPR_IS( eve::jacobi(i_t(), T(), T(), T())  , T);
  TTS_EXPR_IS( eve::jacobi(i_t(), v_t(), v_t(), v_t())  , v_t);
};

//==================================================================================================
// Tests for eve::jacobi
//==================================================================================================
TTS_CASE_WITH( "Check behavior of diff jacobi on wide"
             , eve::test::simd::ieee_reals
             , tts::generate(tts::between(-1.0, 1.0)
                            , tts::between(-1.0, 1.0)
                            , tts::between(-1.0, 1.0)
                            , tts::as_integer(tts::ramp(0))
                            )
             )
  <typename T, typename I>(T const& a0, T const& a1, T const& a2, I const & i0)
{
  auto dt = eve::jacobi(i0, a0, a1, a2);
  auto bdt1 = [&](auto e, auto f, auto g, auto i){return boost::math::jacobi(i, e, f, g); };
  TTS_ULP_EQUAL(dt, tts::map(bdt1, a0, a1, a2, i0), 1000);
};
#else
TTS_CASE("Check return types of jacobi")
{
  TTS_PASS("SKipping due to no reference available");
};
#endif

