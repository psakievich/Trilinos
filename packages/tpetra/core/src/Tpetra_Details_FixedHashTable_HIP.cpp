// @HEADER
// *****************************************************************************
//          Tpetra: Templated Linear Algebra Services Package
//
// Copyright 2008 NTESS and the Tpetra contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

#include "Tpetra_Details_FixedHashTable_decl.hpp"

#if defined(HAVE_TPETRA_EXPLICIT_INSTANTIATION) && defined(KOKKOS_ENABLE_HIP)

#include "TpetraCore_ETIHelperMacros.h"
#include "Tpetra_Details_FixedHashTable_def.hpp"

namespace Tpetra {
namespace Details {

  TPETRA_ETI_MANGLING_TYPEDEFS()

  using hip_device_type = typename Tpetra::KokkosCompat::KokkosHIPWrapperNode::device_type;

#define TPETRA_DETAILS_FIXEDHASHTABLE_INSTANT_HIP( LO, GO ) \
  TPETRA_DETAILS_FIXEDHASHTABLE_INSTANT( LO, GO, hip_device_type )

  TPETRA_INSTANTIATE_LG( TPETRA_DETAILS_FIXEDHASHTABLE_INSTANT_HIP)

  // mfh 26 Sep 2015: Make sure that the {KeyType = LO, ValueType =
  // LO} and {KeyType = int, ValueType = LO} specializations get
  // built, since Directory needs them.

  // KeyType = int doesn't get built if GO = int is disabled.
#ifndef HAVE_TPETRA_INST_INT_INT
#  define TPETRA_DETAILS_FIXEDHASHTABLE_INSTANT_HIP_INT( LO ) \
  TPETRA_DETAILS_FIXEDHASHTABLE_INSTANT( LO, int, hip_device_type ) \

  TPETRA_INSTANTIATE_L( TPETRA_DETAILS_FIXEDHASHTABLE_INSTANT_HIP_INT)

  // FIXME (mfh 26 Sep 2015) Once it becomes possible to disable LO =
  // int, add an instantiation here for {KeyType = LO, ValueType =
  // LO}.  However, this case has likely already been covered above,
  // since disabling LO = int leaves LO = GO = long or long long as
  // the most reasonable options.  (It would be silly to use LO = long
  // and GO = long long if sizeof(long) = sizeof(long long).)

#endif // HAVE_TPETRA_INST_INT_INT

} // namespace Details
} // namespace Tpetra

#endif // defined(HAVE_TPETRA_EXPLICIT_INSTANTIATION) && defined(KOKKOS_ENABLE_HIP)
