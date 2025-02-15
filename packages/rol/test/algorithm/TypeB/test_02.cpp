// @HEADER
// *****************************************************************************
//               Rapid Optimization Library (ROL) Package
//
// Copyright 2014 NTESS and the ROL contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

/*! \file  test_23.cpp
    \brief Validate projected gradient algorithm.
*/

#include "ROL_HS21.hpp"
#include "ROL_HS41.hpp"
#include "ROL_HS53.hpp"
#include "ROL_TypeB_LinMoreAlgorithm.hpp"

#include "ROL_Stream.hpp"
#include "Teuchos_GlobalMPISession.hpp"

typedef double RealT;

int main(int argc, char *argv[]) {

  Teuchos::GlobalMPISession mpiSession(&argc, &argv);

  // This little trick lets us print to std::cout only if a
  // (dummy) command-line argument is provided.
  int iprint     = argc - 1;
  ROL::Ptr<std::ostream> outStream;
  ROL::nullstream bhs; // outputs nothing
  if (iprint > 0)
    outStream = ROL::makePtrFromRef(std::cout);
  else
    outStream = ROL::makePtrFromRef(bhs);

  int errorFlag = 0;

  try {
    RealT tol = std::sqrt(ROL::ROL_EPSILON<RealT>());

    ROL::ParameterList list;
    list.sublist("Status Test").set("Gradient Tolerance",1e-8);
    list.sublist("Status Test").set("Constraint Tolerance",1e-8);
    list.sublist("Status Test").set("Step Tolerance",1e-12);
    list.sublist("Status Test").set("Iteration Limit", 250);
    list.sublist("Step").set("Type","Line Search");
    list.sublist("General").set("Output Level",iprint);

    ROL::Ptr<ROL::Vector<RealT>>     sol, mul;
    ROL::Ptr<ROL::Objective<RealT>>  obj;
    ROL::Ptr<ROL::Constraint<RealT>> con;
    ROL::Ptr<ROL::BoundConstraint<RealT>> bnd;
    ROL::Ptr<ROL::TypeB::LinMoreAlgorithm<RealT>> algo;
    ROL::Ptr<ROL::Problem<RealT>> prob;
    std::vector<RealT> data;
    RealT e1, e2, e3, e4, e5, err;

    *outStream << std::endl << "Hock and Schittkowski Problem #41" << std::endl << std::endl;
    ROL::ZOO::getHS41<RealT> HS41;
    obj = HS41.getObjective();
    sol = HS41.getInitialGuess();
    con = HS41.getEqualityConstraint();
    mul = HS41.getEqualityMultiplier();
    bnd = HS41.getBoundConstraint();

    list.sublist("General").sublist("Polyhedral Projection").set("Type","Dai-Fletcher");
    prob = ROL::makePtr<ROL::Problem<RealT>>(obj,sol);
    prob->addBoundConstraint(bnd);
    prob->addLinearConstraint("con1",con,mul);
    prob->setProjectionAlgorithm(list);
    prob->finalize(false,true,*outStream);
    algo = ROL::makePtr<ROL::TypeB::LinMoreAlgorithm<RealT>>(list);
    algo->run(*prob,*outStream);

    data = *ROL::staticPtrCast<ROL::StdVector<RealT>>(sol)->getVector();
    *outStream << "  Result:     x1 = " << data[0] << "  x2 = " << data[1]
               << "  x3 = " << data[2] << "  x4 = " << data[3] << std::endl;
    e1 = (data[0]-static_cast<RealT>(2.0/3.0));
    e2 = (data[1]-static_cast<RealT>(1.0/3.0));
    e3 = (data[2]-static_cast<RealT>(1.0/3.0));
    e4 = (data[3]-static_cast<RealT>(2.0));
    err = std::max(std::max(std::max(std::abs(e1),std::abs(e2)),std::abs(e3)),std::abs(e4));
    *outStream << "  Max-Error = " << err << std::endl;
    errorFlag += (err > tol ? 1 : 0);

    *outStream << std::endl << "Hock and Schittkowski Problem #53" << std::endl << std::endl;
    ROL::ZOO::getHS53<RealT> HS53;
    obj = HS53.getObjective();
    sol = HS53.getInitialGuess();
    con = HS53.getEqualityConstraint();
    mul = HS53.getEqualityMultiplier();
    bnd = HS53.getBoundConstraint();

    list.sublist("General").sublist("Polyhedral Projection").set("Type","Semismooth Newton");
    prob = ROL::makePtr<ROL::Problem<RealT>>(obj,sol);
    prob->addBoundConstraint(bnd);
    prob->addLinearConstraint("con1",con,mul);
    prob->setProjectionAlgorithm(list);
    prob->finalize(false,true,*outStream);
    algo = ROL::makePtr<ROL::TypeB::LinMoreAlgorithm<RealT>>(list);
    algo->run(*prob,*outStream);

    data = *ROL::staticPtrCast<ROL::StdVector<RealT>>(sol)->getVector();
    *outStream << "  Result:     x1 = " << data[0] << "  x2 = " << data[1]
               << "  x3 = " << data[2] << "  x4 = " << data[3]
               << "  x5 = " << data[4] << std::endl;
    e1 = (data[0]-static_cast<RealT>(-33.0/43.0));
    e2 = (data[1]-static_cast<RealT>( 11.0/43.0));
    e3 = (data[2]-static_cast<RealT>( 27.0/43.0));
    e4 = (data[3]-static_cast<RealT>( -5.0/43.0));
    e5 = (data[4]-static_cast<RealT>( 11.0/43.0));
    err = std::max(std::max(std::max(std::max(std::abs(e1),std::abs(e2)),std::abs(e3)),std::abs(e4)),std::abs(e5));
    *outStream << "  Max-Error = " << err << std::endl;
    errorFlag += (err > tol ? 1 : 0);

    ROL::Ptr<ROL::Vector<RealT>>          imul;
    ROL::Ptr<ROL::Constraint<RealT>>      icon;
    ROL::Ptr<ROL::BoundConstraint<RealT>> ibnd;

    list.sublist("General").sublist("Polyhedral Projection").set("Type","Dai-Fletcher");
    *outStream << std::endl << "Hock and Schittkowski Problem #21" << std::endl << std::endl;
    ROL::ZOO::getHS21<RealT> HS21;
    obj  = HS21.getObjective();
    sol  = HS21.getInitialGuess();
    bnd  = HS21.getBoundConstraint();
    icon = HS21.getInequalityConstraint();
    imul = HS21.getInequalityMultiplier();
    ibnd = HS21.getSlackBoundConstraint();

    prob = ROL::makePtr<ROL::Problem<RealT>>(obj,sol);
    prob->addBoundConstraint(bnd);
    prob->addLinearConstraint("con1",icon,imul,ibnd);
    prob->setProjectionAlgorithm(list);
    prob->finalize(false,true,*outStream);
    algo = ROL::makePtr<ROL::TypeB::LinMoreAlgorithm<RealT>>(list);
    algo->run(*prob,*outStream);

    data = *ROL::staticPtrCast<ROL::StdVector<RealT>>(sol)->getVector();
    *outStream << "  Result:     x1 = " << data[0] << "  x2 = " << data[1] << std::endl;
    e1 = (data[0]-static_cast<RealT>(2));
    e2 = (data[1]-static_cast<RealT>(0));
    err = std::max(std::abs(e1),std::abs(e2));
    *outStream << "  Max-Error = " << err << std::endl;
    errorFlag += (err > tol ? 1 : 0);
  }
  
  catch (std::logic_error& err) {
    *outStream << err.what() << "\n";
    errorFlag = -1000;
  }; // end try

  if (errorFlag != 0)
    std::cout << "End Result: TEST FAILED\n";
  else
    std::cout << "End Result: TEST PASSED\n";

  return 0;
}

