#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_sqrt_2pi() { return eve::sqrt_2pi(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> sqrt_2pi(as<wide_ft>())                 = " << eve::sqrt_2pi(eve::as<wide_ft>())                << std::endl
            << "-> sqrt_2pi(as(wxf))                       = " << eve::sqrt_2pi(eve::as(wxf))                      << std::endl
            << "-> sqrt_2pi[upper](as<wide_ft>())         = " << eve::sqrt_2pi[eve::upper](eve::as<wide_ft>())   << std::endl
            << "-> sqrt_2pi[upper](as(wxf))               = " << eve::sqrt_2pi[eve::upper](eve::as(wxf))         << std::endl
            << "-> sqrt_2pi[lower](as<wide_ft>())       = " << eve::sqrt_2pi[eve::lower](eve::as<wide_ft>()) << std::endl
            << "-> sqrt_2pi[lower](as(wxf))             = " << eve::sqrt_2pi[eve::lower](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> sqrt_2pi(as<wide_dt>())           = " << eve::sqrt_2pi(eve::as<wide_dt>())                << std::endl
            << "-> sqrt_2pi(as(wxd))                 = " << eve::sqrt_2pi(eve::as(wxd))                      << std::endl
            << "-> sqrt_2pi[upper](as<wide_dt>())   = " << eve::sqrt_2pi[eve::upper](eve::as<wide_dt>())   << std::endl
            << "-> sqrt_2pi[upper](as(wxd))         = " << eve::sqrt_2pi[eve::upper](eve::as(wxd))         << std::endl
            << "-> sqrt_2pi[lower](as<wide_dt>()) = " << eve::sqrt_2pi[eve::lower](eve::as<wide_dt>()) << std::endl
            << "-> sqrt_2pi[lower](as(wxd))       = " << eve::sqrt_2pi[eve::lower](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> sqrt_2pi(as<float>())             = " << eve::sqrt_2pi(eve::as(float())) << std::endl
            << "-> sqrt_2pi(as<xf))                  = " << eve::sqrt_2pi(eve::as(xf))      << std::endl
            << "-> sqrt_2pi(as<double>())            = " << eve::sqrt_2pi(eve::as(double()))<< std::endl
            << "-> sqrt_2pi(as<xd))                  = " << eve::sqrt_2pi(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr sqrt_2pi            = " << constexpr_sqrt_2pi<float>() << std::endl;

  return 0;
}
