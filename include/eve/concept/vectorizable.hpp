//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/scalar.hpp>
#include <eve/traits/element_type.hpp>
#include <concepts>

namespace eve
{
  //================================================================================================
  //! @ingroup simd_concepts
  //! @{
  //! @concept integral_scalar_value
  //! @brief Specify that a type represents an integral scalar value.
  //! The concept `integral_scalar_value<T>` is satisfied if and only if T satisfies
  //! `eve::arithmetic_scalar_value<T>` and `std::integral<T>`.
  //!
  //! @groupheader{Examples}
  //! - `std::int32_t`
  //================================================================================================
  template<typename T>
  concept integral_scalar_value  = arithmetic_scalar_value<T> && std::integral<translate_element_type_t<T>>;
  //================================================================================================
  //! @}
  //================================================================================================

  //================================================================================================
  //! @ingroup simd_concepts
  //! @{
  //! @concept signed_scalar_value
  //! @brief Specify that a type represents a signed scalar value.
  //! The concept `signed_scalar_value<T>` is satisfied if and only if T satisfies
  //! `eve::arithmetic_scalar_value<T>` and `std::integral<T>`.
  //!
  //! @groupheader{Examples}
  //! - `std::int32_t`
  //! - `float`
  //================================================================================================
  template<typename T>
  concept signed_scalar_value  = arithmetic_scalar_value<T> && std::is_signed_v<translate_element_type_t<T>>;
  //================================================================================================
  //! @}
  //================================================================================================

  //================================================================================================
  //! @ingroup simd_concepts
  //! @{
  //! @concept unsigned_scalar_value
  //! @brief Specify that a type represents an unsigned scalar value.
  //! The concept `unsigned_scalar_value<T>` is satisfied if and only if T satisfies
  //! `eve::arithmetic_scalar_value<T>` and `std::unsigned_integral<T>`.
  //!
  //! @groupheader{Examples}
  //! - `std::uint32_t`
  //================================================================================================
  template<typename T>
  concept unsigned_scalar_value = arithmetic_scalar_value<T> && std::unsigned_integral<translate_element_type_t<T>>;
  //================================================================================================
  //! @}
  //================================================================================================

  //================================================================================================
  //! @ingroup simd_concepts
  //! @{
  //! @concept signed_integral_scalar_value
  //! @brief Specify that a type represents an integral scalar value.
  //! The concept `unsigned_scalar_value<T>` is satisfied if and only if T satisfies
  //! `eve::arithmetic_scalar_value<T>` and `std::signed_integral<T>`.
  //!
  //! @groupheader{Examples}
  //! - `std::int32_t`
  //================================================================================================
  template<typename T>
  concept signed_integral_scalar_value = arithmetic_scalar_value<T> && std::signed_integral<translate_element_type_t<T>>;
  //================================================================================================
  //! @}
  //================================================================================================

  //================================================================================================
  //! @ingroup simd_concepts
  //! @{
  //! @concept floating_scalar_value
  //! @brief Specify that a type represents a floating scalar value.
  //! The concept `unsigned_scalar_value<T>` is satisfied if and only if T satisfies
  //! `eve::arithmetic_scalar_value<T>` and `std::floating_point<T>`.
  //!
  //! @groupheader{Examples}
  //! - `float`
  //! - `double`
  //================================================================================================
  template<typename T>
  concept floating_scalar_value = arithmetic_scalar_value<T> && std::floating_point<translate_element_type_t<T>>;
  //================================================================================================
  //! @}
  //================================================================================================
}
