#ifndef TENSOR_RANK4_INCLUDED 
#define TENSOR_RANK4_INCLUDED 

#include <assert.h>
#include "Vector.h"
#include <vector>

template <int N>
class SymmetricMatrix
{
public:
    typedef SymmetricMatrix <N> this_t;
    static const int NUM_INDEP_ELEMENTS = N*(N+1)/2;

    SymmetricMatrix () {
        for (int i = 0; i != NUM_INDEP_ELEMENTS; ++i)
            st_[i] = 0.;
    }

    const double &operator() (int i, int j) const
    {
        return const_cast <this_t &> (*this) (i,j);
    }

    double &operator() (int i, int j)
    {
        if (i > j)
            return (*this)(j, i);
        assert (i < N && i >= 0);
        assert (j < N && j >= 0);
        return st_[j*(j+1)/2+i];
    }

    size_t size1 () const { return N; }
    size_t size2 () const { return N; }

    friend void addmul (this_t &lhs, double pref, const this_t &rhs) {
        for (int i = 0; i != NUM_INDEP_ELEMENTS; ++i)
            lhs.st_[i] += pref * rhs.st_[i];
    }

    this_t &operator+= (const this_t &rhs) {
        for (int i = 0; i != NUM_INDEP_ELEMENTS; ++i)
            st_[i] += rhs.st_[i];
        return *this;
    }

    this_t &operator-= (const this_t &rhs) {
        for (int i = 0; i != NUM_INDEP_ELEMENTS; ++i)
            st_[i] -= rhs.st_[i];
        return *this;
    }


private:
    double st_[NUM_INDEP_ELEMENTS];
};


typedef SymmetricMatrix <3> symmetric_matrix;


#endif /* TENSOR_RANK4_INCLUDED */
