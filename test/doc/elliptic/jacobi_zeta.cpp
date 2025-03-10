// revision 1
#include <eve/module/elliptic.hpp>
#include <iostream>

eve::wide wf{1.0, 0.0, 0.75, 0.5};
eve::wide wphi{1.0, 1.0e-30, 0.5, 0.0};

int main(){
   std::cout << "<- wf   = " << wf << "\n";
   std::cout << "<- wphi = " << wphi << "\n";

   std::cout << "-> jacobi_zeta(wphi, wf)               = " << eve::jacobi_zeta(wphi, wf) << "\n";
   std::cout << "-> jacobi_zeta[ignore_last(2)](wphi,wf)= " << eve::jacobi_zeta[eve::ignore_last(2)](wphi, wf) << "\n";
   std::cout << "-> jacobi_zeta[wf != 1.0](wphi,wf)     = " << eve::jacobi_zeta[wf != -1.0f](wphi, wf) << "\n";
   std::cout << "-> jacobi_zeta(pio_2[lower], wf)       = " << eve::jacobi_zeta(eve::pio_2[eve::lower](eve::as(wphi)), wf) << '\n';
   std::cout << "-> jacobi_zeta(pio_2[upper], wf)       = " << eve::jacobi_zeta(eve::pio_2[eve::upper](eve::as(wphi)), wf) << '\n';
}
