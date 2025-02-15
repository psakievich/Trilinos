// @HEADER
// *****************************************************************************
//               Rapid Optimization Library (ROL) Package
//
// Copyright 2014 NTESS and the ROL contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

/*! \file  test_06.cpp
    \brief Test line search.
*/

#define USE_HESSVEC 0

#include "ROL_GetTestProblems.hpp"
#include "ROL_OptimizationSolver.hpp"
#include "ROL_Stream.hpp"
#include "Teuchos_GlobalMPISession.hpp"


#include <iostream>

typedef double RealT;

int main(int argc, char *argv[]) {

  Teuchos::GlobalMPISession mpiSession(&argc, &argv);

  // This little trick lets us print to std::cout only if a (dummy) command-line argument is provided.
  int iprint     = argc - 1;
  ROL::Ptr<std::ostream> outStream;
  ROL::nullstream bhs; // outputs nothing
  if (iprint > 0)
    outStream = ROL::makePtrFromRef(std::cout);
  else
    outStream = ROL::makePtrFromRef(bhs);

  int errorFlag  = 0;

  // *** Test body.

  try {

    std::string filename = "input.xml";
    
    auto parlist = ROL::getParametersFromXmlFile( filename );
    parlist->sublist("General").set("Inexact Hessian-Times-A-Vector",true);
#if USE_HESSVEC
    parlist->sublist("General").set("Inexact Hessian-Times-A-Vector",false);
#endif
    parlist->sublist("Step").set("Type","Line Search");

    *outStream << "\n\n" << ROL::ETestOptProblemToString(ROL::TESTOPTPROBLEM_ROSENBROCK) << "\n\n";

    for ( ROL::EDescent desc = ROL::DESCENT_STEEPEST; desc < ROL::DESCENT_LAST; desc++ ) {
      parlist->sublist("Step").sublist("Line Search").sublist("Descent Method").set("Type", ROL::EDescentToString(desc));
      *outStream << std::endl << std::endl << ROL::EDescentToString(desc) << std::endl << std::endl;
      for (ROL::ELineSearch ls = ROL::LINESEARCH_BACKTRACKING; ls < ROL::LINESEARCH_USERDEFINED; ls++) {
        // Set Up Optimization Problem
        ROL::Ptr<ROL::Vector<RealT> > x0;
        std::vector<ROL::Ptr<ROL::Vector<RealT> > > z;
        ROL::Ptr<ROL::OptimizationProblem<RealT> > problem;
        ROL::GetTestProblem<RealT>(problem,x0,z,ROL::TESTOPTPROBLEM_ROSENBROCK);

        // Get Dimension of Problem
        int dim = x0->dimension();
        parlist->sublist("General").sublist("Krylov").set("Iteration Limit", 2*dim);

        // Error Vector
        ROL::Ptr<ROL::Vector<RealT> > e = x0->clone();
        e->zero();

        // Define Step
        parlist->sublist("Step").sublist("Line Search").sublist("Line-Search Method").set("Type",ROL::ELineSearchToString(ls));
        // Define Solver
        ROL::OptimizationSolver<RealT> solver(*problem,*parlist);

        // Run Solver
        solver.solve(*outStream);

        // Compute Error
        RealT err(0);
        for (int i = 0; i < static_cast<int>(z.size()); ++i) {
          e->set(*x0);
          e->axpy(-1.0,*z[i]);
          if (i == 0) {
            err = e->norm();
          }
          else {
            err = std::min(err,e->norm());
          }
        }
        *outStream << std::endl << "Norm of Error: " << err << std::endl;
        //errorFlag += (int)(e.norm() < std::sqrt(ROL::ROL_EPSILON<RealT>())); 
      }
    }
  }
  catch (std::logic_error& err) {
    *outStream << err.what() << std::endl;
    errorFlag = -1000;
  }; // end try

  if (errorFlag != 0)
    std::cout << "End Result: TEST FAILED" << std::endl;
  else
    std::cout << "End Result: TEST PASSED" << std::endl;

  return 0;

}
