#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_zeta_2() { return eve::zeta_2(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> zeta_2(as<wide_ft>())                 = " << eve::zeta_2(eve::as<wide_ft>())                << std::endl
            << "-> zeta_2(as(wxf))                       = " << eve::zeta_2(eve::as(wxf))                      << std::endl
            << "-> zeta_2[upper](as<wide_ft>())         = " << eve::zeta_2[eve::upper](eve::as<wide_ft>())   << std::endl
            << "-> zeta_2[upper](as(wxf))               = " << eve::zeta_2[eve::upper](eve::as(wxf))         << std::endl
            << "-> zeta_2[lower](as<wide_ft>())       = " << eve::zeta_2[eve::lower](eve::as<wide_ft>()) << std::endl
            << "-> zeta_2[lower](as(wxf))             = " << eve::zeta_2[eve::lower](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> zeta_2(as<wide_dt>())           = " << eve::zeta_2(eve::as<wide_dt>())                << std::endl
            << "-> zeta_2(as(wxd))                 = " << eve::zeta_2(eve::as(wxd))                      << std::endl
            << "-> zeta_2[upper](as<wide_dt>())   = " << eve::zeta_2[eve::upper](eve::as<wide_dt>())   << std::endl
            << "-> zeta_2[upper](as(wxd))         = " << eve::zeta_2[eve::upper](eve::as(wxd))         << std::endl
            << "-> zeta_2[lower](as<wide_dt>()) = " << eve::zeta_2[eve::lower](eve::as<wide_dt>()) << std::endl
            << "-> zeta_2[lower](as(wxd))       = " << eve::zeta_2[eve::lower](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> zeta_2(as<float>())             = " << eve::zeta_2(eve::as(float())) << std::endl
            << "-> zeta_2(as<xf))                  = " << eve::zeta_2(eve::as(xf))      << std::endl
            << "-> zeta_2(as<double>())            = " << eve::zeta_2(eve::as(double()))<< std::endl
            << "-> zeta_2(as<xd))                  = " << eve::zeta_2(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr zeta_2            = " << constexpr_zeta_2<float>() << std::endl;

  return 0;
}
