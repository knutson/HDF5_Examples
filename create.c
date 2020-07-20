
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <mpi.h>
#include <hdf5.h>

int main( int argc, char *argv[] )
{

   hid_t id_type;
   id_type = H5T_NATIVE_INT;

   hid_t       file_id, group_id, dataset_id, dataspace_id, memspace_id;
   hsize_t     dims[2];
   herr_t      status;
   int         i, j, dset_data[4][6];

   // Initialize the dataset
   for (i = 0; i < 4; i++) {
      for (j = 0; j < 6; j++) {
         dset_data[i][j] = 6*i + j;
      }
    }

//   H5open();

   // Create a new file using default properties
   file_id = H5Fcreate("file.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

   // Create a group
   // What is H5Gcreate2 used for?
   group_id = H5Gcreate(file_id, "/MyGroup", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

   // Create the data space for the dataset
   dims[0] = 4;
   dims[1] = 6;
   dataspace_id = H5Screate_simple(2, dims, NULL);

   // Create the dataset
   //dataset_id = H5Dcreate(file_id, "/MyGroup/dset", H5T_STD_I32BE, dataspace_id, 
   //                       H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
   dataset_id = H5Dcreate(group_id, "dset", id_type, dataspace_id,
                          H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

   status = H5Dwrite(dataset_id, id_type, H5S_ALL, H5S_ALL, H5P_DEFAULT, dset_data);

   // *** OVERWRITE A SUBSET OF THE DATA WITH ZEROS ***

   //ndims = 2
   hsize_t icnt[2] = {2, 3};
   hsize_t ioff[2] = {1, 2};
   hsize_t istd[2] = {1, 1};
   hsize_t iblk[2] = {1, 1};

   int sdata[2][3] = {{0, 0, 0},{0, 0, 0}};

   // create a transfer property list with parallel I/O
   //id_plist = H5Pcreate( H5P_DATASET_XFER );
   //H5Pset_dxpl_mpio( id_plist, H5FD_MPIO_COLLECTIVE );

   memspace_id = H5Screate_simple( 2, icnt, icnt );

   H5Sselect_hyperslab( dataspace_id, H5S_SELECT_SET, ioff, istd, icnt, iblk );

   status = H5Dwrite(dataset_id, id_type, memspace_id, dataspace_id, H5P_DEFAULT, sdata);

   //INHDF5
   //ierr = H5Dwrite( id_data, id_type, id_mem, id_space, id_plist, data );

   // *************************************************

   H5Sclose( memspace_id );
   //H5Pclose( id_plist );

   // Close the data space
   status = H5Sclose(dataspace_id);

   // Close the dataset
   status = H5Dclose(dataset_id);

   // Close the group
   status = H5Gclose(group_id);

   // Close the file
   status = H5Fclose(file_id);

   printf("status: %d\n",status);

//   H5close();

   return 0;
}

