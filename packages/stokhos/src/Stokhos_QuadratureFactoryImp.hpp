// @HEADER
// *****************************************************************************
//                           Stokhos Package
//
// Copyright 2009 NTESS and the Stokhos contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

#include "Teuchos_Assert.hpp"

#include "Stokhos_BasisFactory.hpp"
#include "Stokhos_TensorProductQuadrature.hpp"
#include "Stokhos_SparseGridQuadrature.hpp"
#include "Stokhos_ProductBasis.hpp"

template <typename ordinal_type, typename value_type>
Teuchos::RCP<const Stokhos::Quadrature<ordinal_type, value_type> >
Stokhos::QuadratureFactory<ordinal_type, value_type>::
create(Teuchos::ParameterList& sgParams)
{
  // Check if quadrature is already there
  Teuchos::ParameterList& quadParams = sgParams.sublist("Quadrature");
  Teuchos::RCP<const Stokhos::Quadrature<ordinal_type,value_type> > quad = 
    quadParams.template get< Teuchos::RCP<const Stokhos::Quadrature<ordinal_type,value_type> > >("Stochastic Galerkin Quadrature", Teuchos::null);
  if (quad != Teuchos::null)
    return quad;

  // Get basis
  Teuchos::ParameterList& basisParams = sgParams.sublist("Basis");
  Teuchos::RCP< const Stokhos::OrthogPolyBasis<ordinal_type,value_type> > basis;
  if (basisParams.template isType< Teuchos::RCP< const Stokhos::OrthogPolyBasis<ordinal_type,value_type> > >("Stochastic Galerkin Basis"))
    basis = basisParams.template get< Teuchos::RCP<const Stokhos::OrthogPolyBasis<ordinal_type,value_type> > >("Stochastic Galerkin Basis");
  else
    basis = Stokhos::BasisFactory<ordinal_type,value_type>::create(sgParams);
  Teuchos::RCP<const Stokhos::ProductBasis<ordinal_type,value_type> > product_basis = Teuchos::rcp_dynamic_cast<const Stokhos::ProductBasis<ordinal_type,value_type> >(basis, true);

  // Create quadrature
  std::string quad_type = quadParams.get("Type", "Tensor Product");
  if (quad_type == "Tensor Product") {
    if (quadParams.isType<ordinal_type>("Quadrature Order")) {
      ordinal_type order = quadParams.get<ordinal_type>("Quadrature Order");
      quad = 
	Teuchos::rcp(new Stokhos::TensorProductQuadrature<ordinal_type,value_type>(product_basis, order));
    }
    else {
      quad = 
	Teuchos::rcp(new Stokhos::TensorProductQuadrature<ordinal_type,value_type>(product_basis));
    }
  }
  else if (quad_type == "Sparse Grid") {
#ifdef HAVE_STOKHOS_DAKOTA
    ordinal_type level = quadParams.get("Sparse Grid Level", 0);
    value_type dup_tol = quadParams.get("Duplicate Tolerance", 1e-12);
    ordinal_type growth = quadParams.get<ordinal_type>(
      "Growth Rule", Pecos::SLOW_RESTRICTED_GROWTH);
    quad = 
      Teuchos::rcp(new Stokhos::SparseGridQuadrature<ordinal_type,value_type>(
		     product_basis, level, dup_tol, growth));
#else
    TEUCHOS_TEST_FOR_EXCEPTION(true, Teuchos::Exceptions::InvalidParameter,
		       std::endl << 
		       "Error!  Stokhos::QuadratureFactory::create():  " <<
		       "Sparse Grid Quadrature requires Dakota!" << std::endl);
#endif
  }
  else
    TEUCHOS_TEST_FOR_EXCEPTION(true, Teuchos::Exceptions::InvalidParameter,
		       std::endl << 
		       "Error!  Stokhos::QuadratureFactory::create():  " <<
		       "Invalid quadrature type  " << quad_type << std::endl);

  quadParams.set("Stochastic Galerkin Quadrature", quad);
  return quad;
}
