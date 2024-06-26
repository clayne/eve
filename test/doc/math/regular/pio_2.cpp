#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_pio_2() { return eve::pio_2(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> pio_2(as<wide_ft>())        = " << eve::pio_2(eve::as<wide_ft>())            << std::endl
            << "-> pio_2(as(wxf))              = " << eve::pio_2(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> pio_2(as<float>())         = " << eve::pio_2(eve::as(float())) << std::endl
            << "-> pio_2(as<xf))              = " << eve::pio_2(eve::as(xf))      << std::endl;


  std::cout << "-> constexpr pio_2            = " << constexpr_pio_2<float>() << std::endl;

  return 0;
}
