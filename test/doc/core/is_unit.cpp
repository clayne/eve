#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -0.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf          = " << pf << '\n'
            << "-> is_unit(pf) = " << eve::is_unit(pf) << '\n'
            << "-> is_unit[pf > 0](pf) = " << eve::is_unit[pf > 0](pf) << '\n';
  return 0;
}
