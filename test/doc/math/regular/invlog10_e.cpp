#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_invlog10_e() { return eve::invlog10_e(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> invlog10_e(as<wide_ft>())                 = " << eve::invlog10_e(eve::as<wide_ft>())                << std::endl
            << "-> invlog10_e(as(wxf))                       = " << eve::invlog10_e(eve::as(wxf))                      << std::endl
            << "-> invlog10_e[upper](as<wide_ft>())         = " << eve::invlog10_e[eve::upper](eve::as<wide_ft>())   << std::endl
            << "-> invlog10_e[upper](as(wxf))               = " << eve::invlog10_e[eve::upper](eve::as(wxf))         << std::endl
            << "-> invlog10_e[lower](as<wide_ft>())       = " << eve::invlog10_e[eve::lower](eve::as<wide_ft>()) << std::endl
            << "-> invlog10_e[lower](as(wxf))             = " << eve::invlog10_e[eve::lower](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> invlog10_e(as<wide_dt>())           = " << eve::invlog10_e(eve::as<wide_dt>())                << std::endl
            << "-> invlog10_e(as(wxd))                 = " << eve::invlog10_e(eve::as(wxd))                      << std::endl
            << "-> invlog10_e[upper](as<wide_dt>())   = " << eve::invlog10_e[eve::upper](eve::as<wide_dt>())   << std::endl
            << "-> invlog10_e[upper](as(wxd))         = " << eve::invlog10_e[eve::upper](eve::as(wxd))         << std::endl
            << "-> invlog10_e[lower](as<wide_dt>()) = " << eve::invlog10_e[eve::lower](eve::as<wide_dt>()) << std::endl
            << "-> invlog10_e[lower](as(wxd))       = " << eve::invlog10_e[eve::lower](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> invlog10_e(as<float>())             = " << eve::invlog10_e(eve::as(float())) << std::endl
            << "-> invlog10_e(as<xf))                  = " << eve::invlog10_e(eve::as(xf))      << std::endl
            << "-> invlog10_e(as<double>())            = " << eve::invlog10_e(eve::as(double()))<< std::endl
            << "-> invlog10_e(as<xd))                  = " << eve::invlog10_e(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr invlog10_e            = " << constexpr_invlog10_e<float>() << std::endl;

  return 0;
}
