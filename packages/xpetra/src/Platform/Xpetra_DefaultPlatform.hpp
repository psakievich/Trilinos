// @HEADER
// *****************************************************************************
//             Xpetra: A linear algebra interface package
//
// Copyright 2012 NTESS and the Xpetra contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

#ifndef XPETRA_DEFAULTPLATFORM_HPP
#define XPETRA_DEFAULTPLATFORM_HPP

#include <Tpetra_KokkosCompat_DefaultNode.hpp>
#include "Xpetra_ConfigDefs.hpp"
#include "Xpetra_SerialPlatform.hpp"
#ifdef HAVE_MPI
#include "Xpetra_MpiPlatform.hpp"
#endif

#include "Xpetra_ConfigDefs.hpp"

namespace Xpetra {

/** \brief Returns a default platform appropriate for the enviroment.

The DefaultPlatform mechanism is useful for easily accessing default
Comm and Node types on a particular system.

If HAVE_MPI is defined, then an instance of <tt>MpiPlatform</tt> will be
created.  Otherwise, a <tt>SerialPlatform</tt> is returned.
*/
class DefaultPlatform {
 public:
  //! Typedef indicating the default platform type specified at compile time. For a serial build, this will be SerialPlatform. Otherwise, it will be MpiPlatform.
#ifdef HAVE_MPI
  typedef MpiPlatform<Tpetra::KokkosClassic::DefaultNode::DefaultNodeType> DefaultPlatformType;
#else
  typedef SerialPlatform<Tpetra::KokkosClassic::DefaultNode::DefaultNodeType> DefaultPlatformType;
#endif

  /** \brief Return the default platform.
   */
  static DefaultPlatformType& getDefaultPlatform();

 private:
  static Teuchos::RCP<DefaultPlatformType> platform_;
};

}  // namespace Xpetra

#endif  // XPETRA_DEFAULTPLATFORM_HPP
