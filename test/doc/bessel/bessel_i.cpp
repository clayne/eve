#include <eve/eve.hpp>
#include <eve/module/bessel.hpp>
#include <iostream>

int main()
{
   eve::wide<double> wdf([](auto i, auto c)->double{ return 2*(i-c/2);});
   eve::wide<std::uint64_t> wu([](auto i, auto )->std::uint64_t{ return 2*i;});
   eve::wide wd{0.5, 1.5, 0.1, 1.0, 19.0, 0.0, 0.0, 10000.0};
   eve::wide m{0.5, -1.0, 1.5, -2.0, 2.5, -2.6, 3.2, -12.0};

   std::cout << "<- wdf = " << wdf << "\n";
   std::cout << "<- wu = " << wu << "\n";
   std::cout << "<- m  = " << m << "\n";
   std::cout << "<- wd  = " << wd << "\n";

   std::cout << "-> bessel_j(wu, wdf)                = " << eve::bessel_j(wu, wdf) << "\n";
   std::cout << "-> bessel_j[ignore_last(2)](wu, wdf)= " << eve::bessel_j[eve::ignore_last(2)](wu, wdf) << "\n";
   std::cout << "-> bessel_j[wu != 2u](wu, wdf)      = " << eve::bessel_j[wu != 2u](wu, wdf) << "\n";
   std::cout << "-> bessel_j(m, wd)                  = " << eve::bessel_j(m, wd) << "\n";
   std::cout << "-> bessel_j[spherical](m, wd)       = " << eve::bessel_j[eve::spherical](m, wd) << "\n";
}
