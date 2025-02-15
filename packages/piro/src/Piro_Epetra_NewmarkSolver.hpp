// @HEADER
// *****************************************************************************
//        Piro: Strategy package for embedded analysis capabilitites
//
// Copyright 2010 NTESS and the Piro contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

#ifndef PIRO_EPETRA_NEWMARKSOLVER_H
#define PIRO_EPETRA_NEWMARKSOLVER_H

#include <iostream>

#include "Epetra_Vector.h"
#include "EpetraExt_ModelEvaluator.h"
#include "NOX_Epetra_Observer.H"
#include "Teuchos_ParameterList.hpp"
#include "Teuchos_RCP.hpp"
#include "Piro_Epetra_NOXSolver.hpp"

namespace Piro {
namespace Epetra {

/** \ingroup Piro_Epetra_solver_grp */
class NewmarkDecorator
    : public EpetraExt::ModelEvaluator
{

  typedef double Scalar;

  public:

  /** \name Constructors/initializers */
  //@{

  /** \brief Takes the number of elements in the discretization . */
  NewmarkDecorator( 
                Teuchos::RCP<EpetraExt::ModelEvaluator>& model,
                double beta_, double gamma_
                );

  //@}

  ~NewmarkDecorator();


  /** \name Overridden from EpetraExt::ModelEvaluator . */
  //@{

  Teuchos::RCP<const Epetra_Map> get_g_map(int j) const;
  /** \brief . */
  Teuchos::RCP<const Epetra_Vector> get_p_init(int l) const;
  /** \brief . */
  Teuchos::RCP<Epetra_Operator> create_W() const;
  /** \brief . */
  EpetraExt::ModelEvaluator::InArgs createInArgs() const;
  /** \brief . */
  EpetraExt::ModelEvaluator::OutArgs createOutArgs() const;
  /** \brief . */
  void evalModel( const InArgs& inArgs, const OutArgs& outArgs ) const;

  //! Method to give info to compute xDotDot(x), so that the
  // NOX solver can treat the time dep problem as steady 
  void injectData(const Teuchos::RCP<Epetra_Vector>& acceleration_, 
                  const Teuchos::RCP<Epetra_Vector>& velocity_pred_,
                  const Teuchos::RCP<Epetra_Vector>& displacement_pred_, 
                  double delta_t_, double time_ );

  /** \brief . */
  Teuchos::RCP<const Epetra_Map> get_x_map() const;
  /** \brief . */
  Teuchos::RCP<const Epetra_Map> get_f_map() const;
  /** \brief . */
  Teuchos::RCP<const Epetra_Vector> get_x_init() const;
  /** \brief . */
  Teuchos::RCP<const Epetra_Vector> get_x_dot_init() const;
  /** \brief . */
  Teuchos::RCP<const Epetra_Vector> get_x_dotdot_init() const;
  /** \brief . */
  Teuchos::RCP<const Epetra_Map> get_p_map(int l) const;

  //@}

  private:

   //These are set in the constructor and used in evalModel
   Teuchos::RCP<EpetraExt::ModelEvaluator> model;
   Teuchos::RCP<Epetra_Vector> displacement;
   Teuchos::RCP<Epetra_Vector> velocity;
   Teuchos::RCP<Epetra_Vector> velocity_pred;
   Teuchos::RCP<Epetra_Vector> displacement_pred;
   Teuchos::RCP<Epetra_Vector> acceleration_save;
   double beta;
   double gamma;
   double delta_t;
   double time; 

};


class NewmarkSolver
    : public EpetraExt::ModelEvaluator
{

  typedef double Scalar;

  public:

  /** \name Constructors/initializers */
  //@{

  /** \brief Takes the number of elements in the discretization . */
  NewmarkSolver(Teuchos::RCP<Teuchos::ParameterList> appParams,
                Teuchos::RCP<EpetraExt::ModelEvaluator> model,
                Teuchos::RCP<NOX::Epetra::Observer> observer = Teuchos::null
                );

  //@}

  ~NewmarkSolver();


  /** \name Overridden from EpetraExt::ModelEvaluator . */
  //@{

  Teuchos::RCP<const Epetra_Map> get_g_map(int j) const;
  /** \brief . */
  Teuchos::RCP<const Epetra_Vector> get_p_init(int l) const;
  /** \brief . */
//  Teuchos::RCP<Epetra_Operator> create_W() const;
  /** \brief . */
  EpetraExt::ModelEvaluator::InArgs createInArgs() const;
  /** \brief . */
  EpetraExt::ModelEvaluator::OutArgs createOutArgs() const;
  /** \brief . */
  void evalModel( const InArgs& inArgs, const OutArgs& outArgs ) const;

  private:
  /** \brief . */
  Teuchos::RCP<const Epetra_Map> get_x_map() const;
  /** \brief . */
  Teuchos::RCP<const Epetra_Map> get_f_map() const;
  /** \brief . */
  Teuchos::RCP<const Epetra_Vector> get_x_init() const;
  /** \brief . */
  Teuchos::RCP<const Epetra_Map> get_p_map(int l) const;
  /** \brief . */
  void setProblemParamDefaults(Teuchos::ParameterList* appParams_);
  /** \brief . */
  void setSolverParamDefaults(Teuchos::ParameterList* appParams_);
  /** \brief . */
  Teuchos::RCP<const Teuchos::ParameterList>
    getValidNewmarkParameters() const;

  //@}

  private:
   //These are set in the constructor and used in evalModel
   mutable Teuchos::RCP<Teuchos::ParameterList> appParams;
   Teuchos::RCP<Piro::Epetra::NewmarkDecorator> model;
   Teuchos::RCP<Piro::Epetra::NOXSolver> noxSolver;
   Teuchos::RCP<NOX::Epetra::Observer> observer;
   Teuchos::RCP<Teuchos::FancyOStream> out;
   Teuchos::EVerbosityLevel solnVerbLevel;

   int num_p;
   int num_g;

   int numTimeSteps;
   double t_init, t_final, delta_t;
   double beta, gamma;
};




}
}
#endif
