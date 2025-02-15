// @HEADER
// *****************************************************************************
//                           Stokhos Package
//
// Copyright 2009 NTESS and the Stokhos contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

#include "Teuchos_UnitTestHarness.hpp"
#include "Teuchos_TestingHelpers.hpp"
#include "Teuchos_UnitTestRepository.hpp"
#include "Teuchos_GlobalMPISession.hpp"

#include "Stokhos.hpp"
#include "Stokhos_UnitTestHelpers.hpp"

namespace PseudoSpectralExpansionUnitTest {

  // Common setup for unit tests that defines what pseudospectral expansion
  // we are testing
  template <typename OrdinalType, typename ValueType>
  struct UnitTestSetup {
    
    typedef Stokhos::SmolyakBasis<OrdinalType,ValueType> product_basis_type;
    ValueType rtol, atol;
    ValueType crtol, catol;
    OrdinalType sz;
    Teuchos::RCP<const product_basis_type> basis;
    Teuchos::RCP<const Stokhos::Quadrature<OrdinalType,ValueType> > quad;
    Teuchos::RCP<const Stokhos::PseudoSpectralOperator<OrdinalType,ValueType> > ps_op;
    Teuchos::RCP<Stokhos::Sparse3Tensor<int,double> > Cijk, Cijk_linear;
    Teuchos::RCP< Stokhos::PseudoSpectralOrthogPolyExpansion<OrdinalType,ValueType> > exp, exp_linear;
    Stokhos::OrthogPolyApprox<OrdinalType,ValueType> x, y, u, u2, cx, cu, cu2, sx, su, su2;
    ValueType a;
    
    UnitTestSetup() {
      rtol = 1e-4;
      atol = 1e-5;
      crtol = 1e-12;
      catol = 1e-12;
      a = 3.1;
      const OrdinalType d = 2;
      const OrdinalType p = 7;
      
      // Create product basis
      Teuchos::Array< Teuchos::RCP<const Stokhos::OneDOrthogPolyBasis<OrdinalType,ValueType> > > bases(d);
      for (OrdinalType i=0; i<d; i++)
	bases[i] = 
	  Teuchos::rcp(new Stokhos::LegendreBasis<OrdinalType,ValueType>(p));

      Stokhos::TotalOrderIndexSet<OrdinalType> coeff_index_set(d, p);
      basis =
	Teuchos::rcp(new product_basis_type(bases, coeff_index_set));
      
      // Tensor product quadrature
      quad = 
	Teuchos::rcp(new Stokhos::TensorProductQuadrature<OrdinalType,ValueType>(basis));

      // Tensor product pseudospectral operator
      ps_op = 
	Teuchos::rcp(new Stokhos::SmolyakPseudoSpectralOperator<OrdinalType,ValueType>(*basis, true, true));

      // Triple product tensor
      Cijk = basis->computeTripleProductTensor();
      Cijk_linear = basis->computeLinearTripleProductTensor();
      
      // Quadrature expansion
      exp = 
	Teuchos::rcp(new Stokhos::PseudoSpectralOrthogPolyExpansion<OrdinalType,ValueType>(basis, Cijk, ps_op));
      exp_linear = 
	Teuchos::rcp(new Stokhos::PseudoSpectralOrthogPolyExpansion<OrdinalType,ValueType>(basis, Cijk_linear, ps_op));
      
      // Create approximation
      sz = basis->size();
      x.reset(basis);
      y.reset(basis);
      u.reset(basis); 
      u2.reset(basis);
      cx.reset(basis, 1);
      x.term(0, 0) = 1.0;
      cx.term(0, 0) = a;
      cu.reset(basis);
      cu2.reset(basis, 1);
      sx.reset(basis, d+1);
      su.reset(basis, d+1);
      su2.reset(basis, d+1);
      for (OrdinalType i=0; i<d; i++) {
	x.term(i, 1) = 0.1;
	sx.term(i, 1) = 0.0;
      }
      y.term(0, 0) = 2.0;
      for (OrdinalType i=0; i<d; i++)
	y.term(i, 1) = 0.25;
    }
    
  };

  // typedef int OrdinalType;
  // typedef double ValueType;
  UnitTestSetup<int,double> setup;

}

// Include unit tests for the above setup class
#include "Stokhos_PseudoSpectralExpansionUnitTest.hpp"

int main( int argc, char* argv[] ) {
  Teuchos::GlobalMPISession mpiSession(&argc, &argv);
  return Teuchos::UnitTestRepository::runUnitTestsFromMain(argc, argv);
}
