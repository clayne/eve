//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/concept/value.hpp>
#include <eve/module/core/constant/eps.hpp>
#include <cmath>

int main()
{
  auto lmax = [](){
    if constexpr(eve::floating_value<EVE_VALUE>) return 2/eve::eps(eve::as<EVE_VALUE>());
    else return eve::valmax(eve::as<EVE_VALUE>());
  }();
  auto lmin = EVE_VALUE(1);

  auto const std__rec = [](EVE_VALUE x) { return EVE_VALUE(1/x); };
  auto const eve__div = []<typename T>(T x) { return eve::div(T(1), x); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__rec) , xp, std__rec, arg0);
  run<EVE_VALUE> (EVE_NAME(eve__div) , xp, eve__div, arg0);
  run<EVE_TYPE>  (EVE_NAME(eve__div) , xp, eve__div, arg0);
  run<EVE_VALUE> (EVE_NAME(eve:rec[eve::raw]) , xp, eve::rec[eve::raw], arg0);
  run<EVE_TYPE>  (EVE_NAME(eve:rec[eve::raw]) , xp, eve::rec[eve::raw], arg0);
  run<EVE_VALUE> (EVE_NAME(eve:rec           ) , xp, eve::rec           , arg0);
  run<EVE_TYPE>  (EVE_NAME(eve:rec           ) , xp, eve::rec           , arg0);
  run<EVE_VALUE> (EVE_NAME(eve:rec[eve::pedantic]) , xp, eve::rec[eve::pedantic], arg0);
  run<EVE_TYPE>  (EVE_NAME(eve:rec[eve::pedantic]) , xp, eve::rec[eve::pedantic], arg0);
}
