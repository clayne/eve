#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.5f, -2.0f, eve::nan(eve::as<float>()),
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), -eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                      = " << pf << '\n'
            << "-> is_positive(pf)         = " << eve::is_positive(pf) << '\n'
            << "-> is_positive[pf < 2](pf) = " << eve::is_positive[pf < 2](pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf              = " << xf << '\n'
            << "-> is_positive(xf) = " << eve::is_positive(xf) << '\n';
  return 0;
}
