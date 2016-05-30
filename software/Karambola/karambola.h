// vim: et:sw=4:ts=4
//!  -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//!  Authors       : Fabian Schaller     fabian.schaller@physik.uni-erlangen.de
//!                  Sebastian Kapfer    sebastian.kapfer@physik.uni-erlangen.de
//!                  Gerd Schroeder-Turk gerd.schroeder-turk@physik.uni-erlangen.de
//!  File          : karambola.h
//!  copyright     : Universitaet Erlangen
//!  Version       : 1.5-NJP
//!  
//!  Journal Ref.  : Gerd Schroeder-Turk et al., Minkowski Tensors of Anisotropic
//!                  Spatial Structure, New Journal of Physics, 2013
//!  -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


#ifndef KARAMBOLA_H_INCLUDED
#define KARAMBOLA_H_INCLUDED

#include <math.h>
#include <string>
#include <iostream>

#include "lib/Vector.h"
#include "lib/tensor.h"
#include "lib/MinkValResultType.h"
#include "lib/check_command_line.h"
#include "lib/check_surface.h"
#include "lib/CalcOptions.h"

#include "minkowski_functions/calculate.h"
#include "minkowski_functions/calculate_wxxx.h"

#include "lib/calculate_eigensystem.h"

#include "print_functions/print_functions.h"
#include "print_functions/write_functions.h"

#endif // KARAMBOLA_H_INCLUDED
