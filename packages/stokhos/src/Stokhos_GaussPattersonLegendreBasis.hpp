// @HEADER
// *****************************************************************************
//                           Stokhos Package
//
// Copyright 2009 NTESS and the Stokhos contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

#ifndef STOKHOS_GAUSS_PATTERSON_LEGENDRE_BASIS_HPP
#define STOKHOS_GAUSS_PATTERSON_LEGENDRE_BASIS_HPP

#include "Stokhos_LegendreBasis.hpp"

namespace Stokhos {

  //! Legendre polynomial basis using Gauss-Patterson quadrature points
  /*!
   * This is the same as Stokhos::LegendreBasis, but uses Gauss-Patterson
   * quadrature points (instead of Gauss-Legendre).
   */
  template <typename ordinal_type, typename value_type>
  class GaussPattersonLegendreBasis : 
    public LegendreBasis<ordinal_type, value_type> {
  public:

    //! Constructor
    /*!
     * \param p order of the basis
     * \param normalize whether polynomials should be given unit norm
     */
    GaussPattersonLegendreBasis(ordinal_type p, bool normalize = false,
				bool isotropic = false);

    //! Destructor
    ~GaussPattersonLegendreBasis();

    //! \name Implementation of Stokhos::OneDOrthogPolyBasis methods
    //@{ 

    /*! 
     * \brief Compute quadrature points, weights, and values of 
     * basis polynomials at given set of points \c points.
     */
    /*!
     * \c quad_order specifies the order to which the quadrature should be
     * accurate, not the number of quadrature points which for Clenshaw-Curtis
     * points is equal to the number of points
     */
    virtual void 
    getQuadPoints(ordinal_type quad_order,
		  Teuchos::Array<value_type>& points,
		  Teuchos::Array<value_type>& weights,
		  Teuchos::Array< Teuchos::Array<value_type> >& values) const;

    /*!
     * Return polynomial degree of exactness for a given number of quadrature
     * points.
     */
    virtual ordinal_type quadDegreeOfExactness(ordinal_type n) const;

    /*! 
     * \brief Clone this object with the option of building a higher order
     * basis.
     */
    /*!
     * This method is following the Prototype pattern (see Design Pattern's textbook).
     * The slight variation is that it allows the order of the polynomial to be modified,
     * otherwise an exact copy is formed. The use case for this is creating basis functions
     * for column indices in a spatially varying adaptive refinement context.
     */
    virtual Teuchos::RCP<OneDOrthogPolyBasis<ordinal_type,value_type> > cloneWithOrder(ordinal_type p) const;

    //! Evaluate coefficient growth rule for Smolyak-type bases
    virtual ordinal_type coefficientGrowth(ordinal_type n) const;

    //! Evaluate point growth rule for Smolyak-type bases
    virtual ordinal_type pointGrowth(ordinal_type n) const;

    //@}

  protected:

    //! Copy constructor with specified order
    GaussPattersonLegendreBasis(ordinal_type p, 
				const GaussPattersonLegendreBasis& basis);

  private:

    // Prohibit copying
    GaussPattersonLegendreBasis(const GaussPattersonLegendreBasis&);

    // Prohibit Assignment
    GaussPattersonLegendreBasis& operator=(const GaussPattersonLegendreBasis& b);

  protected:

    //! Flag determining if expansion is iostropic (same basis in every dim)
    bool isotropic;

  }; // class GaussPattersonLegendreBasis

} // Namespace Stokhos

// Include template definitions
#include "Stokhos_GaussPattersonLegendreBasisImp.hpp"

#endif
