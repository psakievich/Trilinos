// @HEADER
// *****************************************************************************
//                           Stokhos Package
//
// Copyright 2009 NTESS and the Stokhos contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

namespace Sacado {
  namespace MP {

    template <typename O, typename T, int N, typename D>
    KOKKOS_INLINE_FUNCTION
    Vector< Stokhos::StaticFixedStorage<O,T,N,D> >
    OPNAME (const Vector< Stokhos::StaticFixedStorage<O,T,N,D> >& a,
            const Vector< Stokhos::StaticFixedStorage<O,T,N,D> >& b)
    {
      using std::OPNAME;
      Vector< Stokhos::StaticFixedStorage<O,T,N,D> > c;
#ifdef STOKHOS_HAVE_PRAGMA_IVDEP
#pragma ivdep
#endif
#ifdef STOKHOS_HAVE_PRAGMA_VECTOR_ALIGNED
#pragma vector aligned
#endif
#ifdef STOKHOS_HAVE_PRAGMA_UNROLL
#pragma unroll
#endif
      for (O i=0; i<a.size(); ++i)
        c.fastAccessCoeff(i) =
          OPNAME( a.fastAccessCoeff(i) ,  b.fastAccessCoeff(i) );
      return c;
    }

    template <typename O, typename T, int N, typename D>
    KOKKOS_INLINE_FUNCTION
    Vector< Stokhos::StaticFixedStorage<O,T,N,D> >
    OPNAME (const volatile Vector< Stokhos::StaticFixedStorage<O,T,N,D> >& a,
            const volatile Vector< Stokhos::StaticFixedStorage<O,T,N,D> >& b)
    {
      using std::OPNAME;
      Vector< Stokhos::StaticFixedStorage<O,T,N,D> > c;
#ifdef STOKHOS_HAVE_PRAGMA_IVDEP
#pragma ivdep
#endif
#ifdef STOKHOS_HAVE_PRAGMA_VECTOR_ALIGNED
#pragma vector aligned
#endif
#ifdef STOKHOS_HAVE_PRAGMA_UNROLL
#pragma unroll
#endif
      for (O i=0; i<a.size(); ++i)
        c.fastAccessCoeff(i) =
          OPNAME( a.fastAccessCoeff(i) ,  b.fastAccessCoeff(i) );
      return c;
    }

    template <typename O, typename T, int N, typename D>
    KOKKOS_INLINE_FUNCTION
    Vector< Stokhos::StaticFixedStorage<O,T,N,D> >
    OPNAME (const Vector< Stokhos::StaticFixedStorage<O,T,N,D> >& a,
            const volatile Vector< Stokhos::StaticFixedStorage<O,T,N,D> >& b)
    {
      using std::OPNAME;
      Vector< Stokhos::StaticFixedStorage<O,T,N,D> > c;
#ifdef STOKHOS_HAVE_PRAGMA_IVDEP
#pragma ivdep
#endif
#ifdef STOKHOS_HAVE_PRAGMA_VECTOR_ALIGNED
#pragma vector aligned
#endif
#ifdef STOKHOS_HAVE_PRAGMA_UNROLL
#pragma unroll
#endif
      for (O i=0; i<a.size(); ++i)
        c.fastAccessCoeff(i) =
          OPNAME( a.fastAccessCoeff(i) ,  b.fastAccessCoeff(i) );
      return c;
    }

    template <typename O, typename T, int N, typename D>
    KOKKOS_INLINE_FUNCTION
    Vector< Stokhos::StaticFixedStorage<O,T,N,D> >
    OPNAME (const volatile Vector< Stokhos::StaticFixedStorage<O,T,N,D> >& a,
            const Vector< Stokhos::StaticFixedStorage<O,T,N,D> >& b)
    {
      using std::OPNAME;
      Vector< Stokhos::StaticFixedStorage<O,T,N,D> > c;
#ifdef STOKHOS_HAVE_PRAGMA_IVDEP
#pragma ivdep
#endif
#ifdef STOKHOS_HAVE_PRAGMA_VECTOR_ALIGNED
#pragma vector aligned
#endif
#ifdef STOKHOS_HAVE_PRAGMA_UNROLL
#pragma unroll
#endif
      for (O i=0; i<a.size(); ++i)
        c.fastAccessCoeff(i) =
          OPNAME( a.fastAccessCoeff(i) ,  b.fastAccessCoeff(i) );
      return c;
    }

    template <typename O, typename T, int N, typename D>
    KOKKOS_INLINE_FUNCTION
    Vector< Stokhos::StaticFixedStorage<O,T,N,D> >
    OPNAME (const typename Vector< Stokhos::StaticFixedStorage<O,T,N,D> >::value_type& a,
            const Vector< Stokhos::StaticFixedStorage<O,T,N,D> >& b)
    {
      using std::OPNAME;
      Vector< Stokhos::StaticFixedStorage<O,T,N,D> > c;
#ifdef STOKHOS_HAVE_PRAGMA_IVDEP
#pragma ivdep
#endif
#ifdef STOKHOS_HAVE_PRAGMA_VECTOR_ALIGNED
#pragma vector aligned
#endif
#ifdef STOKHOS_HAVE_PRAGMA_UNROLL
#pragma unroll
#endif
      for (O i=0; i<b.size(); ++i)
        c.fastAccessCoeff(i) =
          OPNAME( a , b.fastAccessCoeff(i) );
      return c;
    }

    template <typename O, typename T, int N, typename D>
    KOKKOS_INLINE_FUNCTION
    Vector< Stokhos::StaticFixedStorage<O,T,N,D> >
    OPNAME (const typename Vector< Stokhos::StaticFixedStorage<O,T,N,D> >::value_type& a,
            const volatile Vector< Stokhos::StaticFixedStorage<O,T,N,D> >& b)
    {
      using std::OPNAME;
      Vector< Stokhos::StaticFixedStorage<O,T,N,D> > c;
#ifdef STOKHOS_HAVE_PRAGMA_IVDEP
#pragma ivdep
#endif
#ifdef STOKHOS_HAVE_PRAGMA_VECTOR_ALIGNED
#pragma vector aligned
#endif
#ifdef STOKHOS_HAVE_PRAGMA_UNROLL
#pragma unroll
#endif
      for (O i=0; i<b.size(); ++i)
        c.fastAccessCoeff(i) =
          OPNAME( a , b.fastAccessCoeff(i) );
      return c;
    }

    template <typename O, typename T, int N, typename D>
    KOKKOS_INLINE_FUNCTION
    Vector< Stokhos::StaticFixedStorage<O,T,N,D> >
    OPNAME (const Vector< Stokhos::StaticFixedStorage<O,T,N,D> >& a,
            const typename Vector< Stokhos::StaticFixedStorage<O,T,N,D> >::value_type& b)
    {
      using std::OPNAME;
      Vector< Stokhos::StaticFixedStorage<O,T,N,D> > c;
#ifdef STOKHOS_HAVE_PRAGMA_IVDEP
#pragma ivdep
#endif
#ifdef STOKHOS_HAVE_PRAGMA_VECTOR_ALIGNED
#pragma vector aligned
#endif
#ifdef STOKHOS_HAVE_PRAGMA_UNROLL
#pragma unroll
#endif
      for (O i=0; i<a.size(); ++i)
        c.fastAccessCoeff(i) =
          OPNAME( a.fastAccessCoeff(i) , b );
      return c;
    }

    template <typename O, typename T, int N, typename D>
    KOKKOS_INLINE_FUNCTION
    Vector< Stokhos::StaticFixedStorage<O,T,N,D> >
    OPNAME (const volatile Vector< Stokhos::StaticFixedStorage<O,T,N,D> >& a,
            const typename Vector< Stokhos::StaticFixedStorage<O,T,N,D> >::value_type& b)
    {
      using std::OPNAME;
      Vector< Stokhos::StaticFixedStorage<O,T,N,D> > c;
#ifdef STOKHOS_HAVE_PRAGMA_IVDEP
#pragma ivdep
#endif
#ifdef STOKHOS_HAVE_PRAGMA_VECTOR_ALIGNED
#pragma vector aligned
#endif
#ifdef STOKHOS_HAVE_PRAGMA_UNROLL
#pragma unroll
#endif
      for (O i=0; i<a.size(); ++i)
        c.fastAccessCoeff(i) =
          OPNAME( a.fastAccessCoeff(i) , b );
      return c;
    }
  }
}
