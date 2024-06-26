#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_rsqrt_pi() { return eve::rsqrt_pi(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> rsqrt_pi(as<wide_ft>())       = " << eve::rsqrt_pi(eve::as<wide_ft>())            << std::endl
            << "-> rsqrt_pi(as(wxf))             = " << eve::rsqrt_pi(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> rsqrt_pi(as<float>())         = " << eve::rsqrt_pi(eve::as(float())) << std::endl
            << "-> rsqrt_pi(as<xf))              = " << eve::rsqrt_pi(eve::as(xf))      << std::endl;


  std::cout << "-> constexpr rsqrt_pi            = " << constexpr_rsqrt_pi<float>() << std::endl;

  return 0;
}
