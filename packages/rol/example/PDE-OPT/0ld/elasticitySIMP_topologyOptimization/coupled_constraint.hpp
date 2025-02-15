// @HEADER
// *****************************************************************************
//               Rapid Optimization Library (ROL) Package
//
// Copyright 2014 NTESS and the ROL contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

#ifndef ROL_CoupledConstraint_SimOpt_H
#define ROL_CoupledConstraint_SimOpt_H

#include "ROL_Constraint_SimOpt.hpp"

#include "constraint.hpp"
#include "volume_constraint_SimOpt.hpp"

#include "ROL_TpetraMultiVector.hpp"
#include "ROL_StdVector.hpp"
#include "Amesos2.hpp"

template<class Real>
class EqualityConstraint_PDEOPT_ElasticitySIMP_Coupled : public ROL::Constraint_SimOpt<Real> {
private:
  const ROL::Ptr<EqualityConstraint_PDEOPT_ElasticitySIMP<Real> > pde_;
  const ROL::Ptr<EqualityConstraint_PDEOPT_ElasticitySIMP_Volume_SimOpt<Real> > vol_;

public:
  EqualityConstraint_PDEOPT_ElasticitySIMP_Coupled(const ROL::Ptr<EqualityConstraint_PDEOPT_ElasticitySIMP<Real> > &pde,
                                                   const ROL::Ptr<EqualityConstraint_PDEOPT_ElasticitySIMP_Volume_SimOpt<Real> > &vol) : pde_(pde), vol_(vol) {}

  using ROL::Constraint_SimOpt<Real>::value;
  void value(ROL::Vector<Real> &c, const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) 
  {
    ROL::Ptr<std::vector<Real> > cp = (dynamic_cast<ROL::StdVector<Real>&>(c)).getVector();
    ROL::Ptr<const Tpetra::MultiVector<> > up = (dynamic_cast<const ROL::TpetraMultiVector<Real>&>(u)).getVector();
    ROL::Ptr<const Tpetra::MultiVector<> > zp = (dynamic_cast<const ROL::TpetraMultiVector<Real>&>(z)).getVector();

    pde_->value(*cp1,*up,*zp,tol);
    vol_->value(*cp2,*up,*zp,tol);
  }


  void applyJacobian_1(ROL::Vector<Real> &jv, const ROL::Vector<Real> &v, const ROL::Vector<Real> &u,
                       const ROL::Vector<Real> &z, Real &tol) 
  {
    ROL::Ptr<std::vector<Real> > jvp = (dynamic_cast<ROL::StdVector<Real>&>(jv)).getVector();
    ROL::Ptr<const Tpetra::MultiVector<> > vp = (dynamic_cast<const ROL::TpetraMultiVector<Real>&>(v)).getVector();
    ROL::Ptr<const Tpetra::MultiVector<> > up = (dynamic_cast<const ROL::TpetraMultiVector<Real>&>(u)).getVector();
    ROL::Ptr<const Tpetra::MultiVector<> > zp = (dynamic_cast<const ROL::TpetraMultiVector<Real>&>(z)).getVector();

    pde_->applyJacobian_1(*jvp1,*vp,*up,*zp,tol);
    vol_->applyJacobian_1(*jvp2,*vp,*up,*zp,tol);
  }


  void applyJacobian_2(ROL::Vector<Real> &jv, const ROL::Vector<Real> &v, const ROL::Vector<Real> &u,
                       const ROL::Vector<Real> &z, Real &tol) 
  {
    ROL::Ptr<std::vector<Real> > jvp = (dynamic_cast<ROL::StdVector<Real>&>(jv)).getVector();
    ROL::Ptr<const Tpetra::MultiVector<> > vp = (dynamic_cast<const ROL::TpetraMultiVector<Real>&>(v)).getVector();
    ROL::Ptr<const Tpetra::MultiVector<> > up = (dynamic_cast<const ROL::TpetraMultiVector<Real>&>(u)).getVector();
    ROL::Ptr<const Tpetra::MultiVector<> > zp = (dynamic_cast<const ROL::TpetraMultiVector<Real>&>(z)).getVector();

    pde_->applyJacobian_2(*jvp1,*vp,*up,*zp,tol);
    vol_->applyJacobian_2(*jvp2,*vp,*up,*zp,tol);
  }


  void applyAdjointJacobian_1(ROL::Vector<Real> &ajv, const ROL::Vector<Real> &v, const ROL::Vector<Real> &u,
                              const ROL::Vector<Real> &z, Real &tol) 
  {
    ROL::Ptr<std::vector<Real> > ajvp = (dynamic_cast<ROL::StdVector<Real>&>(jv)).getVector();
    ROL::Ptr<const Tpetra::MultiVector<> > vp = (dynamic_cast<const ROL::TpetraMultiVector<Real>&>(v)).getVector();
    ROL::Ptr<const Tpetra::MultiVector<> > up = (dynamic_cast<const ROL::TpetraMultiVector<Real>&>(u)).getVector();
    ROL::Ptr<const Tpetra::MultiVector<> > zp = (dynamic_cast<const ROL::TpetraMultiVector<Real>&>(z)).getVector();

    pde_->applyAdjointJacobian_1(*ajvp1,*vp,*up,*zp,tol);
    vol_->applyAdjointJacobian_1(*ajvp2,*vp,*up,*zp,tol);
  }


  void applyAdjointJacobian_2(ROL::Vector<Real> &ajv, const ROL::Vector<Real> &v, const ROL::Vector<Real> &u,
                              const ROL::Vector<Real> &z, Real &tol) 
  {
    ROL::Ptr<Tpetra::MultiVector<> > ajvp = (dynamic_cast<ROL::TpetraMultiVector<Real>&>(ajv)).getVector();
    ROL::Ptr<const std::vector<Real> > vp = (dynamic_cast<const ROL::StdVector<Real>&>(v)).getVector();
    ROL::Ptr<const Tpetra::MultiVector<> > up = (dynamic_cast<const ROL::TpetraMultiVector<Real>&>(u)).getVector();
    ROL::Ptr<const Tpetra::MultiVector<> > zp = (dynamic_cast<const ROL::TpetraMultiVector<Real>&>(z)).getVector();

    pde_->applyAdjointJacobian_2(*ajvp1,*vp,*up,*zp,tol);
    vol_->applyAdjointJacobian_2(*ajvp2,*vp,*up,*zp,tol);
  }


  void applyAdjointHessian_11(ROL::Vector<Real> &ahwv, const ROL::Vector<Real> &w, const ROL::Vector<Real> &v,
                              const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) 
  {
	  ahwv.zero();
  }


  void applyAdjointHessian_12(ROL::Vector<Real> &ahwv, const ROL::Vector<Real> &w, const ROL::Vector<Real> &v,
                              const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) 
  {
	  ahwv.zero();
  }


  void applyAdjointHessian_21(ROL::Vector<Real> &ahwv, const ROL::Vector<Real> &w, const ROL::Vector<Real> &v,
                              const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) 
  {
	  ahwv.zero();
  }


  void applyAdjointHessian_22(ROL::Vector<Real> &ahwv, const ROL::Vector<Real> &w, const ROL::Vector<Real> &v,
                              const ROL::Vector<Real> &u, const ROL::Vector<Real> &z, Real &tol) 
  {
	  ahwv.zero();	
  }

};

#endif
