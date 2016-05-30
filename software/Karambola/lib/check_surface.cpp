#include "check_surface.h"

#include <math.h>
#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include <errno.h>
#include <stdexcept>


SurfaceStatistics check_surface(CalcOptions* CO, Triangulation& surface){


    SurfaceStatistics SurfStat;

    //are there polys/triangles?
    if (surface.n_triangles() == 0)
        throw std::runtime_error ("There are no polygons in your .poly file");

    //is surface closed?
    for(unsigned int i = 0; i<surface.n_triangles();i++){
        CO->create_label (surface.label_of_triangle (i), 0);
    }

    for(unsigned int i = 0; i<surface.n_triangles();i++){
      for(int j = 0; j < 3; j++){
        if(surface.ith_neighbour_of_triangle(i,j) != NEIGHBOUR_UNASSIGNED){
          if(surface.label_of_triangle(i) != surface.label_of_triangle(surface.ith_neighbour_of_triangle(i,j))){
            CO->create_label (surface.label_of_triangle (i), 1);
          }
        }
      }
    }
    for(unsigned int i = 0; i<surface.n_triangles();i++){
      for(int j = 0; j < 3; j++){
        if(surface.ith_neighbour_of_triangle(i,j) == NEIGHBOUR_UNASSIGNED){
            CO->create_label (surface.label_of_triangle (i), 2);
        }
      }
    }

    //get surface properties
    double shortest_edge = std::numeric_limits<double>::max();
    double longest_edge = 0;
    for(unsigned int i = 0; i<surface.n_triangles();i++){
        for(unsigned int j = 0; j<3;j++){
            Vector v1 = surface.get_pos_of_vertex(surface.ith_vertex_of_triangle(i,j));
            Vector v2 = surface.get_pos_of_vertex(surface.ith_vertex_of_triangle(i,(j+1)%3));
            double e = norm(v1-v2);
            if (e<shortest_edge)
                shortest_edge = e;
            if (e>longest_edge)
                longest_edge = e;
        }
    }
    SurfStat.shortest_edge = shortest_edge;
    SurfStat.longest_edge = longest_edge;
    double smallest_area = std::numeric_limits<double>::max();
    double largest_area = 0;
    for(unsigned int i = 0; i<surface.n_triangles();i++){
        double area = surface.area_of_triangle(i);
        if (area<smallest_area)
                smallest_area = area;
        if (area>largest_area)
                largest_area = area;
    }
    SurfStat.smallest_area = smallest_area;
    SurfStat.largest_area = largest_area;

    //check if more than one objects are at one vertex
    for(unsigned int i = 0; i<surface.n_vertices();i++){
        unsigned int sum_of_triangles = 1;
        if (surface.get_triangles_of_vertex(i).size() == 0) break;
        unsigned int start_triangle = surface.get_triangles_of_vertex(i).at(0);
        unsigned int new_triangle = surface.get_triangles_of_vertex(i).at(0);

//FIXME
        bool neigh_un = false;

        for (unsigned int j = 0; j< surface.get_triangles_of_vertex(i).size();j++){
            unsigned int triangle = new_triangle;
            unsigned int vertex_id = 0;
            for (unsigned int k = 0; k < 3; k++){
                if(surface.ith_vertex_of_triangle(triangle,k)==i){
                    vertex_id = k;
                }
            }

//FIXME
            if (surface.ith_neighbour_of_triangle(triangle,vertex_id) == NEIGHBOUR_UNASSIGNED){ neigh_un = true; break;}
            new_triangle = surface.ith_neighbour_of_triangle(triangle,vertex_id);
            if (new_triangle == start_triangle) break;
            sum_of_triangles+=1;
        }

//FIXME
        if(surface.get_triangles_of_vertex(i).size() != sum_of_triangles && neigh_un == false){
            //throw std::runtime_error ("your polyfile is damaged\nthere are more than one objects at one vertex\n"+std::to_string(i)+" "+std::to_string(sum_of_triangles+"\n"));
        }
    }

    return SurfStat;

}


