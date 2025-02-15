// @HEADER
// *****************************************************************************
//                           Stokhos Package
//
// Copyright 2009 NTESS and the Stokhos contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

#ifndef STOKHOS_OPENMP_CRS_PRODUCT_TENSOR_HPP
#define STOKHOS_OPENMP_CRS_PRODUCT_TENSOR_HPP

#include "Kokkos_Core.hpp"

#include "Stokhos_Multiply.hpp"
#include "Stokhos_CrsProductTensor.hpp"
#include "Stokhos_BlockCrsMatrix.hpp"
#include "Stokhos_StochasticProductTensor.hpp"
#include "Stokhos_TinyVec.hpp"

namespace Stokhos {

template< typename ValueType , typename MatrixValue , typename VectorValue >
class Multiply<
  BlockCrsMatrix< StochasticProductTensor< ValueType, CrsProductTensor< ValueType , Kokkos::OpenMP > , Kokkos::OpenMP > , MatrixValue , Kokkos::OpenMP > ,
  Kokkos::View< VectorValue** , Kokkos::LayoutLeft , Kokkos::OpenMP > ,
  Kokkos::View< VectorValue** , Kokkos::LayoutLeft , Kokkos::OpenMP > >
{
public:
  typedef MultiplyImpl<ValueType, MatrixValue, VectorValue, Kokkos::OpenMP> impl_type;
  typedef typename impl_type::matrix_type matrix_type;
  typedef typename impl_type::block_vector_type block_vector_type;

  static void apply( const matrix_type & A ,
                     const block_vector_type & x ,
                     const block_vector_type & y ) {
    impl_type::apply(A,x,y);
  }
};

} // namespace Stokhos

#endif /* #ifndef STOKHOS_OPENMP_CRS_PRODUCT_TENSOR_HPP */
