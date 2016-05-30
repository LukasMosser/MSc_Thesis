#ifndef WRITE_FUNCTIONS
#define WRITE_FUNCTIONS

#include "../lib/common.h"
#include "../lib/CalcOptions.h"
#include "../lib/check_surface.h"
#include "../lib/MinkValResultType.h"
#include <math.h>
#include <cassert>
#include <iomanip>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include "print_explanations.h"

void write_surface_props_to_file(const CalcOptions& CO, const SurfaceStatistics& SurfStat);

void write_CompWiseEigenSystemMinkValResultType_to_file(const CalcOptions& CO, const CompWiseEigenSystemMinkValResultType &w_eigsys);

void write_CompWiseMatrixMinkValResultType_to_file( const CalcOptions& CO,
                                                    const CompWiseMatrixMinkValResultType &w);

void write_CompWiseScalarMinkValResultType_to_file( const CalcOptions& CO,
                                                    const CompWiseScalarMinkValResultType &w000,
                                                    const CompWiseScalarMinkValResultType &w100,
                                                    const CompWiseScalarMinkValResultType &w200,
                                                    const CompWiseScalarMinkValResultType &w300);



void write_CompWiseVectorMinkValResultType_to_file( const CalcOptions& CO,
                                                    const CompWiseVectorMinkValResultType &w010,
                                                    const CompWiseVectorMinkValResultType &w110,
                                                    const CompWiseVectorMinkValResultType &w210,
                                                    const CompWiseVectorMinkValResultType &w310);

#endif // WRITE_FUNCTIONS
