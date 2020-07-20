
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <mpi.h>
#include <hdf5.h>

int main( int argc, char *argv[] )
{

   hid_t id_type;
   id_type = H5T_NATIVE_INT;

   hid_t       file_id, group_id, dataset_id, dataspace_id;
   herr_t      status;

//   H5open();

   file_id = H5Fopen("file.h5", H5F_ACC_RDWR, H5P_DEFAULT);

   // Open an existing group
   // What is H5Gopen2 used for?
   group_id = H5Gopen(file_id, "/MyGroup", H5P_DEFAULT);

   // Open dataset
   // What is H5Dopen2 used for?
   //dataset_id = H5Dopen(file_id, "/MyGroup/dset", H5P_DEFAULT);
   //dataset_id = H5Dopen(file_id, "MyGroup/dset", H5P_DEFAULT);
   dataset_id = H5Dopen(group_id, "dset", H5P_DEFAULT);

   // Return an identifier for a copy of the dataspace for a dataset
   dataspace_id = H5Dget_space(dataset_id);

   // Determine the dimensionality of a dataspace
   hsize_t ndims = H5Sget_simple_extent_ndims(dataspace_id);

   printf("ndims: %lld\n",ndims);

   hsize_t dims[ndims], maxdims[ndims];

   // Retrieve dataspace dimension size and maximum size
   H5Sget_simple_extent_dims(dataspace_id,dims,maxdims);

   printf("dims: ");
   for (int i=0;i<ndims;++i) {
      printf("%lld ",dims[i]);
   }
   printf("\n");

   // INITIALIZE DATA
   int read_data[dims[0]][dims[1]];

   // READ DATA
   status = H5Dread(dataset_id, id_type, H5S_ALL, H5S_ALL, H5P_DEFAULT, read_data);

   // PRINT DATA
   printf("data:\n");
   for (int i = 0; i < dims[0]; i++) {
      for (int j = 0; j < dims[1]; j++) {
         if (read_data[i][j]<10) {
            printf(" %d ",read_data[i][j]);
         } else {
            printf("%d ",read_data[i][j]);
         }
      }
      printf("\n");
   }

   status = H5Dclose(dataset_id);

   status = H5Gclose(group_id);

   status = H5Fclose(file_id);

   printf("status: %d\n",status);

//   H5close();

   return 0;
}

