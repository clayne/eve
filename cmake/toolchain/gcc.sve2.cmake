##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(CMAKE_SYSTEM_NAME Linux     )
set(CMAKE_SYSTEM_PROCESSOR arm  )

set(EVE_USE_PCH OFF)  # https://gcc.gnu.org/bugzilla/show_bug.cgi?id=106491
set(CMAKE_C_COMPILER    aarch64-linux-gnu-gcc-14  )
set(CMAKE_CXX_COMPILER  aarch64-linux-gnu-g++-14  )
set(CMAKE_CXX_FLAGS     "-Wno-psabi -DEVE_NO_FORCEINLINE ${EVE_OPTIONS} -march=armv8-a+sve2 -msve-vector-bits=128" )

set(CMAKE_CROSSCOMPILING_CMD ${PROJECT_SOURCE_DIR}/cmake/toolchain/run_sve128.sh     )
