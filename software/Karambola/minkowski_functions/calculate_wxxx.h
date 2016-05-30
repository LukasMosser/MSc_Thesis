#ifndef CALCULATE_XXX
#define CALCULATE_XXX

#include "calculate.h"
#include <math.h>
#include <iostream>
#include <string>

template <typename T> void set_NAN (T &input);
template <> void set_NAN (double &input){
    input = NAN;
}
template <> void set_NAN (Vector &input){
    Vector test(NAN,NAN,NAN);
    input = test;
}
template <int U> void set_NAN (SymmetricMatrix<U> &input){
    SymmetricMatrix<U> test;
    for (size_t a = 0; a < test.size1(); a++)
    for (size_t b = a; b < test.size2(); b++)
        test(a,b) = NAN;
    input = test;
}


template <typename T>
T calculate_w ( const std::string &name,
                const Triangulation& surface,
                const CompWiseScalarMinkValResultType &w_scalar = CompWiseScalarMinkValResultType(),
                const CompWiseVectorMinkValResultType &w_vector = CompWiseVectorMinkValResultType());

template <>
CompWiseScalarMinkValResultType calculate_w (const std::string &name,
                                             const Triangulation& surface,
                                             const CompWiseScalarMinkValResultType &w_scalar,
                                             const CompWiseVectorMinkValResultType &w_vector){

    if(name == "w000")
        return calculate_w000(surface);
    if(name == "w100")
        return calculate_w100(surface);
    if(name == "w200")
        return calculate_w200(surface);
    if(name == "w300")
        return calculate_w300(surface);
    abort ();
}

template <>
CompWiseVectorMinkValResultType calculate_w (const std::string &name,
                                             const Triangulation& surface,
                                             const CompWiseScalarMinkValResultType &w_scalar,
                                             const CompWiseVectorMinkValResultType &w_vector){

    if(name == "w010")
        return calculate_w010(surface);
    if(name == "w110")
        return calculate_w110(surface);
    if(name == "w210")
        return calculate_w210(surface);
    if(name == "w310")
        return calculate_w310(surface);
    abort ();
}

template <>
CompWiseMatrixMinkValResultType calculate_w (const std::string &name,
                                             const Triangulation &surface,
                                             const CompWiseScalarMinkValResultType &w_scalar,
                                             const CompWiseVectorMinkValResultType &w_vector){
    if(name == "w020")
        return calculate_w020(surface, w_scalar, w_vector);
    if(name == "w120")
        return calculate_w120(surface, w_scalar, w_vector);
    if(name == "w220")
        return calculate_w220(surface, w_scalar, w_vector);
    if(name == "w320")
        return calculate_w320(surface, w_scalar, w_vector);
    if(name == "w102")
        return calculate_w102(surface);
    if(name == "w202")
        return calculate_w202(surface);
    abort ();
}

template<typename T>
T calculate_wxxx(   const std::string name,
                    const CalcOptions& CO,
                    const Triangulation& surface,
                    const CompWiseScalarMinkValResultType w_scalar = CompWiseScalarMinkValResultType(),
                    const CompWiseVectorMinkValResultType w_vector = CompWiseVectorMinkValResultType()){
    T w;
    if(CO.get_compute(name) == false && CO.get_force(name) == false)
        return w;
    std::cout << "calculate " << name << " ...";
    std::cout.flush();

    if (CO.reference_origin == false)
        w = calculate_w<T>(name, surface, w_scalar, w_vector); 
    else
        w = calculate_w<T>(name, surface); 


//    add_surface_props;
    for (w.it = w.begin (); w.it != w.end (); ++w.it) {

        w.it->second.name_ = name;

        int test = CO.get_label_closed_status (w.it->first);
        if (test == 0) w.it->second.append_keyword( "closed" );
        if (test == 1) w.it->second.append_keyword ( "shared" );
        if (test == 2) w.it->second.append_keyword ("open" );
        if( CO.reference_origin == true)
            w.it->second.append_keyword(reference_origin_string.first);
        else
            w.it->second.append_keyword(reference_centroid_string.first);
    }

    //check if w can be calculated or is forced to be calculated
    for (w.it = w.begin (); w.it != w.end (); ++w.it) {
        if(CO.get_label_closed_status(w.it->first) > CO.get_allowed_to_calc(name)){
            if (CO.get_force(name) == true){
                w.it->second.append_keyword(calc_forced.first);
            }
            else{
                set_NAN(w.it->second.result_);
                w.it->second.append_keyword(cant_calc.first);
            }
        }
    }

    std::cout << "     done" << std::endl;
    return w;
}


#endif // CALCULATE_XXX

