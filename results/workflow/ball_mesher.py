from pykowski.image import VoxelImage
from pykowski.processes import unique_random_subsets, run_karambola
from pykowski.meshing import mesh_from_vtk_discrete
from pykowski.io import write_poly_from_mesh
from pykowski.karambola import KarambolaResults
import os
import click
import numpy as np
import shutil
from tqdm import *
from skimage.filters import gaussian

#@click.command()
#@click.option('--file', default='/images/ketton.tif', help="Image to process")
#@click.option('--samples', default=1, help='Number of samples to compute')
#@click.option('--dx', nargs=3, default=[50, 50, 50], type=click.Tuple([int, int, int]), help="Tuple of 3 indices indicating the subvolume box size")
#@click.option('--seed', default=666, help='Random number generator seed')
#@click.option('--dest', default='/results', help="The folder to output results to.")
#@click.option('--level', default=0.8, help="Level set to use for construction of mesh.")
def run_app():#file, samples, dx, seed, dest, level):
    dest = "figure_meshes"
    image_name = "image_data/images/Berea.tif" #file.split("/")[-1].strip(".tif")
    im = VoxelImage(image_name)
    midpoint = [int(np.floor(im.image.shape[0]/2.)), int(np.floor(im.image.shape[1]/2.)), int(np.floor(im.image.shape[2]/2.))]
    i = 75
    subset = im.image[midpoint[0]-i:midpoint[0]+i, midpoint[1]-i:midpoint[1]+i, midpoint[2]-i:midpoint[2]+i]
    indices = [str(int(val)) for val in subset.shape]
    name = "_".join(indices)
    print im.image.shape
    try:
        mesh = mesh_from_vtk_discrete(subset, stl=True, filter=True)
        #out_str = dest+"/"+name
        #out = write_poly_from_mesh(out_str, mesh, export_off=False)
    except (ValueError, AttributeError) as e:
        print "Could not threshold ", name
    print "Finished. Exiting."""
	

if __name__ == "__main__":
    run_app()