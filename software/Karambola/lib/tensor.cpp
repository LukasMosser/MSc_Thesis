#include "tensor.h"
#include "gsleig.h"


template <int N>
std::vector <double> eigenvalues (const SymmetricMatrix <N> &mat)
{
    EigensystemWorkspace e (N);
    e.diagonalize_matrix (mat);
    std::vector <double> ret;
    ret.reserve (N);
    for (int i = 0; i != N; ++i)
        ret.push_back (e.eigenvalue (i));
    return ret;
}

template std::vector <double> eigenvalues (const SymmetricMatrix <3> &mat);
template std::vector <double> eigenvalues (const SymmetricMatrix <6> &mat);
